#include "lib/UILib.h"
#include "lib/ButtonLib.h"
#include "lib/RTCLib.h"

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

[[noreturn]] void button_check(void *param) {
    QueueHandle_t handle;
    ButtonLib::createAndSubscribe(&handle);
    GPIOInput_st buff{};
    while (true) {

        if (xQueueReceive(handle, &buff, 10000)) {
            if (buff.pin == TP_PIN_PIN && buff.state == HIGH) {
                UILib::ChangeLightMode(HIGH);
                vTaskDelay(5000 / portTICK_PERIOD_MS);
                UILib::ChangeLightMode(LOW);
                while (xQueueReceive(handle, &buff, 0));
            }
        }
    }

}

[[noreturn]] void rtc_check(void *param) {
    QueueHandle_t handle;
    RTCLib::createAndSubscribe(&handle);

    RTCDriverCallbackFrame_st buff{};
    while (true) {
        RTCLib::triggerDate();
        if (xQueueReceive(handle, &buff, 1000)) {
            UILib::DrawFillSquare(0, 0, 200, 40, ST7735_BLACK);
            String ret;
            ret = buff.date.day;
            ret += "/";
            ret += buff.date.month;
            ret += "/";
            ret += buff.date.year;
            UILib::DrawString(0, 0, ret.c_str());
            ret = "";
            ret += buff.date.hour;
            ret += " ";
            ret += buff.date.minute;
            ret += " ";
            ret += buff.date.second;
            UILib::DrawString(0, 20, ret.c_str());
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }


}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting");

    pinMode(TP_PWR_PIN, PULLUP);
    digitalWrite(TP_PWR_PIN, HIGH);

    if (DEBUG && Serial.availableForWrite()) {
        xTaskCreate(heap_check, "HeapCheckProcess", 2000, nullptr, 1, nullptr);
    }
    UILib::initDrivers();
    ButtonLib::initDrivers();
    RTCLib::initDrivers();


    UILib::ChangeLightMode(LOW);
    UILib::DrawSquare(10, 10, 10, 10, ST7735_BLUE);
    UILib::DrawString(30, 30, "OK !");


    xTaskCreate(button_check, "button_check", 2000, nullptr, 1, nullptr);
    xTaskCreate(rtc_check, "rtc_check", 2000, nullptr, 1, nullptr);
}

void loop() {

}

