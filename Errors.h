#ifndef PROJECT_ERRORS_H
#define PROJECT_ERRORS_H

class WrongInput : public std::exception {
    std::string text;
public:
    WrongInput(const char *v) { text = v; };
    std::string message() const { return text; };
};

class WrongTime : public WrongInput {
public:
    WrongTime(const char *v) : WrongInput(v) {};
};

class WrongTrainType : public WrongInput{
public:
    WrongTrainType(const char *v) : WrongInput(v) {};
};

class WrongInputFile : public WrongInput{
public:
    WrongInputFile(const char *v) : WrongInput(v) {};
};

class WrongStation : public WrongInput{
public:
    WrongStation(const char *v) : WrongInput(v) {};
};

#endif //PROJECT_ERRORS_H
