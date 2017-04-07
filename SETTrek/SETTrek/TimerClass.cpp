/*
* PROJECT		: SETTrek
* FILE			: TimerClass.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The CPP file containing the class defintion for a TimerClass.
*/
#include "TimerClass.h"



INT64 TimerClass::_startTime;
INT64 TimerClass::_frequency;
float TimerClass::_tickersPerMilli;
float TimerClass::_frameTime;
clock_t TimerClass::start;
clock_t TimerClass::diff;
clock_t TimerClass::current;


void TimerClass::InitTimer(void)
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&_frequency);
    if (_frequency == 0)
    {
        return;
    }

    _tickersPerMilli = (float)(_frequency / 1000);

    QueryPerformanceCounter((LARGE_INTEGER*)&_startTime);
}


void TimerClass::StartTimer(void)
{
    start = clock();
}

void TimerClass::EndTimer(void)
{
    diff = clock() - start;
}

int TimerClass::GetCurrentElapsedTime(void)
{
    current = clock() - start;

    int milliseconds = current * 1000 / CLOCKS_PER_SEC;
    return milliseconds;
}