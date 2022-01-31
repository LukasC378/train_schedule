#include "StationView.h"
#include "Errors.h"

StationView::StationView(const string &stationName, const Time &arrival,
                         const Time &departure) {
    if(arrival.getTime() != "null" && departure.getTime() != "null"){
        if(departure < arrival){
            throw WrongTime("Arrival greater than departure");
        }
    }
    this->stationName = stationName;
    this->arrival = arrival;
    this->departure = departure;
}
