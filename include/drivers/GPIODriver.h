//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_GPIODRIVER_H
#define LWOS_GPIODRIVER_H

#include "Driver.h"
#include "SubscribableDriver.h"

enum GPIOCommand_e : short {
    GPIO_ADD_QUEUE,
    GPIO_REMOVE_QUEUE,
    GPIO_TURN_ON,
    GPIO_TURN_OFF,
    GPIO_TURN_ON_FOR,
    GPIO_TURN_OFF_FOR,
};

struct GPIOFrame_st {
    GPIOCommand_e command;
    void *data;
};

struct GPIOInput_st {
    uint8_t pin;
    int state;
};

struct GPIOInterruptArg_st {
    uint8_t pin;
    QueueHandle_t *subscribedQueueHandle;
    bool *subscribedQueueMap;
};


class GPIODriver : public Driver, public SubscribableDriver {

};

#endif //LWOS_GPIODRIVER_H
