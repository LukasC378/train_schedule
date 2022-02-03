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
        s1->addAdjacent(s2);
        s2->addAdjacent(s1);
#pragma endregion
    }
    readFile.close();
}

void Program::train_init(const string &info) {
# pragma region declaration of variables
    string trainType;
    int trainId;
    string trainName;
    Time arrival;
    Time departure;
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
                    arrival.putTime(line);
            }
            else if(j == 1){
                    departure.putTime(line);
            }
            else if(j == 2){
                stationName = line;
                if(stations.find(line) == stations.end()){
                    string ex = "Unknown station " + stationName;
                    throw WrongStation(ex.c_str());
                }
                if(arrival.getTime() == "null" && departure.getTime() == "null"){
                    throw WrongTime("arrival and departure are null");
                }
                if(arrival.getTime() == "null")
                    arrival = departure;
                if(departure.getTime() == "null")
                    departure = arrival;
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
    trains[trainId] = train;
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
        if(line == "\n" || line == "\r" || line == "" || readFile.eof()){
            try {
                train_init(info);
            }
            catch(exception &e){
                continue;
            }
            info = "";
        }
        else {
            removeEndChars(line);
            info += line + '\n';
        }
    }
    try {
        if(info != "")
            train_init(info);
    }
    catch(exception &e){}
}

Station Program::getStation(const string &name) {
    if(stations.find(name) == stations.end()){
        string ex = "Unknown station " + name;
        throw WrongStation(ex.c_str());
    }
    return stations.at(name);
}

Train Program::getTrain(const int &trainId) {
    if(trains.find(trainId)->second.getId() == trains.end()->second.getId()){
        string ex = "Unknown train " + to_string(trainId);
        throw WrongTrain(ex.c_str());
    }
    return trains.at(trainId);
}

bool backtracking(const Station station1, const Station station2, set<string> &visited, vector<string> &route){
    route.push_back(station1.getName());
    if(station1.getName() == station2.getName()){
        return true;
    }
    visited.emplace(station1.getName());
    for(auto &i : station1.getAdjacent()){
        if(!visited.contains(i->getName())){
            bool found = backtracking(*i, station2, visited, route);
            if(found) return true;
        }
    }
    visited.erase(station1.getName());
    route.pop_back();
    return false;
}

vector<string> Program::getRoute(const string &stationName1, const string &stationName2) {
#pragma region init stations
    vector<string> route;
    if(stationName1 == stationName2)
        return route;

    Station station1;
    Station station2;
    try{
        station1 = getStation(stationName1);
        station2 = getStation(stationName2);
    }
    catch (WrongStation){
        return route;
    }
#pragma endregion

#pragma region backtracking
    set<string> visited;
    backtracking(station1, station2, visited, route);
#pragma endregion

    return route;
}

string Program::getRouteString(const string &stationName1, const string &stationName2) {
    string output;
    vector<string> vector = getRoute(stationName1, stationName2);
    for(auto &i : vector){
        output += i + "->";
    }
    return output.substr(0, output.size() - 2);
}

int Program::checkTrains(const string &stationName1, const string &stationName2, const string &timeString,
                         const set<int> &setOfTrainsWithoutTransfer, const int &firstTrainId){
    Station station1 = Program::getStation(stationName1);
    vector<int> trainsId = station1.getTrainsInTime(timeString);
    Time maxTime("23:59");
    int correctTrainId = 0;
    for(auto &id : trainsId) {
        if(id == firstTrainId)
            continue;
        if(setOfTrainsWithoutTransfer.contains(id))
            continue;
        Train t = Program::getTrain(id);
        if (!t.stationInWayFrom(stationName1, stationName2))
            continue;
        experimental::optional<StationView> s = t.getStationViewByName(stationName2);
        if(s == experimental::nullopt)
            continue;
        if(s->getDeparture() < maxTime){
            correctTrainId = t.getId();
            maxTime = s->getDeparture();
        }
    }
    return correctTrainId;
}

