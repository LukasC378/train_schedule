#include "../gtest/gtest.h"

#include "../Time.h"
#include "../Errors.h"

using namespace ::testing;

TEST(TimeTest1, WrongFormat) {
    string ex;
    try {
        Time time;
        time.putTime("12");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong format");
}

TEST(TimeTest2, WrongFormat) {
    string ex;
    try {
        Time time;
        time.putTime("12-15");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong format");
}

TEST(TimeTest3, HourOutOfLimit) {
    string ex;
    try {
        Time time;
        time.putTime("24:00");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong hour");
}

TEST(TimeTest4, HourOutOfLimit) {
    string ex;
    try {
        Time time;
        time.putTime("-5:10");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong hour");
}

TEST(TimeTest5, MinuteOutOfLimit) {
    string ex;
    try {
        Time time;
        time.putTime("10:68");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong minute");
}

TEST(TimeTest6, MinuteOutOfLimit) {
    string ex;
    try {
        Time time;
        time.putTime("10:-80");
    }
    catch (WrongTime &e) {
        ex = e.message();
    }
    ASSERT_EQ(ex, "Wrong minute");
}

TEST(TimeTest7, CorrectTime) {
    Time time;
    time.putTime("5:10");
    ASSERT_EQ(time.getTime(), "5:10");
}

TEST(TimeTest8, Compare){
    Time cas1;
    Time cas2;
    cas1.putTime("5:10");
    cas2.putTime("5:10");
    ASSERT_FALSE(cas1 < cas2);
}

TEST(TimeTest9, Compare){
    Time cas1;
    Time cas2;
    cas1.putTime("5:10");
    cas2.putTime("5:11");
    ASSERT_TRUE(cas1 < cas2);
}

TEST(TimeTest10, Compare){
    Time cas1;
    Time cas2;
    cas1.putTime("5:10");
    cas2.putTime("5:10");
    ASSERT_EQ(cas1, cas2);
}
