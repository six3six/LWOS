#include "arch/esp32/ST7735.h"

ST7735::ST7735(int width, int height) : screen(
        Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST)) {
    this->width = width;
    this->height = height;
}

void ST7735::init() {
    this->screen.initR(INITR_BLACKTAB);
    this->screen.fillScreen(ST7735_BLACK);
}

int ST7735::getWidth() const {
    return this->width;
}

int ST7735::getHeight() const {
    return this->height;
}

void ST7735::drawPixel(int x, int y, color c) {
    this->screen.drawPixel(x, y, 1);
}