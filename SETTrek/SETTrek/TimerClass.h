/*
* PROJECT		: SETTrek
* FILE			: TimerClass.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/02/8
* DESCRIPTION	: The header file containing the class defintion for the TimerClass.
*       The TimerClass is a utility to keep track of the computer time.
*/
#pragma once

#include <Windows.h>
#include <time.h>
#include <timeapi.h>
using namespace std;




/**
* \class TimerClass
* \brief The TimerClass utility has time functionality for keeping track of the computer time.
*/
class TimerClass
{
private:

    static INT64 _startTime;
    static INT64 _frequency;
    static float _tickersPerMilli;
    static float _frameTime;

    static clock_t start;
    static clock_t diff;
    static clock_t current;

public:


    static void InitTimer(void);
    static void StartTimer(void);
    static void EndTimer(void);
    static int GetCurrentElapsedTime(void);
};