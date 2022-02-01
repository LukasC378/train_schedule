#ifndef PROJECT_TRAINVIEW_H
#define PROJECT_TRAINVIEW_H

#pragma once

#include <experimental/optional>
#include "Time.h"

class TrainView {
    int trainId;
    Time arrival;
    Time departure;
public:
    TrainView(const int &trainId, const Time &arrival, const Time &departure);
    int getId() const { return trainId; };
    Time getArrival() const { return arrival; };
    Time getDeparture() const { return departure; };
};


#endif //PROJECT_TRAINVIEW_H
