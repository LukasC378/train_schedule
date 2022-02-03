#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

#include "Program.h"

class Application {

    Program program;

public:
    Application();
    string Find(const string &stationName1, const string &stationName2, const string &timeString);
};


#endif //PROJECT_APPLICATION_H
