//
// Created by ldesp on 10/01/2021.
//

#ifndef LWOS_SERVICE_H
#define LWOS_SERVICE_H

#include "Arch.h"
#include "HW.h"

class Service {
public:
    virtual void init() = 0;
};

#endif //LWOS_SERVICE_H
