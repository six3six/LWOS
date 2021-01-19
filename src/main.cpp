#include "lib/UILib.h"
#include "lib/ButtonLib.h"
#include "lib/RTCLib.h"
#include "DaemonRegister.h"
#include "daemon/BLDaemon.h"
#include "WiFi.h"


#define DEBUG true

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

[[noreturn]] void rtc_check(void *param) {
    QueueHandle_t handle;
    RTCLib::createAndSubscribe(&handle);

    RTCDriverCallbackFrame_st buff{};
    while (true) {
        RTCLib::triggerDate();
        if (xQueueReceive(handle, &buff, 1000)) {
            UILib::DrawFillSquare(0, 0, 500, 60, ST7735_BLACK);
            String ret;
            ret += RTCLib::weekdayToString(buff.date.weekday);
            UILib::DrawString(0, 0, ret.c_str());

            ret = "";
            ret += RTCLib::int2number(buff.date.day, 2);
            ret += "/";
            ret += RTCLib::int2number(buff.date.month, 2);
            ret += "/";
            ret += RTCLib::int2number(buff.date.year, 4);
            UILib::DrawString(0, 20, ret.c_str());
            ret = "";
            ret += RTCLib::int2number(buff.date.hour, 2);
            ret += ":";
            ret += RTCLib::int2number(buff.date.minute, 2);
            ret += ":";
            ret += RTCLib::int2number(buff.date.second, 2);
            UILib::DrawString(0, 40, ret.c_str());
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void initDrivers() {
    UILib::initDrivers();
    UILib::ChangeLightMode(LOW);
    ButtonLib::initDrivers();
    RTCLib::initDrivers();
}

void initDaemons() {
    DaemonRegister::AddDaemon(new BLDaemon());

    DaemonRegister::StartDaemons();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting");

    pinMode(TP_PWR_PIN, PULLUP);
    digitalWrite(TP_PWR_PIN, HIGH);

    initDrivers();
    initDaemons();

    if (DEBUG && Serial.availableForWrite()) {
        xTaskCreate(heap_check, "HeapCheckProcess", 2000, nullptr, 1, nullptr);
    }


    UILib::DrawSquare(10, 10, 10, 10, ST7735_BLUE);
    UILib::DrawString(30, 30, "OK !");

    xTaskCreate(rtc_check, "rtc_check", 2000, nullptr, 1, nullptr);

    WiFi.begin("LiveboxADE", "Arnaud77420");
    UILib::DrawFillSquare(0, 60, 300, 20, ST7735_BLACK);
    UILib::DrawString(0, 60, "Connexion...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    UILib::DrawFillSquare(0, 60, 300, 20, ST7735_BLACK);

    String ip = WiFi.localIP().toString();
    Serial.println(ip);

    UILib::DrawString(0, 60, ip.c_str(), 10000);
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 3600;
    const int daylightOffset_sec = 3600;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    tm date{};

    if (getLocalTime(&date)) {
        RTCLib::setDate({
                                DateTime_st{
                                        (uint16_t) (date.tm_year + 1900),
                                        (uint8_t) (date.tm_mon + 1),
                                        (uint8_t) date.tm_mday,
                                        (uint8_t) date.tm_hour,
                                        (uint8_t) date.tm_min,
                                        (uint8_t) date.tm_sec,
                                        (Weekday_e) date.tm_wday
                                }
                        });
    }


}

void loop() {
    vTaskDelay(portMAX_DELAY);
}

