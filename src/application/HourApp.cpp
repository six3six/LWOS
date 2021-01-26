//
// Created by ldesp on 26/01/2021.
//

#include "application/HourApp.h"


void HourApp::Run() {
    xTaskCreate(loop, "HourApp", 2000, nullptr, 1, &taskHandle);
}

void HourApp::loop(void *) {
    QueueHandle_t handle;
    RTCLib::createAndSubscribe(&handle);

    tm current_date{};
    tm prev_date{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    timeval tv{};
    timezone tz{};

    UILib::changeFontColor(DD_BLUE);
    UILib::drawString(20, 20, "/", 1000);
    UILib::drawString(50, 20, "/", 1000);
    UILib::changeFontColor(DD_RED);
    UILib::drawString(20, 40, ":", 1000);
    UILib::drawString(50, 40, ":", 1000);

    pinMode(CHARGE_PIN, INPUT_PULLUP);

    int voltage_take = 0;
    float voltage_mean = 0;


    // int i = 0;
    while (true) {
        /*
        if (i % 10 == 0) {
            RTCLib::syncToSystem();
        }
        i++;
        RTCLib::triggerDate();
        RTCDriverCallbackFrame_st cb{};
        if (xQueueReceive(handle, &cb, 100 / portTICK_PERIOD_MS)) {
            if (cb.lowVoltage) {
                UILib::DrawString(110, 110, "LV");
            } else {
                UILib::drawString(110, 0, "HV");
            }
        }*/
        gettimeofday(&tv, &tz);
        current_date = *localtime(&tv.tv_sec);
        UILib::changeFontColor(DD_BLUE);
        if (prev_date.tm_wday != current_date.tm_wday) {
            UILib::drawFillRect(0, 0, 210, 20, DD_BLACK);
            UILib::drawString(0, 0, RTCLib::weekdayToString((Weekday_e) current_date.tm_wday).c_str());
        }

        if (prev_date.tm_mday != current_date.tm_mday) {
            UILib::drawFillRect(0, 20, 23, 20, DD_BLACK);
            UILib::drawString(0, 20, RTCLib::int2number(current_date.tm_mday, 2).c_str());
        }

        if (prev_date.tm_mon != current_date.tm_mon) {
            UILib::drawFillRect(30, 20, 23, 20, DD_BLACK);
            UILib::drawString(30, 20, RTCLib::int2number(current_date.tm_mon + 1, 2).c_str());
        }

        if (prev_date.tm_year != current_date.tm_year) {
            UILib::drawFillRect(60, 20, 50, 20, DD_BLACK);
            UILib::drawString(60, 20, RTCLib::int2number(current_date.tm_year + 1900, 4).c_str());
        }
        UILib::changeFontColor(DD_RED);
        if (prev_date.tm_hour != current_date.tm_hour) {
            UILib::drawFillRect(0, 40, 23, 20, DD_BLACK);
            UILib::drawString(0, 40, RTCLib::int2number(current_date.tm_hour, 2).c_str());
        }

        if (prev_date.tm_min != current_date.tm_min) {
            UILib::drawFillRect(30, 40, 23, 20, DD_BLACK);
            UILib::drawString(30, 40, RTCLib::int2number(current_date.tm_min, 2).c_str());
        }

        if (prev_date.tm_sec != current_date.tm_sec) {
            UILib::drawFillRect(60, 40, 23, 20, DD_BLACK);
            UILib::drawString(60, 40, RTCLib::int2number(current_date.tm_sec, 2).c_str());
        }
        if (voltage_take < 3) {
            voltage_take++;
            voltage_mean += EnergyManager::getBatteryVoltage();
        } else {
            UILib::changeFontColor(DD_WHITE);
            UILib::drawFillRect(90, 40, 60, 20, DD_BLACK);
            UILib::drawString(90, 40,
                              (RTCLib::int2number(EnergyManager::getBatteryPercent(voltage_mean / (float) voltage_take),
                                                  2) +
                               "%").c_str());
            if (digitalRead(CHARGE_PIN) == LOW) {
                UILib::drawString(140, 40, "C");
            }
            voltage_take = 0;
            voltage_mean = 0;
        }


        gettimeofday(&tv, &tz);
        prev_date = *localtime(&tv.tv_sec);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}

