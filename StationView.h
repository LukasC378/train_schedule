#ifndef PROJECT_STATIONVIEW_H
#define PROJECT_STATIONVIEW_H

#include <experimental/optional>
#include "Time.h"

#pragma once

using namespace std;

class StationView {
    string stationName;
    Time arrival;
    Time departure;
public:
    StationView()= default;
    StationView(const string &stationName, const Time &arrival,
                const Time &departure);
    string getStationName(){ return stationName; };
    Time getArrival(){ return arrival; };
    Time getDeparture(){ return departure; };
};

#endif //PROJECT_STATIONVIEW_H
