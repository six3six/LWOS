//
// Created by ldesp on 19/01/2021.
//


#include "daemon/BLDaemon.h"

void BLDaemon::Run() {
    xTaskCreate(loop, "BLDaemon", 2000, nullptr, 1, &taskHandle);
}

[[noreturn]] void BLDaemon::loop(void *) {
    QueueHandle_t handle;
    ButtonLib::createAndSubscribe(&handle);
    GPIOInput_st buff{};
    UILib::changeBLMode(HIGH);
    while (true) {
        if (xQueueReceive(handle, &buff, 10000)) {
            if (buff.pin == TP_PIN_PIN && buff.state == HIGH) {
                UILib::changeBLMode(HIGH);
                vTaskDelay(5000 / portTICK_PERIOD_MS);
                UILib::changeBLMode(LOW);
                while (xQueueReceive(handle, &buff, 0));
            }
        }
    }
}
