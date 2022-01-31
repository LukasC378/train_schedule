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
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Kuty_Ba.txt");
    string route = p.getRouteString("Malacky", "XXX");
    ASSERT_EQ(route, "");
}

TEST(ProgramTest3, routeFound){
    Program p;
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Kuty_Ba.txt");
    string route = p.getRouteString("Malacky", "Zohor");
    ASSERT_EQ(route, "Malacky->Plavecký Štvrtok->Zohor");
}

