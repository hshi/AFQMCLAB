#include <iostream>
#include <stdexcept>
#include "../test_hao/gtest_custom.h"
#include "time_hao.h"

struct tm transferSecondToTm (double seconds);

using namespace std;

TEST (Timer_hao, void_constructor)
{
    TimerHao timer;
    EXPECT_EQ( 0, timer.getFlag() );
    EXPECT_DOUBLE_EQ( 0, timer.getSeconds() );
}

TEST (Timer_hao, double_constructor)
{
    TimerHao timer(3.0);
    EXPECT_EQ( 0, timer.getFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.getSeconds() );
}

TEST (Timer_hao, equal_constructor)
{
    TimerHao timer_init(3.0);
    TimerHao timer = timer_init;
    EXPECT_EQ( 0, timer.getFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.getSeconds() );
}

TEST (Timer_hao, equal_assignment)
{
    TimerHao timer_init(3.0);
    TimerHao timer;
    timer = timer_init;
    EXPECT_EQ( 0, timer.getFlag() );
    EXPECT_DOUBLE_EQ( 3.0, timer.getSeconds() );
}

TEST(Timer_hao, setSeconds)
{
    TimerHao timer;
    timer.setSeconds(2.0);
    EXPECT_EQ( 2.0, timer.getSeconds() );
}

TEST (Timer_hao, init)
{
    TimerHao timer;
    timer.init();
    EXPECT_EQ( 1, timer.getFlag() );
    EXPECT_DOUBLE_EQ( 0.0, timer.getSeconds() );
    EXPECT_THROW( timer.init(), runtime_error );
    try
    {
        timer.init();
    }
    catch(runtime_error& err)
    {
        EXPECT_EQ( "ERROR!!! Cannot initial the timer before it is ended!", string(err.what()) );
    }

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

    EXPECT_EQ( 0, timer.getFlag() );
    EXPECT_DOUBLE_EQ( sec, timer.getSeconds() );
    EXPECT_THROW( timer.end(), runtime_error );
    try
    {
        timer.end();
    }
    catch(runtime_error& err)
    {
        EXPECT_EQ( "ERROR!!! Cannot end the timer before it is initialized!", string(err.what()) );
    }
}

TEST(Timer_hao, clear)
{
    TimerHao timer;
    timer.setSeconds(2.0);
    timer.clear();
    EXPECT_EQ( 0.0, timer.getSeconds() );
    EXPECT_EQ( 0.0, timer.getFlag() );
}


TEST(Timer_hao, transferSecondToTm)
{
    double seconds=446582.0;
    struct tm timeinfo= transferSecondToTm (seconds);
    EXPECT_EQ(5, timeinfo.tm_mday);
    EXPECT_EQ(4, timeinfo.tm_hour);
    EXPECT_EQ(3, timeinfo.tm_min);
    EXPECT_EQ(2, timeinfo.tm_sec);
}