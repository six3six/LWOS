//
// Created by ldesp on 18/01/2021.
//

#ifndef LWOS_SUBSCRIBABLEDRIVER_H
#define LWOS_SUBSCRIBABLEDRIVER_H

#include "FreeRTOS.h"
#include "Driver.h"

#define MAX_QUEUE 10

class SubscribableDriver {

public:
    SubscribableDriver();

    bool subscribe(QueueHandle_t handle);

    void unsubscribe(QueueHandle_t handle);

    void sendMessage(void *);

protected:
    QueueHandle_t subscribedQueueHandle[MAX_QUEUE]{};
    bool subscribedQueueMap[MAX_QUEUE]{};
};

#endif //LWOS_SUBSCRIBABLEDRIVER_H
