#ifndef PROJECT_TRAIN_H
#define PROJECT_TRAIN_H

#pragma once
#include "StationView.h"
#include "Transport.h"

#include <string>

using namespace std;

class Train : Transport {
    string name = "";
    string trainType;
    vector<StationView> stations;
public:
    Train(const int &id, const string &name, const string &trainType);
    Train(){};

    void addStationView(const string &stationName, const experimental::optional<Time> &arrival, const experimental::optional<Time> &departure);
    string getName(){return name;};
    int getId(){return id;}
    int numberOfStations();
};


#endif //PROJECT_TRAIN_H
