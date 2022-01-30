#ifndef PROJECT_STATIONVIEW_H
#define PROJECT_STATIONVIEW_H

#include <experimental/optional>
#include "Time.h"

#pragma once

using namespace std;

class StationView {
    string stationName;
    experimental::optional<Time> arrival;
    experimental::optional<Time> departure;
public:
    StationView(const string &stationName, const experimental::optional<Time> &arrival,
                const experimental::optional<Time> &departure);
};

#endif //PROJECT_STATIONVIEW_H
