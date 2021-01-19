//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_UILIB_H
#define LWOS_UILIB_H

#include "Lib.h"
#include "../drivers/DisplayDriver.h"


class UILib : Lib {
public:
    static void initDrivers();

    static void DrawSquare(int32_t x, int32_t y, int32_t w, int32_t h, color color);

    static void DrawFillSquare(int32_t x, int32_t y, int32_t w, int32_t h, color color);


    static void DrawString(int32_t x, int32_t y, const char *text);

    static void Clear();

    static void ChangeLightMode(int32_t mode);

private:

};

#endif //LWOS_UILIB_H
