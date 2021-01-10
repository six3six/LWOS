//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_DISPLAYDRIVER_H
#define LWOS_DISPLAYDRIVER_H

#include <stdint.h>

typedef uint16_t color;

class DisplayDriver {

public:

    virtual void drawPixel(int x, int y, color c) = 0;

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

private:


};

#endif //LWOS_DISPLAYDRIVER_H
