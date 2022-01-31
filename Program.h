#ifndef PROJECT_PROGRAM_H
#define PROJECT_PROGRAM_H

#pragma once
#include <string>
#include <fstream>
#include <experimental/optional>

#include "Train.h"
#include "Station.h"

using namespace std;

class Program {
    map<int, Train> trains;
    map<string, Station> stations;
public:
    void trains_init(const string &fileName);

    void train_init(const string &info);

    void station_init(const string &fileName);

    int numberOfStations();

    int numberOfTrains();

    Station* getStation(const string &name);

    Train getTrain(const int &trainId);

    void getRequest();

    string findTransport();

    vector<string> getRoute(const string &stationName1, const string &stationName2);

    string getRouteString(const string &stationName1, const string &stationName2);

};

#endif //PROJECT_PROGRAM_H
