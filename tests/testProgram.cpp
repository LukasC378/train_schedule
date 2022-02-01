#include "../gtest/gtest.h"

#include "../Program.h"
#include "../Errors.h"

using namespace ::testing;

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

