#include <iostream>
#include "gtest/gtest.h"
#include "../include/time_hao.h"

TEST (Timer_hao, void_constructor)
{
    Timer_hao timer;
    EXPECT_EQ(0, timer.timing_flag);
    EXPECT_DOUBLE_EQ(0, timer.seconds);
}

TEST (Timer_hao, double_constructor)
{
    Timer_hao timer(3.0);
    EXPECT_EQ(0, timer.timing_flag);
    EXPECT_DOUBLE_EQ(3.0, timer.seconds);
}

TEST (Timer_hao, equal_constructor)
{
    Timer_hao timer_init(3.0);
    Timer_hao timer = timer_init;
    EXPECT_EQ(0, timer.timing_flag);
    EXPECT_DOUBLE_EQ(3.0, timer.seconds);
}

TEST (Timer_hao, equal_assignment)
{
    Timer_hao timer_init(3.0);
    Timer_hao timer;
    timer = timer_init;
    EXPECT_EQ(0, timer.timing_flag);
    EXPECT_DOUBLE_EQ(3.0, timer.seconds);
}

TEST (Timer_hao, init)
{
    Timer_hao timer;
    timer.init();
    EXPECT_EQ(1, timer.timing_flag);
    EXPECT_DOUBLE_EQ(0.0, timer.seconds);
}

TEST (Timer_hao, end)
{
    Timer_hao timer;
    timer.init();

    clock_t start_time = clock();
    clock_t sec=1;
    clock_t end_time = sec * CLOCKS_PER_SEC + start_time;
    while(clock() != end_time);

    timer.end();

    EXPECT_EQ(0, timer.timing_flag);
    EXPECT_DOUBLE_EQ(1, timer.seconds);
}

TEST (Timer_hao, second_to_tm)
{
    double seconds=446582.0;
    struct tm timeinfo=second_to_tm(seconds);
    EXPECT_EQ(5, timeinfo.tm_mday);
    EXPECT_EQ(4, timeinfo.tm_hour);
    EXPECT_EQ(3, timeinfo.tm_min);
    EXPECT_EQ(2, timeinfo.tm_sec);
}