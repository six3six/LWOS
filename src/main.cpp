
#include "esp_pm.h"

#include <EnergyManager.h>
#include "lib/RTCLib.h"
#include "DaemonRegister.h"
#include "daemon/BLDaemon.h"
#include "WiFi.h"
#include <lib/OTALib.h>
#include <ApplicationManager.h>
#include "application/HourApp.h"
#include "config.h"


#define DEBUG false

[[noreturn]] void heap_check(void *param) {
    while (true) {
        Serial.print(F("Heap used : "));
        Serial.print(ESP.getHeapSize() - ESP.getFreeHeap());
        Serial.print("/");
        Serial.print(ESP.getHeapSize());
        Serial.print(" - ");
        Serial.print(((double) (ESP.getHeapSize() - ESP.getFreeHeap()) / (double) ESP.getHeapSize()) * (double) 100);
        Serial.print("%");
        Serial.println();
        vTaskDelay(10000);
    }
}


IRAM_ATTR void initDrivers() {
    UILib::initDrivers();
    ButtonLib::initDrivers();
    RTCLib::initDrivers();
    //OTALib::initDrivers();
}

IRAM_ATTR void initDaemons() {
    //DaemonRegister::AddDaemon(new BLDaemon());

    DaemonRegister::StartDaemons();
}


void scanI2Cdevice() {
    uint8_t err, addr;
    int nDevices = 0;
    for (addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        err = Wire.endTransmission();
        if (err == 0) {
            Serial.print("I2C device found at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.print(addr, HEX);
            Serial.println(" !");
            nDevices++;
        } else if (err == 4) {
            Serial.print("Unknow error at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.println(addr, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Done\n");
}

IRAM_ATTR void setup() {
    Serial.begin(115200);
    Serial.println("Starting");

    esp_log_level_set("*", ESP_LOG_ERROR);
    esp_log_level_set(EnMag_TAG, ESP_LOG_INFO);

    ESP_LOGE("SETUP", "CpuFrequency : %d", getCpuFrequencyMhz());

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(400000);

    scanI2Cdevice();

    pinMode(LED_PIN, OUTPUT);
    //digitalWrite(LED_PIN, HIGH);

    pinMode(TP_PWR_PIN, PULLUP);
    digitalWrite(TP_PWR_PIN, HIGH);

    initDrivers();
    initDaemons();



#if DEBUG
    xTaskCreate(heap_check, "HeapCheckProcess", 2000, nullptr, 1, nullptr);
#endif

    Serial.println("Running EnergyManager");
    EnergyManager::Run();
    Serial.println("Syncing RTC to system");
    RTCLib::syncToSystem();

    ApplicationManager::StartApp(new HourApp());

    Serial.println("Connecting");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        if (WiFi.status() == WL_CONNECT_FAILED) ESP.restart();
    }


    Serial.println("Wifi connected");

    OTALib::initDrivers();

    configTime(3600, 3600, "pool.ntp.org");


    tm t{};
    if (getLocalTime(&t)) {
        RTCLib::syncFromSystem();
    }

}

void loop() {
    vTaskDelay(portMAX_DELAY);
}

