//
// Created by ldesp on 11/01/2021.
//

#ifndef LWOS_LOGDRIVER_H
#define LWOS_LOGDRIVER_H

#include "HW.h"
#include "Driver.h"

class LogDriver  : public Driver {
public:
    virtual void print(const char *s) {};

    virtual void print(char c) {};

    virtual void print(int i) {};
};

#endif //LWOS_LOGDRIVER_H
