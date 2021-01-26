//
// Created by ldesp on 26/01/2021.
//

#ifndef LWOS_APPLICATION_H
#define LWOS_APPLICATION_H

#include "FreeRTOS.h"

class Application {
public:

    virtual void Run() {};

    void Stop() { vTaskDelete(taskHandle); };

    void Pause() { vTaskSuspend(taskHandle); };

    void Resume() { vTaskResume(taskHandle); };

protected:
    TaskHandle_t taskHandle{};
};

#endif //LWOS_APPLICATION_H
