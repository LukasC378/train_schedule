#include "../gtest/gtest.h"

#include "../Application.h"

using namespace ::testing;

TEST(ApplicationTest1, notFound){
    Application app;
    string s = app.Find("Malacky", "Malacky", "9:00");
    ASSERT_EQ(s, "");
}

TEST(ApplicationTest2, Found){
    Application app;
    string s = app.Find("Malacky", "Zohor", "10:00");
    ASSERT_EQ(s, "Without transfer\nOs 3015\n10:35 Malacky\n10:48 Zohor\n\nOs 3017\n11:35 Malacky\n11:48 Zohor");
}

TEST(ApplicationTest3, Found){
    Application app;
    string s = app.Find("Malacky", "Trnava", "8:00");
    string s1 = "Without transfer\nOs 3011\n8:35 Malacky\n10:05 Trnava\n\nOs 3013\n9:35 Malacky\n11:05 Trnava\n\n";
    s1 += "With transfer\nOs 2043\n8:04 Malacky\n8:42 Bratislava hl.st.\n\nRR 705 POVAŽAN\n9:13 Bratislava hl.st.\n9:41 Trnava";
    ASSERT_EQ(s, s1);
}
