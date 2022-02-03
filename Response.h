#ifndef PROJECT_RESPONSE_H
#define PROJECT_RESPONSE_H

#include <string>

using namespace std;

class Response {
    int trainId = 0;
    string trainType;
    string trainName;
    string initialStation;
    string endStation;
    string departureFromInitialStation;
    string arrivalToEndStation;

public:
    Response(const int &trainId, const string &trainType, const string &trainName, const string &initialStation, const string &endStation,
             const string &departureFromInitialStation, const string &arrivalToEndStation);

    int getTrainId() const { return trainId; };
    string getTrainType() const { return trainType; };
    string getTrainName() const { return trainName; };
    string getInitialStation() const { return initialStation; };
    string getEndStation() const { return endStation; };
    string getDepartureFromInitialStation() const { return departureFromInitialStation; };
    string getArrivalToEndStation() const { return arrivalToEndStation; };
};


#endif //PROJECT_RESPONSE_H
