//
// Created by ldesp on 16/01/2021.
//

#include "lib/ButtonLib.h"


void ButtonLib::init() {
    ArduinoGPIO::Run(declared_inputs, INPUT_NB);

}

void ButtonLib::createAndSubscribe(QueueHandle_t *handle) {
    *handle = xQueueCreate(10, sizeof(GPIOInput_st));
    const GPIOFrame_st frame{
            GPIOCommand_e::ADD_QUEUE,
            (byte *) handle
    };
    xQueueSend(ArduinoGPIO::getQueue(), (void *) &frame, 10000);
}
