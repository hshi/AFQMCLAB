#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "time_hao.h"

using namespace std;

struct tm transferSecondToTm (double seconds);

TimerHao::TimerHao():seconds(0),flag(0) {}

TimerHao::TimerHao(double secs):seconds(secs),flag(0) {}

TimerHao::TimerHao(const TimerHao& x):seconds(x.seconds),flag(x.flag),clockInit(x.clockInit),clockEnd(x.clockEnd) {}

TimerHao::~TimerHao() {}

TimerHao& TimerHao::operator  = (const TimerHao& x)
{
    seconds=x.seconds;
    flag=x.flag;
    clockInit=x.clockInit;
    clockEnd=x.clockEnd;
    return *this;
}

double TimerHao::getSeconds() {return seconds;}

int TimerHao::getFlag() {return flag;}

void TimerHao::setSeconds(double seconds)
{
    TimerHao::seconds = seconds;
}

void TimerHao::init()
{
    if(flag!=0) { throw runtime_error( "ERROR!!! Cannot initial the timer before it is ended!" ); }
    clockInit = clock();
    flag=1;
}


void TimerHao::end()
{
    if(flag!=1) { throw runtime_error("ERROR!!! Cannot end the timer before it is initialized!");}
    clockEnd = clock();
    seconds += double(clockEnd - clockInit) / CLOCKS_PER_SEC;
    flag=0;
}

void TimerHao::clear()
{
    seconds=0;
    flag = 0;
}

void TimerHao::print() const
{
    if(flag!=0) {cout<<"WARNING!!! It is still timing, the accumulation will not contain current timing circle!";}
    cout<<setprecision(15);
    cout<<"Total seconds: "<<seconds<<"\n";
}

void TimerHao::printFormat() const
{
    if(flag!=0) {cout<<"WARNING!!! It is still timing, the accumulation will not contain current timing circle!";}
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