#ifdef ARDUINO

#include "drivers/arduino/ST7735.h"

QueueHandle_t ST7735::queueHandle = xQueueCreate(10, sizeof(ST7735Frame));

QueueHandle_t ST7735::getQueue() {
    return ST7735::queueHandle;
}

void ST7735::Run() {
    ST7735::queueHandle = xQueueCreate(10, sizeof(ST7735Frame));
    xTaskCreate(ST7735::loop, "ST7735_Driver", 30000, nullptr, 1, nullptr);
}

void ST7735::loop(void *param) {
    ST7735 st7735 = ST7735();
    st7735.init(nullptr);
    ST7735Frame frame{};
    while (true) {
        if (xQueueReceive(ST7735::queueHandle, &frame, 1000)) {
            auto *intdata = (int32_t *) frame.data;
            switch (frame.command) {
                case LightControl:
                    st7735.setBL((int) frame.data[0]);
                    break;
                case Rect:
                    st7735.screen.drawRect(intdata[0], intdata[1], intdata[2], intdata[3], intdata[4]);
                    break;
                case FillRect:
                    st7735.screen.fillRect(intdata[0], intdata[1], intdata[2], intdata[3], intdata[4]);
                    break;
                case Fill:
                    st7735.screen.fillScreen(intdata[0]);
                    break;
                case Circle:
                    st7735.screen.drawCircle(intdata[0], intdata[1], intdata[2], intdata[3]);
                    break;
                case FillCircle:
                    st7735.screen.fillCircle(intdata[0], intdata[1], intdata[2], intdata[3]);
                    break;
                case String:
                    st7735.screen.drawString((char *) &intdata[2], intdata[0], intdata[1]);
                    break;
            }
            free(frame.data);
        }
    }
}


void ST7735::init(void *param) {
    screen.init();
    screen.setRotation(3);
    screen.fillScreen(TFT_BLACK);
    screen.setTextColor(TFT_WHITE);
    screen.setCursor(0, 0);
    setBL(LOW);
    screen.setTextSize(2);
}

void ST7735::setBL(int bl_mode) const {
    digitalWrite(BL_pin, bl_mode);
}

int ST7735::getWidth() {
    return screen.width();
}

int ST7735::getHeight() {
    return screen.height();
}

void ST7735::drawPixel(int x, int y, color c) {
    screen.drawPixel(x, y, 1);
}

#endif