//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_ST7735_H
#define LWOS_ST7735_H

#include "../../drivers/DisplayDriver.h"
#include "../../HW.h"
#include "Adafruit_ST7735.h"

class ST7735 : DisplayDriver {
public:
    ST7735(int width, int height);

    void init();

    void drawPixel(int x, int y, color c) override;

    int getWidth() const override;

    int getHeight() const override;

private:

    Adafruit_ST7735 screen;

    int width;
    int height;


};

#endif //LWOS_ST7735_H
