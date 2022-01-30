#include "Station.h"

Station::Station(const string &name) {
    if(name != "") {
        this->name = name;
        return;
    }
    this->name = "EMPTY_NAME";
}

void Station::addTrain(const int &train, const experimental::optional<Time> &arrival, const experimental::optional<Time> &departure) {
    Time keyTime;
    if(arrival != experimental::nullopt)
        keyTime = arrival->ceil();
    else
        keyTime = departure->ceil();
    TrainView trainView(train, arrival, departure);
    if(trainTable.find(keyTime) == trainTable.end()){
        vector<TrainView> list;
        list.emplace_back(trainView);
        trainTable[keyTime] = list;
        return;
    }
    trainTable[keyTime].emplace_back(trainView);
}

void Station::addAdjacent(const Station &station) {
    this->adjacent.push_back(station);
}

