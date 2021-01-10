//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_ARCH_H
#define LWOS_ARCH_H

#ifdef ESP32

#include "arch/esp32/ST7735.h"

#endif
#ifdef x86

#include "arch/x86/SDL2.h"

#endif


#endif //LWOS_ARCH_H
