//
// Created by ldesp on 19/01/2021.
//

#ifndef LWOS_ENERGYMANAGER_H
#define LWOS_ENERGYMANAGER_H



#include "FreeRTOS.h"
#include "lib/ButtonLib.h"
#include "DaemonRegister.h"
#include "ArduinoOTA.h"
#include "lib/UILib.h"
#include "driver/adc.h"

#include <config.h>

#include <esp_bt.h>
#include <esp_wifi.h>

#define INACTIVE_STEP_TIME 20000
#define TOUCHPAD_THRESHOLD 40

#define EnMag_TAG "EnergyManager"

class EnergyManager {
public:
    static void Run();

    static void lock() { blocked = true; };

    static void unlock() { blocked = false; };

private:
    [[noreturn]] static void loop(void *);

    static uint8_t step;
    static bool blocked;
};


#endif //LWOS_ENERGYMANAGER_H
