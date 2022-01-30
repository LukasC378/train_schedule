#include "Program.h"
#include "Errors.h"

void removeEndChars(string &str){
    size_t i = 0;
    while(i < str.size()){
        if(str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\b' || str[i] == '\v' || str[i] == '\0'){
            str = str.substr(0, i) + str.substr(i + 1, str.size() - i - 1);
        }
        else{
            i++;
        }
    }
}

void Program::station_init(const string &fileName) {
    string line;
    ifstream readFile;
    readFile.open(fileName);
    if(!readFile.is_open()){
        throw WrongInputFile("station file connection failed");
    }
    while (getline (readFile, line, '\r')){
        istringstream lineStream(line);
#pragma region station1
        string stationName1;
        getline(lineStream, stationName1, '/');
        removeEndChars(stationName1);
        Station station1;
        if(stations.find(stationName1) == stations.end()){
            station1 = Station(stationName1);
            stations[stationName1] = move(station1);
        }
#pragma endregion

#pragma region station2
        string stationName2;
        getline(lineStream, stationName2, '/');
        removeEndChars(stationName2);
        Station station2;
        if(stations.find(stationName2) == stations.end()){
            station2 = Station(stationName2);
            stations[stationName2] = move(station2);
        }
#pragma endregion

#pragma region adjacent
        Station *s1 = &stations.find(stationName1)->second;
        Station *s2 = &stations.find(stationName2)->second;
        s1->addAdjacent(*s2);
        s2->addAdjacent(*s1);
#pragma endregion
    }
    readFile.close();
}

void Program::train_init(const string &info) {
# pragma region declaration of variables
    string trainType;
    int trainId;
    string trainName;
    experimental::optional<Time> arrival;
    experimental::optional<Time> departure;
    Train train;
#pragma endregion

#pragma region create train
    istringstream stream(info);
    string text;
    getline(stream, text, '\n');
    string line;
    istringstream lineStream(text);
    size_t j = 0;
    try {
        while (getline(lineStream, line, '/')) {
            if (j == 0) {
                trainType = line;
            } else if (j == 1) {
                trainId = atoi(line.c_str());
            } else if (j == 2) {
                trainName = line;
            }
            j++;
        }
        train = Train(trainId, trainName, trainType);
    }
    catch (WrongTrainType &e){
        return;
    }
#pragma endregion

#pragma region push station views
    text = "";
    while(getline(stream, text, '\n')){
        string stationName;
        j = 0;
        istringstream lineStream1(text);
        while(getline(lineStream1, line, '/')){
            if(j == 0){
                if(line == "null")
                    arrival = experimental::nullopt;
                else
                    arrival->putTime(line);
            }
            else if(j == 1){
                if(line == "null")
                    departure = experimental::nullopt;
                else
                    departure->putTime(line);
            }
            else if(j == 2){
                stationName = line;
                if(stations.find(line) == stations.end()){
                    string ex = "Unknown station " + stationName;
                    throw WrongStation(ex.c_str());
                }
                try {
                    train.addStationView(stationName, arrival, departure);
                }
                catch (WrongTrainType &e) {
                    continue;
                }
            }
            j++;
        }
        //train view
        Station *station = &stations[stationName];
        station->addTrain(trainId, arrival, departure);
    }
#pragma endregion

#pragma region push train
    trains.emplace_back(train);
#pragma endregion
}

int Program::numberOfStations() {
    return stations.size();
}

int Program::numberOfTrains() {
    return trains.size();
}

void Program::trains_init(const string &fileName) {
    string line;
    string info;
    ifstream readFile;
    readFile.open(fileName);
    if(!readFile.is_open()){
        throw WrongInputFile("train file connection failed");
    }
    while (getline (readFile, line)){
        if(line == "\n" || line == "\r" || readFile.eof()){
            try {
                train_init(info);
            }
            catch(exception e){
                continue;
            }
            info = "";
        }
        else {
            removeEndChars(line);
            info += line + '\n';
        }
    }
}

void Program::getRequest() {

}

string Program::findTransport() {
    return string();
}

Station Program::getStation(const string &name) {
    if(stations.at(name).getName() == stations.end()->second.getName()){
        string ex = "Unknown station " + name;
        throw WrongStation(ex.c_str());
    }
    return stations.at(name);
}



