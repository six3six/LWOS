//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_DISPLAYDRIVER_H
#define LWOS_DISPLAYDRIVER_H

#include <cstdint>
#include "Driver.h"

typedef uint32_t color;

enum DisplayCommand_e : short {
    Display_LightControl,
    Display_Fill,
    Display_Rect,
    Display_FillRect,
    Display_Circle,
    Display_FillCircle,
    Display_String,
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
