#include <EnergyManager.h>
#include "lib/UILib.h"
#include "lib/ButtonLib.h"
#include "lib/RTCLib.h"
#include "DaemonRegister.h"
#include "daemon/BLDaemon.h"
#include "WiFi.h"
#include <ArduinoOTA.h>


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

#define BATTERY_MIN_V 2.9
#define BATTERY_MAX_V 3.7

int vref = 1100;

float getVoltage() {
    uint16_t v = analogRead(BATT_ADC_PIN);
    return ((float) v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
}

uint8_t calcPercentage(float volts) {
    uint8_t percentage = (volts - BATTERY_MIN_V) * 100 / (BATTERY_MAX_V - BATTERY_MIN_V);
    if (percentage > 100) {
        percentage = 100;
    }
    if (percentage < 0) {
        percentage = 0;
    }
    return percentage;
}

[[noreturn]] IRAM_ATTR void rtc_check(void *param) {
    QueueHandle_t handle;
    RTCLib::createAndSubscribe(&handle);

    tm current_date{INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX};
    tm prev_date{INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX};
    UILib::DrawString(20, 20, "/", 1000);
    UILib::DrawString(50, 20, "/", 1000);
    UILib::DrawString(20, 40, ":", 1000);
    UILib::DrawString(50, 40, ":", 1000);

    pinMode(CHARGE_PIN, INPUT_PULLUP);

    int voltage_take;
    float voltage_mean;

    while (true) {
        getLocalTime(&current_date);
        if (prev_date.tm_wday != current_date.tm_wday) {
            UILib::DrawFillSquare(0, 0, 210, 20, ST7735_BLACK, 1000);
            UILib::DrawString(0, 0, RTCLib::weekdayToString((Weekday_e) current_date.tm_wday).c_str(), 1000);
        }

        if (prev_date.tm_mday != current_date.tm_mday) {
            UILib::DrawFillSquare(0, 20, 23, 20, ST7735_BLACK, 1000);
            UILib::DrawString(0, 20, RTCLib::int2number(current_date.tm_mday, 2).c_str(), 1000);
        }

        if (prev_date.tm_mon != current_date.tm_mon) {
            UILib::DrawFillSquare(30, 20, 23, 20, ST7735_BLACK, 1000);
            UILib::DrawString(30, 20, RTCLib::int2number(current_date.tm_mon + 1, 2).c_str(), 1000);
        }

        if (prev_date.tm_year != current_date.tm_year) {
            UILib::DrawFillSquare(60, 20, 50, 20, ST7735_BLACK, 1000);
            UILib::DrawString(60, 20, RTCLib::int2number(current_date.tm_year + 1900, 4).c_str(), 1000);
        }

        if (prev_date.tm_hour != current_date.tm_hour) {
            UILib::DrawFillSquare(0, 40, 23, 20, ST7735_BLACK, 1000);
            UILib::DrawString(0, 40, RTCLib::int2number(current_date.tm_hour, 2).c_str(), 1000);
        }

        if (prev_date.tm_min != current_date.tm_min) {
            UILib::DrawFillSquare(30, 40, 23, 20, ST7735_BLACK, 1000);
            UILib::DrawString(30, 40, RTCLib::int2number(current_date.tm_min, 2).c_str(), 1000);
        }

        if (prev_date.tm_sec != current_date.tm_sec) {
            UILib::DrawFillSquare(60, 40, 23, 20, ST7735_BLACK, 1000);
            UILib::DrawString(60, 40, RTCLib::int2number(current_date.tm_sec, 2).c_str(), 1000);
        }

        if (voltage_take < 3) {
            voltage_take++;
            voltage_mean += getVoltage();
        } else {
            UILib::DrawFillSquare(90, 40, 60, 20, ST7735_BLACK, 1000);
            UILib::DrawString(90, 40,
                              (RTCLib::int2number(calcPercentage(voltage_mean / (float) voltage_take), 2) +
                               "%").c_str(), 1000);
            if(digitalRead(CHARGE_PIN) == LOW){
                UILib::DrawString(140, 40, "C");
            }
            voltage_take = 0;
            voltage_mean = 0;
        }


        getLocalTime(&prev_date);


        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void initDrivers() {
    UILib::initDrivers();
    ButtonLib::initDrivers();
    RTCLib::initDrivers();
}

void initDaemons() {
    DaemonRegister::AddDaemon(new BLDaemon());

    DaemonRegister::StartDaemons();
}

void reachNTP() {
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
    } else {
        RTCLib::syncToSystem();
    }
}

IRAM_ATTR void setup() {
    Serial.begin(115200);
    Serial.println("Starting");

    pinMode(LED_PIN, OUTPUT);
    //digitalWrite(LED_PIN, HIGH);


    pinMode(TP_PWR_PIN, PULLUP);
    digitalWrite(TP_PWR_PIN, HIGH);

    initDrivers();
    initDaemons();

#if DEBUG
    xTaskCreate(heap_check, "HeapCheckProcess", 2000, nullptr, 1, nullptr);
#endif

    EnergyManager::Run();

    xTaskCreate(rtc_check, "rtc_check", 2000, nullptr, 1, nullptr);

    WiFi.begin("LiveboxADE", "Arnaud77420");
    UILib::DrawFillSquare(0, 60, 300, 20, ST7735_BLACK);
    UILib::DrawString(0, 60, "Connexion...");
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(1000);
    }


    UILib::DrawFillSquare(0, 60, 300, 20, ST7735_BLACK);


    String ip = WiFi.localIP().toString();
    UILib::DrawString(0, 60, ip.c_str(), 10000);

    reachNTP();
    ArduinoOTA.begin();
}

void loop() {
    ArduinoOTA.handle();
    vTaskDelay(500);
}

