//
// Created by ldesp on 26/01/2021.
//

#ifndef LWOS_HOURAPP_H
#define LWOS_HOURAPP_H

#include "Application.h"
#include "lib/UILib.h"
#include "lib/RTCLib.h"
#include "time.h"
#include "EnergyManager.h"

class HourApp : public Application {
public:
    void Run() override;

private:
    [[noreturn]] static void loop(void *);
};

#endif //LWOS_HOURAPP_H
