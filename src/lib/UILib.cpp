//
// Created by ldesp on 10/01/2021.
//

#include "lib/UILib.h"

void UILib::ChangeLightMode(int32_t mode) {
    size_t coordSize = sizeof(int32_t);

    int *coord = (int32_t *) malloc(coordSize);
    *coord = mode;
    DisplayFrame_st frame{DisplayCommand_e::Display_LightControl, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, 0);
}


void UILib::DrawSquare(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;

    int *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = w;
    coord[3] = h;
    coord[4] = color;
    DisplayFrame_st frame{DisplayCommand_e::Display_Rect, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::Clear(TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;
    int *coord = (int32_t *) malloc(coordSize);
    *coord = ST7735_BLACK;

    DisplayFrame_st frame{DisplayCommand_e::Display_Fill, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::DrawString(int32_t x, int32_t y, const char *text, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 2 + sizeof(char) * strlen(text) + 1;
    int *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    strcpy((char *) &coord[2], text);

    DisplayFrame_st frame{DisplayCommand_e::Display_String, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::initDrivers() {
    ST7735::Run();
}

void UILib::DrawFillSquare(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait) {

    size_t coordSize = sizeof(int32_t) * 5;

    int *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = w;
    coord[3] = h;
    coord[4] = color;
    DisplayFrame_st frame{DisplayCommand_e::Display_FillRect, coordSize, (byte *) coord};
    xQueueSend(ST7735::getQueue(), (void *) &frame, wait);
}
