
#ifndef TIMER_H_
#define TIMER_H_

#include "CommonFun.h"
#include "BaseObject.h"

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_start();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_start_;
};

#endif // TIMER_H_
