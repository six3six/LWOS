//
// Created by ldesp on 11/01/2021.
//

#ifndef LWOS_ARDUINOSERIAL_H
#define LWOS_ARDUINOSERIAL_H

#include "drivers/LogDriver.h"
#include "Arduino.h"

class ArduinoSerial : public LogDriver {
public:
    ArduinoSerial() = default;

    void print(char c) override;

    void print(int i) override;

    void print(const char *s) override;

private:
    HardwareSerial serial = Serial;


};

#endif //LWOS_ARDUINOSERIAL_H
