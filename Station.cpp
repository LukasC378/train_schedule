#include "Station.h"
#include "Errors.h"

Station::Station(const string &name) {
    if(name != "") {
        this->name = name;
        return;
    }
    this->name = "EMPTY_NAME";
}

void Station::addTrain(const int &train, const Time &arrival, const Time &departure) {
    Time keyTime;
    if(arrival.getTime() != "null")
        keyTime = arrival.ceil();
    else
        keyTime = departure.ceil();
    TrainView trainView(train, arrival, departure);
    if(!trainTable.contains(keyTime.getTime())){
        vector<TrainView> list;
        list.emplace_back(trainView);
        trainTable[keyTime.getTime()] = list;
        return;
    }
    trainTable[keyTime.getTime()].emplace_back(trainView);
}

void Station::addAdjacent(Station *station) {
    this->adjacent.push_back(station);
}

vector<int> Station::getTrainsInTime(const string &timeString) {
    vector<int> trains;
    Time t;
    try {
       t.putTime(timeString);
    }
    catch(WrongTime &e){
        return trains;
    }
    Time t1 = t.ceil();
    Time t2 = t.floor();
    if(trainTable.contains(t1.getTime())) {
        for (auto &i: trainTable[t1.getTime()]) {
            if (t < i.getDeparture())
                trains.push_back(i.getId());
        }
    }
    if(trainTable.contains(t2.getTime())) {
        for (auto &i: trainTable[t2.getTime()]) {
            trains.push_back(i.getId());
        }
    }
    return trains;
}

