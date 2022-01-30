#include "../gtest/gtest.h"

#include "../Program.h"

using namespace ::testing;

TEST(StationTest1, getName) {
    Station station("Malacky");
    ASSERT_EQ(station.getName(), "Malacky");
}

TEST(StationTest2, EmptyName) {
    Station station("");
    ASSERT_EQ(station.getName(), "EMPTY_NAME");
}

TEST(StationTest3, ReadFromFile){
    Program p;
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Kuty_Ba.txt");
    ASSERT_EQ(p.numberOfStations(), 13);
}

TEST(StationTest4, ReadFromFile){
    Program p;
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Ba_Trnava.txt");
    ASSERT_EQ(p.numberOfStations(), 10);
}

TEST(StationTest5, ReadFromFile){
    Program p;
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Kuty_Ba.txt");
    p.station_init("C:\\Users\\lucau\\CLionProjects\\Project\\textFiles\\track_Ba_Trnava.txt");
    ASSERT_EQ(p.numberOfStations(), 22);
}





