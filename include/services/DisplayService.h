//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_DISPLAYSERVICE_H
#define LWOS_DISPLAYSERVICE_H

#include "Service.h"
#include "../drivers/DisplayDriver.h"
#include "ScreenSizes.h"


class DisplayService : Service {
    void init() override;


private:

#if SCREEN_DRV == ST7735
    ST7735 driver = ST7735(SCREEN_WIDTH, SCREEN_HEIGHT);
#elif SCREEN_DRV == SDL2
    SDL2DRV driver = SDL2DRV(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif
};

#endif //LWOS_DISPLAYSERVICE_H
