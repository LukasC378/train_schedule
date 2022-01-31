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

    void addStationView(const string &stationName, const Time &arrival, const Time &departure);
    string getName(){return name;};
    int getId(){return id;}
    int numberOfStations();
    experimental::optional<StationView> getStation(const int &index);
    string getStations();
};


#endif //PROJECT_TRAIN_H
