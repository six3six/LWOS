//
// Created by ldesp on 19/01/2021.
//

#include "EnergyManager.h"

uint8_t EnergyManager::step = 0;
bool EnergyManager::blocked = false;

void EnergyManager::Run() {

    xTaskCreate(loop, "EnergyManager", 2000, nullptr, INT_MAX, nullptr);

}

[[noreturn]] void EnergyManager::loop(void *) {
    QueueHandle_t btnHandle;
    ButtonLib::createAndSubscribe(&btnHandle);
    step = 0;
    GPIOFrame_st frame{};
    while (true) {
        if (!xQueueReceive(btnHandle, &frame, INACTIVE_STEP_TIME / portTICK_PERIOD_MS) && !blocked) {
            if (step == 0) {
                Serial.println("[EM] Turning off screen");
                UILib::ChangeLightMode(LOW);
            } else if (step == 1) {
                Serial.println("[EM] Modem sleep mode");
                esp_bt_controller_disable();
                //esp_wifi_stop();
            }
            step++;
        } else if (step != 0) {
            //esp_wifi_start();
            Serial.println("[EM] Restarting all process");
            UILib::ChangeLightMode(HIGH);
            step = 0;
        } else {
            UILib::ChangeLightMode(HIGH);
        }

    }
}