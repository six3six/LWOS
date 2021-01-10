//
// Created by ldesp on 10/01/2021.
//
#ifdef x86
#ifndef LWOS_SDL2_H
#define LWOS_SDL2_H

#include "../../drivers/DisplayDriver.h"
#include "../../HW.h"
#include <SDL2/SDL.h>
#include <cstdio>

class SDL2DRV : DisplayDriver {
public:
    SDL2DRV(int width, int height);

    void init();

    void drawPixel(int x, int y, color c) override;

    int getWidth() const override;

    int getHeight() const override;

private:

    int width;
    int height;


};

#endif //LWOS_ST7735_H
#endif