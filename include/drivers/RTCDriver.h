//
// Created by ldesp on 16/01/2021.
//

#ifndef LWOS_RTCDRIVER_H
#define LWOS_RTCDRIVER_H

#include "Driver.h"
#include "SubscribableDriver.h"

enum Weekday_e : uint8_t {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
};

struct DateTime_st {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    Weekday_e weekday;
};

enum RTCDriverCommand_e {
    RTC_ADD_QUEUE,
    RTC_REMOVE_QUEUE,
    RTC_SET_ALARM,
    RTC_GET_ALARM,
    RTC_ENABLE_ALARM,
    RTC_CLEAR_ALARM,
    RTC_SET_DATE,
    RTC_GET_DATE,
};


struct RTCDriverFrame_st {
    RTCDriverCommand_e command;
    void *data;
};

struct RTCDriverCallbackFrame_st {
    bool alarm;
    DateTime_st date;
};


class RTCDriver : public Driver, public SubscribableDriver {

public:
    RTCDriver() : Driver(), SubscribableDriver() {};


private:


};

#endif //LWOS_RTCDRIVER_H
