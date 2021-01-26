//
// Created by ldesp on 10/01/2021.
//

#include "WString.h"
#include "esp_log.h"


#define TP_PIN_PIN          33
#define TP_PWR_PIN          25

#define I2C_SDA_PIN         21
#define I2C_SCL_PIN         22

#define I2C1_SDA_PIN        15
#define I2C1_SCL_PIN        13

/*
* For IO4, it is the on-board LED light when external bracelet module
* MAX30208 temperature module: Interrupt pin
* MAX30102 Heart rate module : Interrupt pin
* Motor Module: Drive Pin
* */
#define MAX30208_INT_PIN    4
#define MAX30208_SLAVE_ADDRESS      0x50

#define LED_PIN             4       //motor pin

#define IMU_INT_PIN         38
#define RTC_INT_PIN         34

#define BATT_ADC_PIN        35
#define VBUS_ADC_PIN        36
#define CHARGE_PIN          32

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 80