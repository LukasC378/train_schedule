#include "../gtest/gtest.h"

#include "../Program.h"

using namespace ::testing;

#pragma region testing route

TEST(ProgramTest1, routeNotFound){
    Program p;
    string route = p.getRouteString("Malacky", "Zohor");
    ASSERT_EQ(route, "");
}

TEST(ProgramTest2, routeNotFound){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    string route = p.getRouteString("Malacky", "XXX");
    ASSERT_EQ(route, "");
}

TEST(ProgramTest3, routeFound){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    string route = p.getRouteString("Malacky", "Zohor");
    ASSERT_EQ(route, "Malacky->Plavecký Štvrtok->Zohor");
}

TEST(ProgramTest4, routeFound){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    string route = p.getRouteString("Bratislava-Železná studienka", "Pezinok");
    ASSERT_EQ(route, "Bratislava-Železná studienka->Bratislava hl.st.->Bratislava-Vinohrady->Bratislava-Rača->Svätý Jur->Pezinok zast.->Pezinok");
}

TEST(ProgramTest5, compare){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    string route = p.getRouteString("Malacky", "Pezinok");
    ASSERT_FALSE(route == "Malacky->Plavecký Štvrtok->Zohor");
}

TEST(ProgramTest6, numberOfStations){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    vector<string> route = p.getRoute("Malacky", "Pezinok");
    ASSERT_EQ(route.size(), 13);
}

TEST(ProgramTest7, routeFound){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    string route = p.getRouteString("Malacky", "Kúty");
    ASSERT_EQ(route, "Malacky->Veľké Leváre->Závod->Moravský Svätý Ján->Sekule->Kúty");
}

TEST(ProgramTest8, routeFound){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    string route = p.getRouteString("Bratislava-Rača", "Bratislava hl.st.");
    ASSERT_EQ(route, "Bratislava-Rača->Bratislava-Vinohrady->Bratislava hl.st.");
}

TEST(ProgramTest9, numberOfStations){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    vector<string> route = p.getRoute("Kúty", "Pezinok");
    ASSERT_EQ(route.size(), 18);
}

TEST(ProgramTest10, numberOfStations){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    vector<string> route = p.getRoute("Kúty", "Pezinok zast.");
    ASSERT_EQ(route.size(), 17);
}

TEST(ProgramTest11, numberOfStations){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    vector<string> route = p.getRoute("Pezinok", "Pezinok");
    ASSERT_EQ(route.size(), 0);
}

#pragma endregion

#pragma region testing response from request

TEST(ProgramTest11, requestWrongInputStation){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "XXX", "9:52");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_TRUE(withoutTransfer.empty());
    ASSERT_TRUE(withTransfer.empty());
}

TEST(ProgramTest12, requestWrongInputStation){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Malacky", "9:52");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_TRUE(withoutTransfer.empty());
    ASSERT_TRUE(withTransfer.empty());
}

TEST(ProgramTest8, requestWrongInputTime){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Bratislava hl.st.", "29:52");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_TRUE(withoutTransfer.empty());
    ASSERT_TRUE(withTransfer.empty());
}

TEST(ProgramTest8, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Zohor", "8:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 3);
    ASSERT_EQ(withTransfer.size(), 0);
}

TEST(ProgramTest9, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Zohor", "8:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 3);
    ASSERT_EQ(withTransfer.size(), 0);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 2043);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 3011);
    ASSERT_EQ(withoutTransfer[2].getTrainId(), 3013);
}

TEST(ProgramTest10, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Kúty", "10:25");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 2);
    ASSERT_EQ(withTransfer.size(), 0);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 2012);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 2014);
}

TEST(ProgramTest11, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Kúty", "10:26");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 1);
    ASSERT_EQ(withTransfer.size(), 0);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 2014);
}

TEST(ProgramTest12, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Bratislava-Vinohrady", "14:52");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 2);
    ASSERT_EQ(withTransfer.size(), 0);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 3047);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 3025);
}

TEST(ProgramTest13, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Kúty", "Bratislava hl.st.", "10:20");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 2);
    ASSERT_EQ(withTransfer.size(), 0);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 3017);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 275);
}

TEST(ProgramTest14, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Malacky", "Trnava", "8:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 2);
    ASSERT_EQ(withTransfer.size(), 1);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 3011);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 3013);
    ASSERT_EQ(withTransfer[0].first.getTrainId(), 2043);
    ASSERT_EQ(withTransfer[0].second.getTrainId(), 705);
}

TEST(ProgramTest15, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Kúty", "Trnava", "13:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 2);
    ASSERT_EQ(withTransfer.size(), 1);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 3021);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 3023);
    ASSERT_EQ(withTransfer[0].first.getTrainId(), 277);
    ASSERT_EQ(withTransfer[0].second.getTrainId(), 609);
}

TEST(ProgramTest16, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Kúty", "Trnava", "13:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withTransfer[0].first.getTrainId(), 277);
    ASSERT_EQ(withTransfer[0].first.getTrainType(), "EC");
    ASSERT_EQ(withTransfer[0].first.getTrainName(), "METROPOLITAN");
    ASSERT_EQ(withTransfer[0].first.getInitialStation(), "Kúty");
    ASSERT_EQ(withTransfer[0].first.getEndStation(), "Bratislava hl.st.");
    ASSERT_EQ(withTransfer[0].first.getDepartureFromInitialStation(), "13:12");
    ASSERT_EQ(withTransfer[0].first.getArrivalToEndStation(), "13:54");
}

TEST(ProgramTest17, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Kúty", "Trnava", "13:00");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withTransfer[0].second.getTrainId(), 609);
    ASSERT_EQ(withTransfer[0].second.getTrainType(), "R");
    ASSERT_EQ(withTransfer[0].second.getTrainName(), "TATRAN");
    ASSERT_EQ(withTransfer[0].second.getInitialStation(), "Bratislava hl.st.");
    ASSERT_EQ(withTransfer[0].second.getEndStation(), "Trnava");
    ASSERT_EQ(withTransfer[0].second.getDepartureFromInitialStation(), "14:13");
    ASSERT_EQ(withTransfer[0].second.getArrivalToEndStation(), "14:41");
}

TEST(ProgramTest18, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Bratislava hl.st.", "Kúty", "15:40");
    vector<Response> withoutTransfer = output.first;
    vector<pair<Response ,Response>> withTransfer = output.second;
    ASSERT_EQ(withoutTransfer.size(), 3);
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 2024);
    ASSERT_EQ(withoutTransfer[1].getTrainId(), 2026);
    ASSERT_EQ(withoutTransfer[2].getTrainId(), 274);
}

TEST(ProgramTest19, requestCorrectInput){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    p.trains_init("trains2.txt");
    pair<vector<Response>, vector<pair<Response, Response>>> output;
    output = p.getRequest("Bratislava hl.st.", "Kúty", "15:40");
    vector<Response> withoutTransfer = output.first;
    ASSERT_EQ(withoutTransfer[0].getTrainId(), 2024);
    ASSERT_EQ(withoutTransfer[0].getTrainType(), "Os");
    ASSERT_EQ(withoutTransfer[0].getTrainName(), "");
    ASSERT_EQ(withoutTransfer[0].getInitialStation(), "Bratislava hl.st.");
    ASSERT_EQ(withoutTransfer[0].getEndStation(), "Kúty");
    ASSERT_EQ(withoutTransfer[0].getDepartureFromInitialStation(), "15:43");
    ASSERT_EQ(withoutTransfer[0].getArrivalToEndStation(), "16:58");
}

#pragma endregion



