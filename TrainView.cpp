#include "TrainView.h"
#include "Errors.h"

TrainView::TrainView(const int &trainId, const experimental::optional<Time> &arrival, const experimental::optional<Time> &departure) {
    if(arrival != experimental::nullopt && departure != experimental::nullopt){
        if(departure < arrival){
            throw WrongTime("Arrival greater than departure");
        }
    }
    this->trainId = trainId;
    this->arrival = arrival;
    this->departure = departure;
}
