#include "arch/x86/SDL2.h"

#ifdef x86

SDL2DRV::SDL2DRV(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        exit(-1);
    }
    SDL_Window *pWindow = SDL_CreateWindow("WatchViewer", SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           width,
                                           height,
                                           SDL_WINDOW_SHOWN);

    if (!pWindow) {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }
}

void SDL2DRV::init() {

}

int SDL2DRV::getWidth() const {
    return this->width;
}

int SDL2DRV::getHeight() const {
    return this->height;
}

void SDL2DRV::drawPixel(int x, int y, color c) {
}
#endif