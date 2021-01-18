//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_GPIODRIVER_H
#define LWOS_GPIODRIVER_H

#include "Driver.h"
#include "SubscribableDriver.h"

enum GPIOCommand_e : short {
    ADD_QUEUE,
    REMOVE_QUEUE,
    TURN_ON,
    TURN_OFF,
    TURN_ON_FOR,
    TURN_OFF_FOR,
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
