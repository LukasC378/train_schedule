#ifndef PROJECT_PROGRAM_H
#define PROJECT_PROGRAM_H

#pragma once
#include <string>
#include <fstream>
#include <experimental/optional>

#include "Train.h"
#include "Station.h"
#include "Response.h"

using namespace std;

class Program {
    map<int, Train> trains;
    map<string, Station> stations;

    void train_init(const string &info);

public:
    void trains_init(const string &fileName);

    void station_init(const string &fileName);

    int numberOfStations();

    int numberOfTrains();

    Station getStation(const string &name);

    Train getTrain(const int &trainId);

    pair<vector<Response>, vector<pair<Response, Response>>> getRequest(const string &stationName1, const string &stationName2,
                                                                        const string &timeString);


    vector<string> getRoute(const string &stationName1, const string &stationName2);

    string getRouteString(const string &stationName1, const string &stationName2);

    int checkTrains(const string &stationName1, const string &stationName2, const string &timeString,
                    const set<int> &setOfTrainsWithoutTransfer, const int &firstTrainId);

};

#endif //PROJECT_PROGRAM_H
