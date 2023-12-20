/**
 * @file StopWatch.cpp
 * @author Paul Boik
 */

#include "pch.h"
#include "StopWatch.h"

/**
 * Constructor
 * @param milliseconds Starting time of the stopwatch
 */
StopWatch::StopWatch(int milliseconds)
{
    mStopWatch.Start(milliseconds);
    mStopWatch.Pause();
    mPaused = true;
}

/**
 * Pauses the stopwatch
 */
void StopWatch::Pause()
{
    if (!mPaused)
    {
        mStopWatch.Pause();
    }
    mPaused = true;
}

/**
 * Resumes the stopwatch from pause
 */
void StopWatch::Resume()
{
    if (mPaused)
    {
        mStopWatch.Resume();
    }
    mPaused = false;
}

/**
 * Converts the current time from milliseconds to minutes and seconds
 * @return A string in the format of 0:00 with minutes first and seconds last
 */
std::string StopWatch::Time()
{
    mMinutes = (mStopWatch.Time() / 1000) / 60;
    //if (mMinutes < 1)
    //{
       mSeconds = (mStopWatch.Time() / 1000) % 60 ;
    //}

    if (mSeconds < 10)
    {
        return std::to_string(mMinutes) + ":0" + std::to_string(mSeconds);
    }
    return std::to_string(mMinutes) + ":" + std::to_string(mSeconds);
}