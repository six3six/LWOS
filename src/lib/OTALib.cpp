//
// Created by ldesp on 23/01/2021.
//


#include "lib/OTALib.h"

void OTALib::initDrivers() {
    ArduinoOTA.begin();

    ArduinoOTA.onStart([]() {
        EnergyManager::lock();
        DaemonRegister::PauseDaemons();
        UILib::changeBLMode(HIGH);
    });


    ArduinoOTA.onProgress(progress);
    ArduinoOTA.onError([](ota_error_t error) {
        ESP.restart();
    });

    xTaskCreate([](void *) {
        while (true) {
            ArduinoOTA.handle();
            vTaskDelay(500);
        }
    }, "OTAHandle", 2000, nullptr, 2, nullptr);
}

void OTALib::progress(unsigned int progress, unsigned int total) {
    unsigned int percent = (progress / (total / 100));
    String str_percent = String(percent) + "%";

    UILib::clear(portMAX_DELAY);
    UILib::drawString(0, 0, "Updating", portMAX_DELAY);
    UILib::drawString(0, 30, str_percent.c_str(), portMAX_DELAY);
}
