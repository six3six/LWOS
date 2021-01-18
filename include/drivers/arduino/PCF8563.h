//
// Created by ldesp on 17/01/2021.
//

#ifndef LWOS_PCF8563_H
#define LWOS_PCF8563_H

#include "../RTCDriver.h"
#include "Rtc_Pcf8563.h"


class PCF8563 : public RTCDriver {
public:
    static void Run(const uint8_t *inputs, size_t input_nb);

    static QueueHandle_t getQueue();

private:
    [[noreturn]] static void loop(void *param);



    static QueueHandle_t queueHandle;




};

#endif //LWOS_PCF8563_H
