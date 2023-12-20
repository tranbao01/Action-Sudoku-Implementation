/**
 * @file StopWatch.h
 * @author Paul Boik
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_STOPWATCH_H
#define PROJECT1_SUDOKULIB_STOPWATCH_H

#include <wx/graphics.h>

/**
 * Stopwatch class that keeps track of time in the game
 */
class StopWatch
{
private:

    /// The Stopwatch associated with the class
    wxStopWatch mStopWatch;

    /// The current amount of minutes when Time is called
    int mMinutes;

    /// The current amount of seconds when Time is called
    int mSeconds;

    /// The status of the stopwatch
    bool mPaused;

public:

    /**
     * Sets milliseconds variable to 0
     * @param milliseconds
     */
    StopWatch(int milliseconds = 0);

    void Pause();

    void Resume();

    std::string Time();
};

#endif //PROJECT1_SUDOKULIB_STOPWATCH_H
