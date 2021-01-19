//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_ST7735_H
#define LWOS_ST7735_H

#include "drivers/DisplayDriver.h"
#include "HW.h"
#include "TFT_eSPI.h"



class ST7735 : public DisplayDriver {
public:

    static QueueHandle_t getQueue();

    ST7735() : screen(TFT_eSPI()) {}

    void init(void *) override;

    void drawPixel(int x, int y, color c) override;


    void setBL(int bl_mode) const;

    int getWidth() override;

    int getHeight() override;

    static void Run();

    TFT_eSPI screen;

private:
    [[noreturn]] static void loop(void *param);

    static QueueHandle_t queueHandle;
    int BL_pin = TFT_BL;
};


#endif //LWOS_ST7735_H
