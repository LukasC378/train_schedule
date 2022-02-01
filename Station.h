#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H

#include <string>
#include <set>
#include <map>
#include <list>
#include <vector>

#pragma once
#include "StationView.h"
#include "Train.h"
#include "TrainView.h"

using namespace std;

class Station {
    string name = "EMPTY_NAME";
    map<string, vector<TrainView>> trainTable;
    vector<Station*> adjacent;

public:
    Station()= default;
    explicit Station(const string &name);
    string getName() const {return name;};
    void addAdjacent(Station *station);
    vector<Station*> getAdjacent() const { return adjacent; };
    void addTrain(const int &train, const Time &arrival, const Time &departure);
    vector<int> getTrainsInTime(const string &timeString);
};


#endif //PROJECT_STATION_H
