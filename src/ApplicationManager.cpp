//
// Created by ldesp on 26/01/2021.
//

#include "ApplicationManager.h"

Application *ApplicationManager::currentApp = nullptr;

void ApplicationManager::PauseCurrentApp() {
    currentApp->Pause();
}

void ApplicationManager::ResumeCurrentApp() {
    currentApp->Resume();
}

void ApplicationManager::StartApp(Application *app) {
    app->Run();
    if (currentApp != nullptr) {
        currentApp->Stop();
    }
    currentApp = app;
}
