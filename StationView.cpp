#include "StationView.h"
#include "Errors.h"

StationView::StationView(const string &stationName, const experimental::optional<Time> &arrival,
                         const experimental::optional<Time> &departure) {
    if(arrival != experimental::nullopt && departure != experimental::nullopt){
        if(departure < arrival){
            throw WrongTime("Arrival greater than departure");
        }
    }
    this->stationName = stationName;
    this->arrival = arrival;
    this->departure = departure;
}
