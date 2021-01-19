//
// Created by ldesp on 19/01/2021.
//

#include "DaemonRegister.h"

Daemon *DaemonRegister::daemonList[MAX_DAEMON];
bool DaemonRegister::daemonListMap[MAX_DAEMON];

bool DaemonRegister::AddDaemon(Daemon *daemon) {
    for (int i = 0; i < MAX_DAEMON; ++i) {
        if (!daemonListMap[i]) {
            daemonListMap[i] = true;
            daemonList[i] = daemon;
            return true;
        }
    }

    return false;
}

bool DaemonRegister::RemoveDaemon(Daemon *daemon) {
    for (int i = 0; i < MAX_DAEMON; ++i) {
        if (daemonList[i] == daemon) {
            daemonListMap[i] = false;
            return true;
        }
    }

    return false;
}

void DaemonRegister::PauseDaemons() {
    for (int i = 0; i < MAX_DAEMON; ++i) {
        if (daemonListMap[i]) {
            daemonList[i]->Pause();
        }
    }
}

void DaemonRegister::ResumeDaemons() {
    for (int i = 0; i < MAX_DAEMON; ++i) {
        if (daemonListMap[i]) {
            daemonList[i]->Resume();
        }
    }
}

void DaemonRegister::StartDaemons() {
    for (int i = 0; i < MAX_DAEMON; ++i) {
        if (daemonListMap[i]) {
            daemonList[i]->Run();
        }
    }
}
