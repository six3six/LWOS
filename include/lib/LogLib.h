//
// Created by ldesp on 11/01/2021.
//

#ifndef LWOS_LOGLIB_H
#define LWOS_LOGLIB_H

#include "Lib.h"
#include "../drivers/LogDriver.h"


class LogLib : Lib {
public:
    static void log();

private:
    LogDriver *driver = new ArduinoSerial();
};

#endif //LWOS_LOGLIB_H
