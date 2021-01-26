//
// Created by ldesp on 10/01/2021.
//

#include "lib/UILib.h"

void UILib::initDrivers() {
    ST7735::Run();
}

void UILib::clear(TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;
    auto *coord = (int32_t *) malloc(coordSize);
    *coord = DD_BLACK;

    DisplayFrame_st frame{DisplayCommand_e::Display_Fill, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::changeBLMode(int32_t mode, TickType_t wait) {
    size_t coordSize = sizeof(int32_t);

    auto *coord = (int32_t *) malloc(coordSize);
    *coord = mode;

    DisplayFrame_st frame{DisplayCommand_e::Display_LightControl, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}


void UILib::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;

    auto *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = w;
    coord[3] = h;
    coord[4] = color;

    DisplayFrame_st frame{DisplayCommand_e::Display_Rect, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}


void UILib::drawString(int32_t x, int32_t y, const char *text, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 2 + sizeof(char) * strlen(text) + 1;
    auto *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    strcpy((char *) &coord[2], text);

    DisplayFrame_st frame{DisplayCommand_e::Display_String, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}


void UILib::drawFillRect(int32_t x, int32_t y, int32_t w, int32_t h, color color, TickType_t wait) {

    size_t coordSize = sizeof(int32_t) * 5;

    auto *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = w;
    coord[3] = h;
    coord[4] = color;

    DisplayFrame_st frame{DisplayCommand_e::Display_FillRect, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::drawCircle(int32_t x, int32_t y, int32_t r, color color, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;

    auto *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = r;
    coord[4] = color;

    DisplayFrame_st frame{DisplayCommand_e::Display_Circle, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::drawFillCircle(int32_t x, int32_t y, int32_t r, color color, TickType_t wait) {
    size_t coordSize = sizeof(int32_t) * 5;

    auto *coord = (int32_t *) malloc(coordSize);
    coord[0] = x;
    coord[1] = y;
    coord[2] = r;
    coord[4] = color;

    DisplayFrame_st frame{DisplayCommand_e::Display_FillCircle, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::changeFontSize(int32_t size, TickType_t wait) {
    size_t coordSize = sizeof(int32_t);

    auto *coord = (int32_t *) malloc(coordSize);
    *coord = size;

    DisplayFrame_st frame{DisplayCommand_e::Display_FontSize, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}

void UILib::changeFontColor(color color, TickType_t wait) {
    size_t coordSize = sizeof(int32_t);

    auto *coord = (int32_t *) malloc(coordSize);
    *coord = color;

    DisplayFrame_st frame{DisplayCommand_e::Display_FontColor, coordSize, (byte *) coord};
    xQueueSendToBack(ST7735::getQueue(), (void *) &frame, wait);
}
