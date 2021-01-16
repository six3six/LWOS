//
// Created by ldesp on 10/01/2021.
//

#include "lib/UILib.h"

void UILib::ChangeLightMode(int32_t mode) {
    size_t coordSize = sizeof(int32_t);

    int *coord = (int32_t *) malloc(coordSize);
    *coord = mode;
    ST7735Frame frame{ST7735Command::LightControl, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, 0);
}


void UILib::DrawSquare(int32_t x, int32_t y, int32_t w, int32_t h, color color) {
    size_t coordSize = sizeof(int32_t) * 5;

    int *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = w;
    coord[3] = h;
    coord[4] = color;
    ST7735Frame frame{ST7735Command::Rect, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, 0);
}

void UILib::Clear() {
    size_t coordSize = sizeof(int32_t) * 5;
    int *coord = (int32_t *) malloc(coordSize);
    *coord = ST7735_BLACK;

    ST7735Frame frame{ST7735Command::Fill, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, 0);
}

void UILib::DrawString(int32_t x, int32_t y, const char *text) {
    size_t coordSize = sizeof(int32_t) * 2 + sizeof(char) * strlen(text) + 1;
    int *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    strcpy((char *) &coord[2], text);

    ST7735Frame frame{ST7735Command::String, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, 0);
}
