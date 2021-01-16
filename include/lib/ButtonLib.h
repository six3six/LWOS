//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_BUTTONLIB_H
#define LWOS_BUTTONLIB_H

#include "Lib.h"

class ButtonLib : Lib {
    void init() override;


public:

private:
    static constexpr int BTNS[2] = {TP_PIN_PIN, -1};

};

#endif //LWOS_BUTTONLIB_H
