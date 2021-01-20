//
// Created by ldesp on 19/01/2021.
//

#ifndef LWOS_ENERGYMANAGER_H
#define LWOS_ENERGYMANAGER_H

#include "FreeRTOS.h"
#include "lib/ButtonLib.h"
#include "DaemonRegister.h"
#include "ArduinoOTA.h"

#define INACTIVE_STEP_TIME 30000
#define TOUCHPAD_THRESHOLD 40

class EnergyManager {
public:
    static void Run();

private:
    static uint8_t step;
    [[noreturn]] static void loop(void *);

    static void touchpad_callback();
};


#endif //LWOS_ENERGYMANAGER_H
