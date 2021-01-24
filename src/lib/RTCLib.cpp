//
// Created by ldesp on 18/01/2021.
//

#include "lib/RTCLib.h"

void RTCLib::initDrivers() {
    PCF8563::Run();
}

void RTCLib::createAndSubscribe(QueueHandle_t *handle) {
    *handle = xQueueCreate(5, sizeof(RTCDriverCallbackFrame_st));
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_ADD_QUEUE,
            handle
    };
    xQueueSend(PCF8563::getQueue(), &frame, 10000);
}

void RTCLib::setDate(DateTime_st date) {

    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_SET_DATE,
            &date
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

void RTCLib::setAlarm(DateTime_st date) {

    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_SET_ALARM,
            &date
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

void RTCLib::triggerDate() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_GET_DATE,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

void RTCLib::triggerAlarm() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_GET_ALARM,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

void RTCLib::enableAlarm() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_ENABLE_ALARM,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

void RTCLib::clearAlarm() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_CLEAR_ALARM,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}

String RTCLib::int2number(int val, int nb) {
    String ret;
    for (int i = nb - 1; i > 0; --i) {
        if (val < pow(10, i)) {
            ret += "0";
        }
    }

    ret += val;
    return ret;
}

String RTCLib::weekdayToString(Weekday_e weekday) {
    switch (weekday) {

        case MONDAY:
            return "Monday";
        case TUESDAY:
            return "Tuesday";
        case WEDNESDAY:
            return "Wednesday";
        case THURSDAY:
            return "Thursday";
        case FRIDAY:
            return "Friday";
        case SATURDAY:
            return "Saturday";
        case SUNDAY:
            return "Sunday";
    }
    return "";
}

void RTCLib::syncToSystem() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_SYNC_TO_SYSTEM,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}


void RTCLib::syncFromSystem() {
    RTCDriverFrame_st frame{
            RTCDriverCommand_e::RTC_SYNC_FROM_SYSTEM,
            nullptr
    };
    xQueueSend(PCF8563::getQueue(), (void *) &frame, 10000);
}
