#include "Train.h"
#include "Errors.h"

void checkType(const string &type){
    if(type != "EC" && type != "IC" && type != "R" && type != "RR" && type != "Rex" && type != "Os")
        throw WrongTrainType("Not valid type of train");
}

Train::Train(const int &id, const string &name, const string &trainType) {
    checkType(trainType);

    this->id = id;
    this->name = name;
    this->trainType = trainType;
}


void Train::addStationView(const string &stationName, const experimental::optional<Time> &arrival,
                           const experimental::optional<Time> &departure) {
    StationView stationView(stationName, arrival, departure);
    stations.emplace_back(stationView);
}

int Train::numberOfStations() {
    return stations.size();
}
