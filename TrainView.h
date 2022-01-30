#ifndef PROJECT_TRAINVIEW_H
#define PROJECT_TRAINVIEW_H

#pragma once

#include <experimental/optional>
#include "Time.h"

class TrainView {
    int trainId;
    experimental::optional<Time> arrival;
    experimental::optional<Time> departure;
public:
    TrainView(const int &trainId, const experimental::optional<Time> &arrival, const experimental::optional<Time> &departure);
};


#endif //PROJECT_TRAINVIEW_H
