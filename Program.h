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
    vector<Train> trains;
    map<string, Station> stations;
public:
    void train_init(const string &info);
    void station_init(const string &fileName);
    int numberOfStations();
    int numberOfTrains();
    Station getStation(const string &name);
    void trains_init(const string &fileName);
    void getRequest();
    string findTransport();
};


#endif //PROJECT_PROGRAM_H
