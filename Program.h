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
    static map<int, Train> trains;
    static map<string, Station> stations;

    void train_init(const string &info);

public:
    void trains_init(const string &fileName);

    void station_init(const string &fileName);

    int numberOfStations();

    int numberOfTrains();

    static Station getStation(const string &name);

    static Train getTrain(const int &trainId);

    void getRequest(const string &stationName1, const string &stationName2, const string &timeString);

    string findTransport();

    vector<string> getRoute(const string &stationName1, const string &stationName2);

    string getRouteString(const string &stationName1, const string &stationName2);

};

#endif //PROJECT_PROGRAM_H
