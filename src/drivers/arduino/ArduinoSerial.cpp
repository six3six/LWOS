//
// Created by ldesp on 11/01/2021.
//
#ifdef ARDUINO

#include "drivers/arduino/ArduinoSerial.h"



void ArduinoSerial::print(const char *s) {
    serial.print(s);
}

void ArduinoSerial::print(char c) {
    serial.print(c);
}

void ArduinoSerial::print(int i) {
    serial.print(i);
}
#endif