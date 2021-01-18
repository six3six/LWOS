//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_ARCH_H
#define LWOS_ARCH_H

#ifdef ESP32

#include "drivers/arduino/ST7735.h"
#include "drivers/arduino/ArduinoSerial.h"
#include "drivers/arduino/ArduinoGPIO.h"

#endif
#ifdef x86

#include "drivers/SDL2.h"
#include "drivers/Console.h"

#endif


#endif //LWOS_ARCH_H
