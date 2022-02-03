#include "../gtest/gtest.h"

#include "../Program.h"
#include "../Errors.h"

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
    p.station_init("track_Kuty_Ba.txt");
    ASSERT_EQ(p.numberOfStations(), 13);
}

TEST(StationTest4, ReadFromFile){
    Program p;
    p.station_init("track_Ba_Trnava.txt");
    ASSERT_EQ(p.numberOfStations(), 10);
}

TEST(StationTest5, ReadFromFile){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    ASSERT_EQ(p.numberOfStations(), 22);
}

TEST(StationTest6, UnknownStation){
    string ex;
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    try {
        p.getStation("XXX");
    }
    catch(WrongStation &e){
        ex = e.message();
    }
    ASSERT_EQ("Unknown station XXX", ex);
}

TEST(StationTest7, TrainsInStationByTime){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    Station s;
    s = p.getStation("Malacky");
    vector<int> v = s.getTrainsInTime("14:23");
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0], 3023);
    ASSERT_EQ(v[1], 3047);
    ASSERT_EQ(v[2], 3025);
}

TEST(StationTest8, TrainsByTime){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    Station s;
    s = p.getStation("Malacky");
    vector<int> v = s.getTrainsInTime("14:23");
    ASSERT_EQ(v[0], 3023);
    Train t = p.getTrain(v[0]);
    experimental::optional<StationView> s1;
    s1 = t.getStationViewByIndex(5);
    ASSERT_EQ(s1->getStationName(), "Malacky");
    ASSERT_EQ(s1->getArrival().getTime(), "14:33");
    ASSERT_EQ(s1->getDeparture().getTime(), "14:35");
}

TEST(StationTest9, TrainsByTime){
    Program p;
    p.station_init("track_Kuty_Ba.txt");
    p.station_init("track_Ba_Trnava.txt");
    p.trains_init("trains.txt");
    Station s;
    s = p.getStation("Bratislava hl.st.");
    vector<int> v = s.getTrainsInTime("9:00");
    ASSERT_EQ(v[1], 705);
}

TEST(StationTest10, TrainsByTime){
Program p;
p.station_init("track_Kuty_Ba.txt");
p.station_init("track_Ba_Trnava.txt");
p.trains_init("trains.txt");
Station s;
s = p.getStation("Trnava");
vector<int> v = s.getTrainsInTime("9:00");
ASSERT_EQ(v[0], 3009);
}