pair<vector<Response>, vector<pair<Response, Response>>> Program::getRequest(const string &stationName1, const string &stationName2, const string &timeString) {

#pragma region declaration/check
    vector<Response> trainsWithoutTransfer;
    vector<pair<Response, Response>> trainsWithTransfer;
    vector<string> route = getRoute(stationName1, stationName2);

#pragma region chcek input data
    //chcek route;
    if(route.empty()) {
        pair<vector<Response>, vector<pair<Response, Response>>> output{trainsWithoutTransfer, trainsWithTransfer};
        return output;
    }
    //check time
    try{
        Time t(timeString);
    }
    catch (WrongTime &e){
        pair<vector<Response>, vector<pair<Response, Response>>> output{trainsWithoutTransfer, trainsWithTransfer};
        return output;
    }
#pragma endregion

    Station station1 = getStation(stationName1);
    vector<int> trainsId = station1.getTrainsInTime(timeString);
    set<int> setOfTrainsWithoutTransfer;
#pragma endregion

#pragma region without transfer
    for(auto &trainId : trainsId){
        Train train = getTrain(trainId);
        if(train.stationInWayFrom(stationName1, stationName2)){
            experimental::optional<StationView> stationView1;
            experimental::optional<StationView> stationView2;
            stationView1 = train.getStationViewByName(stationName1);
            stationView2 = train.getStationViewByName(stationName2);
            if(stationView1 == experimental::nullopt || stationView2 == experimental::nullopt)
                continue;
            Response response(trainId, train.getType(), train.getName(), stationName1, stationName2,
                              stationView1->getDeparture().getTime(), stationView2->getArrival().getTime());
            trainsWithoutTransfer.push_back(response);
            setOfTrainsWithoutTransfer.emplace(train.getId());
        }
    }
#pragma endregion

#pragma region with one transfer
    for(auto &firstTrainId : trainsId){
        Train firstTrain = getTrain(firstTrainId);
        if(setOfTrainsWithoutTransfer.contains(firstTrainId))
            continue;
        int indexOfCurrentStation = firstTrain.getIndexOfStation(stationName1);
        //if current station in train
        if (indexOfCurrentStation == -1)
            continue;
        int indexOfNextStation = indexOfCurrentStation + 1;
        experimental::optional<StationView> nextStationView = firstTrain.getStationViewByIndex(indexOfNextStation);
        //if train has next station
        while(true) {
            if (nextStationView == experimental::nullopt)
                break;
            //next station of train in route
            string nextStationName = nextStationView->getStationName();
            if (find(route.begin(), route.end(), nextStationName) == route.end())
                break;
            // check trains in next station
            Time keyTime;
            if(nextStationView->getDeparture().getTime() == "null")
                keyTime = nextStationView->getArrival();
            else
                keyTime = nextStationView->getDeparture();
            int secondTrainId = checkTrains(nextStationName, stationName2, keyTime.getTime(),
                                            setOfTrainsWithoutTransfer, firstTrainId);
            if (secondTrainId != 0) {
#pragma region response1
                experimental::optional<StationView> stationView1;
                experimental::optional<StationView> stationView2;
                stationView1 = firstTrain.getStationViewByName(stationName1);
                stationView2 = firstTrain.getStationViewByName(nextStationName);
                if(stationView1 == experimental::nullopt || stationView2 == experimental::nullopt)
                    continue;
                Response response1(firstTrainId, firstTrain.getType(), firstTrain.getName(), stationName1, nextStationName,
                                   stationView1->getDeparture().getTime(), stationView2->getArrival().getTime());
#pragma endregion

#pragma region response2
                Train secondTrain;
                secondTrain = getTrain(secondTrainId);
                stationView1 = secondTrain.getStationViewByName(nextStationName);
                stationView2 = secondTrain.getStationViewByName(stationName2);
                if(stationView1 == experimental::nullopt || stationView2 == experimental::nullopt)
                    continue;
                Response response2(secondTrainId, secondTrain.getType(), secondTrain.getName(), nextStationName, stationName2,
                                   stationView1->getDeparture().getTime(), stationView2->getArrival().getTime());
#pragma endregion
                pair<Response, Response> p{response1, response2};
                trainsWithTransfer.push_back(p);
                break;
            }
            indexOfNextStation++;
            nextStationView = firstTrain.getStationViewByIndex(indexOfNextStation);
        }
    }
#pragma endregion

    pair<vector<Response>, vector<pair<Response, Response>>> output{trainsWithoutTransfer, trainsWithTransfer};
    return output;
}








