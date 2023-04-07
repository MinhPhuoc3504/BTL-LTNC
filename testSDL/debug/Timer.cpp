
#include "Timer.h"


ImpTimer::ImpTimer()
{
    start_tick=0;
    paused_tick = 0;
    is_paused_=false;
    is_start_=false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    is_start_ = true;
    is_paused_=false;
    start_tick = SDL_GetTicks() ;
}

void ImpTimer::stop()
{
    is_paused_=false;
    is_start_ = false;
}

void ImpTimer::paused()
{
    if(is_start_==true && is_paused_==false)
    {
        is_paused_ =true;
        paused_tick = SDL_GetTicks() - start_tick;//tgian hien tai tru thoi gian troi qua= thoi diem paused

    }
}

void ImpTimer::unpaused()
{
    if(is_paused_ ==true)
    {
        is_paused_ = false;
        // tim thoi diem bat dau lai
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int ImpTimer::get_ticks()
{
    if(is_start_ ==true)
    {
        if(is_paused_ ==true )
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks()-start_tick;
        }

    }
    return 0;
}

bool ImpTimer::is_start()
{
    return is_start_;
}

bool ImpTimer::is_paused()
{
    return is_paused_;
}
