//
// Created by ldesp on 23/01/2021.
//

#ifndef LWOS_OTALIB_H
#define LWOS_OTALIB_H

#include "Lib.h"
#include "ArduinoOTA.h"
#include <EnergyManager.h>
#include "UILib.h"
#include "DaemonRegister.h"

class OTALib : public Lib {
public:
    static void initDrivers();

private:
    static void progress(unsigned int progress, unsigned int total);
};

#endif //LWOS_OTALIB_H
