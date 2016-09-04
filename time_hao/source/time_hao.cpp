#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/time_hao.h"

using namespace std;


Timer_hao::Timer_hao():seconds(0),timing_flag(0) {}

Timer_hao::Timer_hao(double secs):seconds(secs),timing_flag(0) {}

Timer_hao::Timer_hao(const Timer_hao& x):seconds(x.seconds),timing_flag(x.timing_flag),timerinit(x.timerinit),timerend(x.timerend) {}

Timer_hao::~Timer_hao() {}

Timer_hao& Timer_hao::operator  = (const Timer_hao& x)
{
    seconds=x.seconds;
    timing_flag=x.timing_flag;
    timerinit=x.timerinit;
    timerend=x.timerend;
    return *this;
}

void Timer_hao::init()
{
    if(timing_flag!=0) {cerr<<"ERROR!!! Cannot initial the timer before it is ended!"<<endl; exit(1);}
    time(&timerinit);
    timing_flag=1;
}

void Timer_hao::end()
{
    if(timing_flag!=1) {cout<<"ERROR!!! Cannot end the timer before it is initialized!"<<endl; exit(1);}
    time(&timerend);
    seconds+=difftime(timerend,timerinit);
    timing_flag=0;
}


void Timer_hao::clear()
{
    if(timing_flag!=0) {cout<<"ERROR!!! Cannot clear the timer before it is ended!"<<endl; exit(1);}
    seconds=0; //clear the time to zero
}

void Timer_hao::print_init() const {cout<<ctime(&timerinit)<<endl;}  

void Timer_hao::print_end() const {cout<<ctime(&timerend)<<endl;}  

void Timer_hao::print_accumulation() const
{
    if(timing_flag!=0) {cout<<"WARNING!!! It is still timing, the accumulation will not contain current timing circle!";}
    struct tm timeinfo=second_to_tm(seconds);
    cout<<setprecision(15);
    cout<<"Total seconds: "<<seconds<<"\n";
    cout<<"Total Hours: "<<seconds/3600.0<<"\n"; 
    cout<<"Readable Time: "<<timeinfo.tm_mday<<" days, "<<timeinfo.tm_hour<<" hours, "
    <<timeinfo.tm_min<<" minutes, "<<timeinfo.tm_sec <<" seconds\n\n";
}


struct tm second_to_tm(double seconds)
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
