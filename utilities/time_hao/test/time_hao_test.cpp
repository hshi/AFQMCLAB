#include <iostream>
#include "../../test_hao/gtest_custom.h"
#include "../include/time_hao.h"

struct tm transferSecondToTm (double seconds);

TEST (Timer_hao, void_constructor)
{
    TimerHao timer;
    EXPECT_EQ( 0, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( 0, timer.returnSeconds() );
}

TEST (Timer_hao, double_constructor)
{
    TimerHao timer(3.0);
    EXPECT_EQ( 0, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.returnSeconds() );
}

TEST (Timer_hao, equal_constructor)
{
    TimerHao timer_init(3.0);
    TimerHao timer = timer_init;
    EXPECT_EQ( 0, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.returnSeconds() );
}

TEST (Timer_hao, equal_assignment)
{
    TimerHao timer_init(3.0);
    TimerHao timer;
    timer = timer_init;
    EXPECT_EQ( 0, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.returnSeconds() );
}

TEST (Timer_hao, init)
{
    TimerHao timer;
    timer.init();
    EXPECT_EQ( 1, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( 0.0, timer.returnSeconds() );
}

TEST (Timer_hao, end)
{
    TimerHao timer;
    timer.init();

    clock_t start_time = clock();
    double sec=0.02;
    clock_t end_time = sec * CLOCKS_PER_SEC + start_time;
    while(clock() != end_time);

    timer.end();

    EXPECT_EQ( 0, timer.returnFlag() );
    EXPECT_DOUBLE_EQ( sec, timer.returnSeconds() );
}

TEST (Timer_hao, transferSecondToTm)
{
    double seconds=446582.0;
    struct tm timeinfo= transferSecondToTm (seconds);
    EXPECT_EQ(5, timeinfo.tm_mday);
    EXPECT_EQ(4, timeinfo.tm_hour);
    EXPECT_EQ(3, timeinfo.tm_min);
    EXPECT_EQ(2, timeinfo.tm_sec);
}