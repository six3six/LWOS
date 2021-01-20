//
// Created by ldesp on 19/01/2021.
//

#include "EnergyManager.h"

uint8_t EnergyManager::step = 0;

void EnergyManager::Run() {
    xTaskCreate(loop, "EnergyManager", 2000, nullptr, INT_MAX, nullptr);

}

[[noreturn]] void EnergyManager::loop(void *) {
    QueueHandle_t btnHandle;
    ButtonLib::createAndSubscribe(&btnHandle);
    step = 0;
    GPIOFrame_st frame{};
    while (true) {
        if (!xQueueReceive(btnHandle, &frame, INACTIVE_STEP_TIME / portTICK_PERIOD_MS)) {
            if (step == 0) {
                Serial.println("Pause daemons");
                DaemonRegister::PauseDaemons();
            } else if (step == 1) {
                Serial.println("deep sleep on");
                esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
                esp_deep_sleep_start();
            }
            step++;
        } else if (step != 0) {
            Serial.println("Resume daemons");
            DaemonRegister::ResumeDaemons();
            step = 0;
        }

    }
}