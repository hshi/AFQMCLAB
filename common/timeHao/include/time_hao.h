#ifndef AFQMCLAB_TIME_HAO_H
#define AFQMCLAB_TIME_HAO_H

#include <time.h>

//Switch clock_t back to time_t
//clock() function does not work fine for openmp case
//However time function only distinguish up to 1 second!

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
    time_t timerInit, timerEnd;

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