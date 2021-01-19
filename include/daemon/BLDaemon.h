//
// Created by ldesp on 19/01/2021.
//

#ifndef LWOS_BLDAEMON_H
#define LWOS_BLDAEMON_H

#include "Daemon.h"
#include "lib/UILib.h"
#include <lib/ButtonLib.h>

class BLDaemon : public Daemon {
public:
    void Run() override;

private:
    [[noreturn]] static void loop(void *);
};

#endif //LWOS_BLDAEMON_H
