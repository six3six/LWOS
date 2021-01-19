//
// Created by ldesp on 18/01/2021.
//

#include "drivers/SubscribableDriver.h"

bool SubscribableDriver::subscribe(QueueHandle_t handle) {
    for (int i = 0; i < MAX_QUEUE; ++i) {
        if (!subscribedQueueMap[i]) {
            subscribedQueueMap[i] = true;
            subscribedQueueHandle[i] = handle;
            return true;
        }
    }
    return false;
}

void SubscribableDriver::unsubscribe(QueueHandle_t handle) {
    for (int i = 0; i < MAX_QUEUE; ++i) {
        if (handle == subscribedQueueHandle[i]) {
            subscribedQueueMap[i] = false;
        }
    }
}

SubscribableDriver::SubscribableDriver() {
    for (bool &i : this->subscribedQueueMap) {
        i = false;
    }
}

void SubscribableDriver::sendMessage(void *param) {
    for (int i = 0; i < MAX_QUEUE; ++i) {
        if (this->subscribedQueueMap[i]) {
            xQueueSend(this->subscribedQueueHandle[i], param, 0);
        }
    }
}
