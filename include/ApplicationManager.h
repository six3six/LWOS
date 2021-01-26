//
// Created by ldesp on 26/01/2021.
//

#ifndef LWOS_APPLICATIONMANAGER_H
#define LWOS_APPLICATIONMANAGER_H

#include "application/Application.h"

class ApplicationManager {
public:
    static void PauseCurrentApp();

    static void ResumeCurrentApp();

    static void StartApp(Application *app);

private:
    static Application *currentApp;
};

#endif //LWOS_APPLICATIONMANAGER_H
