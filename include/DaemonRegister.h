//
// Created by ldesp on 19/01/2021.
//

#ifndef LWOS_DAEMONREGISTER_H
#define LWOS_DAEMONREGISTER_H

#include "daemon/Daemon.h"

#define MAX_DAEMON 10

class DaemonRegister {
public:
    static bool AddDaemon(Daemon *daemon);

    static bool RemoveDaemon(Daemon *daemon);

    static void PauseDaemons();

    static void ResumeDaemons();

    static void StartDaemons();

private:
    static Daemon *daemonList[MAX_DAEMON];
    static bool daemonListMap[MAX_DAEMON];
};


#endif //LWOS_DAEMONREGISTER_H
