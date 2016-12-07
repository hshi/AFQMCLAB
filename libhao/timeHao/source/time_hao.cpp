#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "../include/time_hao.h"

using namespace std;

struct tm transferSecondToTm (double seconds);

TimerHao::TimerHao():seconds(0),state(TimerState::TIMER_NOT_STARTED) {}

TimerHao::TimerHao(double secs):seconds(secs),state(TimerState::TIMER_NOT_STARTED) {}

TimerHao::TimerHao(const TimerHao& x):seconds(x.seconds),state(x.state),timerInit(x.timerInit),timerEnd(x.timerEnd) {}

TimerHao::~TimerHao() {}

TimerHao& TimerHao::operator  = (const TimerHao& x)
{
    seconds=x.seconds;
    state=x.state;
    timerInit=x.timerInit;
    timerEnd=x.timerEnd;
    return *this;
}

double TimerHao::getSeconds() const {return seconds;}

TimerState TimerHao::getState() const {return state;}

void TimerHao::setSeconds(double seconds)
{
    TimerHao::seconds = seconds;
}

void TimerHao::start()
{
    if( state != TimerState::TIMER_NOT_STARTED )
    {
        throw runtime_error( "ERROR!!! Cannot initial the timer before it is ended!" );
    }
    time(&timerInit);
    state = TimerState::TIMER_IN_ACCUMULATION;
}


void TimerHao::end()
{
    if( state != TimerState::TIMER_IN_ACCUMULATION )
    {
        throw runtime_error("ERROR!!! Cannot end the timer before it is started!");
    }
    time(&timerEnd);
    seconds+=difftime(timerEnd,timerInit);
    state = TimerState::TIMER_NOT_STARTED;
}

void TimerHao::clear()
{
    seconds = 0.0;
    state = TimerState::TIMER_NOT_STARTED;
}

void TimerHao::print() const
{
    if(state != TimerState::TIMER_NOT_STARTED)
    {
        cout<<"WARNING!!! It is still timing, the accumulation will not contain current timing circle!"<<endl;
    }
    cout<<setprecision(15);
    cout<<"Total seconds: "<<seconds<<endl;
}

void TimerHao::printFormat() const
{
    if(state != TimerState::TIMER_NOT_STARTED)
    {
        cout<<"WARNING!!! It is still timing, the accumulation will not contain current timing circle!"<<endl;
    }
    struct tm timeinfo= transferSecondToTm (seconds);
    cout<<setprecision(15);
    cout<<"Total seconds: "<<seconds<<"\n";
    cout<<"Total Hours: "<<seconds/3600.0<<"\n";
    cout<<"Readable Time: "<<timeinfo.tm_mday<<" days, "<<timeinfo.tm_hour<<" hours, "
        <<timeinfo.tm_min<<" minutes, "<<timeinfo.tm_sec <<" seconds\n\n";
}

void TimerHao::printCurrentTime () const
{
    time_t timer;
    time(&timer);
    cout<<ctime(&timer)<<endl;
}

struct tm transferSecondToTm (double seconds)
{
    struct tm timeinfo; long sec=lround(seconds);
    timeinfo.tm_year =0; timeinfo.tm_mon = 0;
    timeinfo.tm_mday=sec/86400;
    sec%=86400;
    timeinfo.tm_hour=sec/3600;
    sec%=3600;
    timeinfo.tm_min=sec/60;
    sec%=60;
    timeinfo.tm_sec=sec;
   
    return timeinfo;
}