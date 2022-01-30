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
    map<Time, vector<TrainView>> trainTable;
    vector<Station> adjacent;

public:
    Station()= default;
    explicit Station(const string &name);
    string getName(){return name;};
    void addAdjacent(const Station &station);
    void addTrain(const int &train, const experimental::optional<Time> &arrival, const experimental::optional<Time> &departure);
};


#endif //PROJECT_STATION_H
