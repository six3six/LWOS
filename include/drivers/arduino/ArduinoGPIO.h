//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_ARDUINOGPIO_H
#define LWOS_ARDUINOGPIO_H

#include "../GPIODriver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "../SubscribableDriver.h"

class ArduinoGPIO : public GPIODriver {
public:
    explicit ArduinoGPIO(const uint8_t inputs[], size_t input_size);

    ~ArduinoGPIO();

    static QueueHandle_t getQueue();

    static void Run(const uint8_t *inputs, size_t input_nb);

    static void IRAM_ATTR isr(void *param);


private :
    [[noreturn]] static void loop(void *param);

    static QueueHandle_t queueHandle;

    uint8_t *inputs;
    GPIOInterruptArg_st *interrupt_args;
    size_t input_nb;
};

#endif //LWOS_ARDUINOGPIO_H
