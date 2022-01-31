#ifndef PROJECT_TIME_H
#define PROJECT_TIME_H

#pragma once
#include <string>

using namespace std;

class Time {
    int hour = 0;
    int minute = 0;

public:
    Time(){};
    Time(const string &timeString);
    void putTime(const string &time);

    int getHour() const{return hour;};
    void setHour(int h);

    int getMinute() const{return minute;};
    void setMinute(int m);

    bool operator<(const Time &t2) const;

    string getTime() const;
    Time ceil() const;
};


#endif //PROJECT_TIME_H
