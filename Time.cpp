#include "Time.h"
#include "Errors.h"
#include <sstream>

Time::Time(const string &timeString) {
    putTime(timeString);
}

void Time::setHour(int h) {
    hour = h;
}

void Time::setMinute(int m) {
    minute = m;
}

bool Time::operator<(const Time &t2) const {
    if(this->hour == -999 || t2.hour == -999)
        return true;
    if(hour > t2.hour)
        return false;
    if(minute >= t2.minute)
        return false;
    return true;
}

void Time::putTime(const string &time) {
    if(time == "null"){
        hour = -999;
        minute = -999;
        return;
    }
    istringstream stream(time);
    int h;
    char del;
    int m;
    if(stream >> h >> del >> m){
        if(del != ':')
            throw WrongTime("Wrong format");
        if(h < 0 || h > 23)
            throw WrongTime("Wrong hour");
        if(m < 0 || m > 59)
            throw WrongTime("Wrong minute");
        hour = h;
        minute = m;
        return;
    }
    throw WrongTime("Wrong format");
}

string Time::getTime() const{
    if(hour == -999 && minute == -999)
        return "null";
    string m;
    if(minute < 10){
        m = '0' + to_string(minute);
    }
    else{
        m = to_string(minute);
    }
    return to_string(hour) + ':' + m;
}

Time Time::ceil() const{
    Time newTime;
    newTime.hour = this->hour;
    newTime.minute = 0;
    return newTime;
}

Time Time::floor() const {
    Time newTime;
    newTime.hour = this->hour + 1;
    newTime.minute = 0;
    return newTime;
}

bool Time::operator==(const Time &t2) const {
    return this->getTime() == t2.getTime();
}



