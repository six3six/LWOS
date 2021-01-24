//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_DISPLAYDRIVER_H
#define LWOS_DISPLAYDRIVER_H

#include <cstdint>
#include "Driver.h"

typedef uint32_t color;

#define DD_BLACK        (color) TFT_BLACK
#define DD_NAVY         (color) TFT_NAVY
#define DD_DARKGREEN    (color) TFT_DARKGREEN
#define DD_DARKCYAN     (color) TFT_DARKCYAN
#define DD_MAROON       (color) TFT_MAROON
#define DD_PURPLE       (color) TFT_PURPLE
#define DD_OLIVE        (color) TFT_OLIVE
#define DD_LIGHTGREY    (color) TFT_LIGHTGREY
#define DD_DARKGREY     (color) TFT_DARKGREY
#define DD_BLUE         (color) TFT_BLUE
#define DD_GREEN        (color) TFT_GREEN
#define DD_CYAN         (color) TFT_CYAN
#define DD_RED          (color) TFT_RED
#define DD_MAGENTA      (color) TFT_MAGENTA
#define DD_YELLOW       (color) TFT_YELLOW
#define DD_WHITE        (color) TFT_WHITE
#define DD_ORANGE       (color) TFT_ORANGE
#define DD_GREENYELLOW  (color) TFT_GREENYELLOW
#define DD_PINK         (color) TFT_PINK
#define DD_BROWN        (color) TFT_BROWN
#define DD_GOLD         (color) TFT_GOLD
#define DD_SILVER       (color) TFT_SILVER
#define DD_SKYBLUE      (color) TFT_SKYBLUE
#define DD_VIOLET       (color) TFT_VIOLET


enum DisplayCommand_e : short {
    Display_LightControl,
    Display_Fill,
    Display_Rect,
    Display_FillRect,
    Display_Circle,
    Display_FillCircle,
    Display_String,
    Display_FontSize,
    Display_FontColor,
};

struct DisplayFrame_st {
    DisplayCommand_e command;
    size_t length;
    void *data;
};

class DisplayDriver : public Driver {

public:
    virtual void init(void *) {};

    virtual void drawPixel(int x, int y, color c) {};

    virtual int getWidth() { return 0; };

    virtual int getHeight() { return 0; };

private:


};

#endif //LWOS_DISPLAYDRIVER_H
