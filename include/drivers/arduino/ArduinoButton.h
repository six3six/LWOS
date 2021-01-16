//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_ARDUINOBUTTON_H
#define LWOS_ARDUINOBUTTON_H

#include "../ButtonDriver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#define ARD_BTN_MAX_QUEUE 10
#define ARD_BTN_MAX_BTN 2


class ArduinoButton : public ButtonDriver {
public:
    static void Run(const int *btn_list);

private :

};

#endif //LWOS_ARDUINOBUTTON_H
