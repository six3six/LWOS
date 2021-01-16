#include "lib/UILib.h"
#include "lib/ButtonLib.h"

#define DEBUG true

static UILib uiLib = UILib();
static ButtonLib btnLib = ButtonLib();

[[noreturn]] void heap_check(void *param) {
    while (true) {
        Serial.print(F("Heap used : "));
        Serial.print(ESP.getHeapSize() - ESP.getFreeHeap());
        Serial.print("/");
        Serial.print(ESP.getHeapSize());
        Serial.print(" - ");
        Serial.print(((double) (ESP.getHeapSize() - ESP.getFreeHeap()) / (double) ESP.getHeapSize()) * (double) 100);
        Serial.print("%");
        Serial.println();
        vTaskDelay(10000);
    }

}


void setup() {
    Serial.begin(115200);
    Serial.printf("Test");
    uiLib.init();

    if (DEBUG && Serial.availableForWrite()) {
        xTaskCreate(heap_check, "HeapCheckProcess", 2000, nullptr, 1, nullptr);
    }

    UILib::DrawSquare(10, 10, 10, 10, ST7735_BLUE);
    UILib::DrawString(30, 30, "OK !");


}

void loop() {
// write your code here

    UILib::ChangeLightMode(HIGH);
    delay(1000);
    UILib::ChangeLightMode(LOW);
    delay(1000);
}

