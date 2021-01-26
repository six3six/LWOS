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
                ESP_LOGI(EnMag_TAG, "Turning off screen");
                UILib::changeBLMode(LOW);

                ESP_LOGI(EnMag_TAG, "Reduce CPU frequency to 80Mhz");
                setCpuFrequencyMhz(80);
            } else if (step == 1) {
                ESP_LOGI(EnMag_TAG, "Pause app");
                ApplicationManager::PauseCurrentApp();
                ESP_LOGI(EnMag_TAG, "Modem off");
                esp_bt_controller_disable();
                WiFi.disconnect();
                WiFi.mode(WIFI_OFF);
                esp_wifi_stop();
                esp_bt_controller_disable();
                btStop();
            }
            step++;
        } else if (step != 0) {
            ESP_LOGI(EnMag_TAG, "Resume app");
            ApplicationManager::ResumeCurrentApp();
            ESP_LOGI(EnMag_TAG, "Restart WiFi");
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            ESP_LOGI(EnMag_TAG, "Increase CPU frequency to 240 Mhz");
            setCpuFrequencyMhz(240);
            ESP_LOGI(EnMag_TAG, "Turning on screen");
            UILib::changeBLMode(HIGH);
            step = 0;
        } else {
            UILib::changeBLMode(HIGH);
        }

    }
}

#define BATTERY_MIN_V 2.9
#define BATTERY_MAX_V 3.7

int vref = 1100;

float EnergyManager::getBatteryVoltage() {
    uint16_t v = analogRead(BATT_ADC_PIN);
    return ((float) v / 4095.0f) * 2.0f * 3.3f * (1100 / 1000.0f);
}

uint8_t EnergyManager::getBatteryPercent() {
    float volts = getBatteryVoltage();
    return getBatteryPercent(volts);
}

uint8_t EnergyManager::getBatteryPercent(float volts) {
    uint8_t percentage = (volts - BATTERY_MIN_V) * 100 / (BATTERY_MAX_V - BATTERY_MIN_V);
    if (percentage > 100) {
        percentage = 100;
    }
    if (percentage < 0) {
        percentage = 0;
    }
    return percentage;
}