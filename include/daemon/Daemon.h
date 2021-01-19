//
// Created by ldesp on 19/01/2021.
//

#ifndef LWOS_DAEMON_H
#define LWOS_DAEMON_H

#include "FreeRTOS.h"

class Daemon {
public:
    virtual void Run() {};

    void Stop() { vTaskDelete(taskHandle); };

    void Pause() { vTaskSuspend(taskHandle); };

    void Resume() { vTaskResume(taskHandle); };

protected:
    TaskHandle_t taskHandle;
};

#endif //LWOS_DAEMON_H
