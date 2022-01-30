#ifndef PROJECT_TRANSPORT_H
#define PROJECT_TRANSPORT_H


#pragma once
#include <vector>
#include <sstream>
#include "StationView.h"

using namespace std;

enum TypesOfTransport {TRAIN, BUS};

class Transport {
protected:
    int id;
    TypesOfTransport transportType;
    vector<StationView> stations;
};


#endif //PROJECT_TRANSPORT_H
