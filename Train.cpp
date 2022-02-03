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


void Train::addStationView(const string &stationName, const Time &arrival,
                           const Time &departure) {
    StationView stationView(stationName, arrival, departure);
    stations.emplace_back(stationView);
}

int Train::numberOfStations() {
    return stations.size();
}

experimental::optional<StationView> Train::getStationViewByIndex(const int &index) {
    if(index < 0 || index >= stations.size())
        return experimental::nullopt;
    return stations.at(index);
}

string Train::getStations() {
    string output;
    for(auto i : stations){
        output += i.getStationName() + "->";
    }
    return output.substr(0, output.size() - 2);
}

bool Train::containsStation(const string &stationName) {
    for(auto &i : stations){
        if(i.getStationName() == stationName)
            return true;
    }
    return false;
}

int Train::getIndexOfStation(const string &stationName) {
    for(int i = 0; i < stations.size(); i++){
        if(stations[i].getStationName() == stationName)
            return i;
    }
    return -1;
}

bool Train::stationInWayFrom(const string &stationName1, const string &stationName2) {
    if(!containsStation(stationName1))
        return false;
    if(!containsStation(stationName2))
        return false;
    bool passFirstStation = false;
    for(auto &i : stations){
        if(i.getStationName() == stationName1)
            passFirstStation = true;
        if(i.getStationName() == stationName2){
            if(passFirstStation)
                return true;
            return false;
        }
    }
    return false;
}

experimental::optional<StationView> Train::getStationViewByName(const string &stationName) {
    for(auto &i : stations){
        if(i.getStationName() == stationName)
            return i;
    }
    return experimental::nullopt;
}
