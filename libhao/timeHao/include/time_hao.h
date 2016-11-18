#ifndef AFQMCLIB_TIME_HAO_H
#define AFQMCLIB_TIME_HAO_H

#include <time.h>

enum class TimerState
{
    TIMER_NOT_STARTED,
    TIMER_IN_ACCUMULATION
};

class TimerHao
{
 private:
    double seconds;
    TimerState state;
    clock_t clockInit, clockEnd;

 public:
    TimerHao();
    TimerHao(double);
    TimerHao(const TimerHao& );
    ~TimerHao();
    TimerHao& operator  = (const TimerHao&);

    double getSeconds() const;
    TimerState getState() const;
    void setSeconds(double seconds);

    void start();
    void end();
    void clear();

    void print() const;
    void printFormat() const;
    void printCurrentTime() const;
};
#endif