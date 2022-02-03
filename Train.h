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

    string getName() const { return name; };
    int getId() const { return id; }
    string getType() const { return trainType; };

    void addStationView(const string &stationName, const Time &arrival, const Time &departure);
    int numberOfStations();
    experimental::optional<StationView> getStationViewByIndex(const int &index);
    experimental::optional<StationView> getStationViewByName(const string &stationName);
    string getStations();
    bool containsStation (const string &stationName);
    int getIndexOfStation (const string &stationName);
    bool stationInWayFrom(const string &stationName1, const string &stationName2);
};


#endif //PROJECT_TRAIN_H
