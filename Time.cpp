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
    if(hour > t2.hour)
        return false;
    if(minute >= t2.minute)
        return false;
    return true;
}

void Time::putTime(const string &time) {
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

string Time::getTime() {
    return to_string(hour) + ':' + to_string(minute);
}

Time Time::ceil() const{
    Time newTime;
    newTime.hour = this->hour;
    newTime.minute = 0;
    return newTime;
}


