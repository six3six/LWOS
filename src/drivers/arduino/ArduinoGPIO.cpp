//
// Created by ldesp on 16/01/2021.
//

#ifdef ARDUINO

#include "drivers/arduino/ArduinoGPIO.h"


QueueHandle_t ArduinoGPIO::queueHandle = xQueueCreate(10, sizeof(GPIOFrame_st));

struct ArduinoGPIOTaskParam {
    size_t input_nb;
    uint8_t *inputs;
};

void ArduinoGPIO::Run(const uint8_t *inputs, size_t input_nb) {
    //Task param must to be created into the heap
    auto *param = (ArduinoGPIOTaskParam *) malloc(sizeof(ArduinoGPIOTaskParam));
    size_t length = sizeof(uint8_t) * input_nb;
    *param = ArduinoGPIOTaskParam{
            input_nb,
            (uint8_t *) malloc(length)
    };
    memcpy(param->inputs, inputs, length);


    xTaskCreate(loop, "ArduinoGPIO_Driver", 5000, (void *) param, 1, nullptr);
}

QueueHandle_t ArduinoGPIO::getQueue() {
    return queueHandle;
}

void ArduinoGPIO::loop(void *param) {
    auto *args = (ArduinoGPIOTaskParam *) param;

    ArduinoGPIO gpio(args->inputs, args->input_nb);

    //Free param
    free(args->inputs);
    free(args);

    GPIOFrame_st frame{};

    while (true) {
        if (xQueueReceive(gpio.getQueue(), &frame, 10000)) {
            auto *handle = (QueueHandle_t *) frame.data;
            switch (frame.command) {
                case ADD_QUEUE:

                    gpio.subscribe(*handle);
                    frame.data = nullptr;
                    break;
                case REMOVE_QUEUE:
                    gpio.unsubscribe((QueueHandle_t *) frame.data);
                    break;
                case TURN_ON:
                    digitalWrite(*(uint8_t *) frame.data, HIGH);
                    break;
                case TURN_OFF:
                    digitalWrite(*(uint8_t *) frame.data, LOW);
                    break;
                case TURN_ON_FOR:
                    digitalWrite(((uint8_t *) frame.data)[0], HIGH);
                    vTaskDelay(((uint8_t *) frame.data)[1] / portTICK_PERIOD_MS);
                    digitalWrite(((uint8_t *) frame.data)[0], LOW);
                    break;
                case TURN_OFF_FOR:
                    digitalWrite(((uint8_t *) frame.data)[0], LOW);
                    vTaskDelay(((uint8_t *) frame.data)[1] / portTICK_PERIOD_MS);
                    digitalWrite(((uint8_t *) frame.data)[0], HIGH);
                    break;
            }

            free(frame.data);
        }
    }
}

ArduinoGPIO::ArduinoGPIO(const uint8_t inputs[], size_t input_size) {
    input_nb = input_size;
    this->inputs = (uint8_t *) malloc(input_size * sizeof(uint8_t));

    this->interrupt_args = (GPIOInterruptArg_st *) malloc(sizeof(GPIOInterruptArg_st) * input_nb);

    for (int i = 0; i < input_nb; ++i) {
        this->inputs[i] = inputs[i];
        pinMode(this->inputs[i], INPUT_PULLUP);
        this->interrupt_args[i] = GPIOInterruptArg_st{this->inputs[i], this->subscribedQueueHandle,
                                                      this->subscribedQueueMap};
        attachInterruptArg(this->inputs[i], isr, this->interrupt_args + i, CHANGE);
    }


}

ArduinoGPIO::~ArduinoGPIO() {
    for (int i = 0; i < input_nb; ++i) {
        this->inputs[i] = inputs[i];
        detachInterrupt(this->inputs[i]);
    }

    free(this->inputs);
    free(this->interrupt_args);
}

void IRAM_ATTR ArduinoGPIO::isr(void *param) {
    auto *args = (GPIOInterruptArg_st *) param;
    for (int i = 0; i < ARD_BTN_MAX_QUEUE; ++i) {
        if (args->subscribedQueueMap[i]) {
            GPIOInput_st msg{args->pin, digitalRead(args->pin)};
            xQueueSend(args->subscribedQueueHandle[i], &msg, 0);
        }
    }
}


#endif