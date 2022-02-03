#include "Response.h"


Response::Response(const int &trainId, const string &trainType, const string &trainName, const string &initialStation,
                   const string &endStation, const string &departureFromInitialStation,
                   const string &arrivalToEndStation) {
    this->trainId = trainId;
    this->trainType = trainType;
    this->trainName = trainName;
    this->initialStation = initialStation;
    this->endStation = endStation;
    this->departureFromInitialStation = departureFromInitialStation;
    this->arrivalToEndStation = arrivalToEndStation;
}
