#include "Application.h"

Application::Application() {
    program.station_init("track_Kuty_Ba.txt");
    program.station_init("track_Ba_Trnava.txt");
    program.trains_init("trains.txt");
    program.trains_init("trains2.txt");
}

string Application::Find(const string &stationName1, const string &stationName2, const string &timeString) {
    string output;
    pair<vector<Response>, vector<pair<Response, Response>>> transports = program.getRequest(stationName1, stationName2, timeString);
    if(transports.first.empty() && transports.second.empty())
        return output;
    if(!transports.first.empty()){
        output += "Without transfer\n";
        for(auto &i : transports.first){
            output += i.getTrainType() + ' ' + to_string(i.getTrainId());
            if(!i.getTrainName().empty())
                output += ' ' + i.getTrainName();
            output += '\n';
            output += i.getDepartureFromInitialStation() + ' ' + i.getInitialStation() + '\n';
            output += i.getArrivalToEndStation() + ' ' + i.getEndStation() + '\n';
            output += '\n';
        }
    }
    if(!transports.second.empty()){
        output += "With transfer\n";
        for(auto &i : transports.second){
            output += i.first.getTrainType() + ' ' + to_string(i.first.getTrainId());
            if(!i.first.getTrainName().empty())
                output += ' ' + i.first.getTrainName();
            output += '\n';
            output += i.first.getDepartureFromInitialStation() + ' ' + i.first.getInitialStation() + '\n';
            output += i.first.getArrivalToEndStation() + ' ' + i.first.getEndStation() + '\n';
            output += '\n';
            output += i.second.getTrainType() + ' ' + to_string(i.second.getTrainId());
            if(!i.second.getTrainName().empty())
                output += ' ' + i.second.getTrainName();
            output += '\n';
            output += i.second.getDepartureFromInitialStation() + ' ' + i.second.getInitialStation() + '\n';
            output += i.second.getArrivalToEndStation() + ' ' + i.second.getEndStation() + '\n';
            output += '\n';
        }
    }
    return output.substr(0, output.size() - 2);
}
