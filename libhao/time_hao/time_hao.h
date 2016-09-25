#ifndef AFQMCLIB_TIME_HAO_H
#define AFQMCLIB_TIME_HAO_H

#include <time.h>

class TimerHao
{
 private:
    double seconds;
    int    flag;  //0: Have not start accumulation. 1: In accumulation, between init() and end();
    clock_t clockInit, clockEnd;

 public:
    TimerHao();
    TimerHao(double);
    TimerHao(const TimerHao& );
    ~TimerHao();
    TimerHao& operator  = (const TimerHao&);

    double getSeconds();
    int getFlag();
    void setSeconds(double seconds);

    void init();
    void end();
    void clear();

    void print() const;
    void printFormat() const;
    void printCurrentTime() const;
};
#endif