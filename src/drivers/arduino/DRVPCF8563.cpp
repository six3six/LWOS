//
// Created by ldesp on 17/01/2021.
//

#ifdef ARDUINO

#include "drivers/arduino/DRVPCF8563.h"

QueueHandle_t PCF8563::queueHandle = xQueueCreate(10, sizeof(RTCDriverFrame_st));

void PCF8563::Run() {
    xTaskCreate(loop, "PCF8563Driver", 3000, nullptr, DRIVER_TASK_PRIORITY, nullptr);
}


void PCF8563::loop(void *param) {
    RTCDriverFrame_st frame{};

    PCF8563 pcf8563;

    RTCDriverCallbackFrame_st frm{};
    pcf8563.rtc.begin();
    pcf8563.rtc.disableAlarm();
    pcf8563.rtc.resetAlarm();
    pcf8563.rtc.disableCLK();
    pcf8563.rtc.disableTimer();
    pcf8563.rtc.check();

    while (true) {
        if (xQueueReceive(getQueue(), &frame, 1000)) {
            auto *date = (DateTime_st *) frame.data;

            switch (frame.command) {
                case RTC_ADD_QUEUE:
                    pcf8563.subscribe(*(QueueHandle_t *) frame.data);
                    break;
                case RTC_REMOVE_QUEUE:
                    pcf8563.unsubscribe(*(QueueHandle_t *) frame.data);
                    break;
                case RTC_SET_ALARM:
                    pcf8563.rtc.setAlarm(date->hour, date->minute, date->day, date->weekday);
                    break;
                case RTC_GET_ALARM:
                    frm = RTCDriverCallbackFrame_st{
                            true,
                            pcf8563.getAlarmDateTime(),
                    };
                    pcf8563.sendMessage(&frm);
                    break;
                case RTC_ENABLE_ALARM:
                    pcf8563.rtc.enableAlarm();
                    break;
                case RTC_CLEAR_ALARM:
                    pcf8563.rtc.disableAlarm();
                    break;
                case RTC_SET_DATE:
                    pcf8563.rtc.setDateTime(date->year, date->month, date->day, date->hour, date->minute, date->second);
                    break;
                case RTC_GET_DATE:
                    frm = RTCDriverCallbackFrame_st{
                            false,
                            pcf8563.getDateTime(),
                    };
                    pcf8563.sendMessage(&frm);
                    break;
                case RTC_SYNC_TO_SYSTEM:
                    pcf8563.rtc.syncToSystem();
            }
        }
    }

}


QueueHandle_t PCF8563::getQueue() {
    return queueHandle;
}

DateTime_st PCF8563::getDateTime() {
    RTC_Date date = rtc.getDateTime();
    return DateTime_st{
            date.year,
            date.month,
            date.day,
            date.hour,
            date.minute,
            date.second,
            (Weekday_e) rtc.getDayOfWeek(date.day, date.month, date.year),
    };
}

DateTime_st PCF8563::getAlarmDateTime() {
    RTC_Alarm date = rtc.getAlarm();
    return DateTime_st{
            0,
            0,
            date.day,
            date.hour,
            date.minute,
            0,
            (Weekday_e) date.weekday,
    };
}

#endif


