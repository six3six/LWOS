//
// Created by ldesp on 18/01/2021.
//

#ifndef LWOS_RTCLIB_H
#define LWOS_RTCLIB_H

#include "Lib.h"
#include "drivers/arduino/DRVPCF8563.h"


class RTCLib : public Lib {
public:
    static void initDrivers();

    static void createAndSubscribe(QueueHandle_t *handle);

    static void triggerDate();

    static void triggerAlarm();

    static void setDate(DateTime_st date);

    static void setAlarm(DateTime_st date);

    static void enableAlarm();

    static void clearAlarm();

    static void syncToSystem();
    static void syncFromSystem();

    static String int2number(int val, int nb);

    static String weekdayToString(Weekday_e);


private:



};

#endif //LWOS_RTCLIB_H
