//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_UILIB_H
#define LWOS_UILIB_H

#include "Lib.h"
#include "../drivers/DisplayDriver.h"

#define UILIB_DEFAULT_WAIT portMAX_DELAY

class UILib : Lib {
public:
    static void initDrivers();

    static void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void
    drawFillRect(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void drawString(int32_t x, int32_t y, const char *text, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void drawCircle(int32_t x, int32_t y, int32_t r, color color, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void drawFillCircle(int32_t x, int32_t y, int32_t r, color color, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void changeFontSize(int32_t size, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void changeFontColor(color color, TickType_t wait = UILIB_DEFAULT_WAIT);

    static void clear(TickType_t wait = UILIB_DEFAULT_WAIT);

    static void changeBLMode(int32_t mode, TickType_t wait = UILIB_DEFAULT_WAIT);

private:

};

#endif //LWOS_UILIB_H
