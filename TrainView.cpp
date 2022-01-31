#include "TrainView.h"
#include "Errors.h"

TrainView::TrainView(const int &trainId, const Time &arrival, const Time &departure) {
    if(arrival.getTime() != "null" && departure.getTime() != "null"){
        if(departure < arrival){
            throw WrongTime("Arrival greater than departure");
        }
    }
    this->trainId = trainId;
    this->arrival = arrival;
    this->departure = departure;
}
