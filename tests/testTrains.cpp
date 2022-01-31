#include "../gtest/gtest.h"

#include "../Program.h"
#include "../Errors.h"

using namespace ::testing;

TEST(TrainTest1, getName){
    Train train(278, "Metropolitan", "EC");
    ASSERT_EQ("Metropolitan", train.getName());
}

TEST(TrainTest2, tarinWithStationView){
    Train train(278, "Metropolitan", "EC");
    Time arrival("9:15");
    Time departure("9:17");
    train.addStationView("Bratislava", arrival, departure);
    ASSERT_EQ(train.numberOfStations(), 1);
}

TEST(TrainTest3, WrongArrivalAndDeparture){
    string ex;
    try {
        Train train(278, "Metropolitan", "EC");
        Time arrival("9:20");
        Time departure("9:17");
        train.addStationView("Bratislava", arrival, departure);
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Arrival greater than departure");
}

TEST(TrainTest3, WrongTrainType){
    string ex;
    try {
        Train train(278, "Metropolitan", "XX");
        Time arrival("9:15");
        Time departure("9:17");
        train.addStationView("Bratislava", arrival, departure);
    }
    catch (WrongTrainType &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Not valid type of train");
}

TEST(TrainTest4, ReadTestFile){
    Program p;
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\testTrains.txt)");
    ASSERT_EQ(0, p.numberOfTrains());
}

TEST(TrainTest5, ReadTestFile){
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\testTrains.txt)");
    ASSERT_EQ(1, p.numberOfTrains());
}

TEST(TrainTest6, ReadFile){
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Ba_Trnava.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\trains.txt)");
    ASSERT_EQ(39, p.numberOfTrains());
}

TEST(TrainTest7, ReadFile){
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Ba_Trnava.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\trains2.txt)");
    ASSERT_EQ(39, p.numberOfTrains());
}

TEST(TrainTest8, Stations){
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\testTrains.txt)");
    Train t;
    t = p.getTrain(2041);
    experimental::optional<StationView> s;
    s = t.getStation(0);
    ASSERT_EQ(t.getId(), 2041);
    ASSERT_EQ(t.numberOfStations(), 8);
    ASSERT_EQ(s->getStationName(), "Malacky");
    ASSERT_EQ(s->getArrival().getTime(), "null");
    ASSERT_EQ(s->getDeparture().getTime(), "7:04");
}

TEST(TrainTest9, UnknownStation){
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\testTrains.txt)");
    Train t;
    t = p.getTrain(2041);
    experimental::optional<StationView> s;
    s = t.getStation(-1);
    ASSERT_EQ(s, experimental::nullopt);
}

TEST(TrainTest9, UnknownTrain){
    string ex;
    Program p;
    p.station_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\track_Kuty_Ba.txt)");
    p.trains_init(R"(C:\Users\lucau\CLionProjects\Project\textFiles\testTrains.txt)");
    Train t;
    try {
        t = p.getTrain(0);
    }
    catch (WrongTrain &e){
        ex = e.message();
    }
    ASSERT_EQ(ex, "Unknown train 0");
}