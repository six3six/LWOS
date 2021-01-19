//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_BUTTONLIB_H
#define LWOS_BUTTONLIB_H

#include "Lib.h"
#include "drivers/arduino/ArduinoGPIO.h"

#define INPUT_NB 1


constexpr static const uint8_t declared_inputs[INPUT_NB] = {
        TP_PIN_PIN,
};


class ButtonLib : Lib {
public:
    static void initDrivers();
    static void createAndSubscribe(QueueHandle_t *handle);

private:



};

#endif //LWOS_BUTTONLIB_H
