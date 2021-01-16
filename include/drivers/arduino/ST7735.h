//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_ST7735_H
#define LWOS_ST7735_H

#include "drivers/DisplayDriver.h"
#include "HW.h"
#include "TFT_eSPI.h"

enum ST7735Command : short {
    LightControl,
    Fill,
    Rect,
    FillRect,
    Circle,
    FillCircle,
    String,
};

struct ST7735Frame {
    ST7735Command command;
    size_t length;
    byte *data;
};

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
