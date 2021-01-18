//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_BUTTONLIB_H
#define LWOS_BUTTONLIB_H

#include "Lib.h"
#include "drivers/arduino/ArduinoGPIO.h"

#define INPUT_NB 3
constexpr static const uint8_t declared_inputs[INPUT_NB] = {
        TP_PIN_PIN,
        IMU_INT_PIN,
        RTC_INT_PIN,
};
class ButtonLib : Lib {


public:

    void init();

    static void createAndSubscribe(QueueHandle_t *handle);

private:


};

#endif //LWOS_BUTTONLIB_H
