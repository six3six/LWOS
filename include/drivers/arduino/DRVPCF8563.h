//
// Created by ldesp on 17/01/2021.
//

#ifndef LWOS_DRVPCF8563_H
#define LWOS_DRVPCF8563_H

#include "../RTCDriver.h"
#include "pcf8563.h"


class PCF8563 : public RTCDriver {
public:
    static void Run();

    static QueueHandle_t getQueue();

private:
    [[noreturn]] static void loop(void *param);

    DateTime_st getDateTime();

    DateTime_st getAlarmDateTime();

    static QueueHandle_t queueHandle;

    PCF8563_Class rtc;

};

#endif //LWOS_DRVPCF8563_H
