/**
 * @file SudokuView.h
 * @author Josh Costantino
 *
 * The view class for the sudoku game
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUVIEW_H
#define PROJECT1_SUDOKULIB_SUDOKUVIEW_H

#include "Game.h"
#include "StopWatch.h"

/**
 * The view class for the sudoku game
 */
class SudokuView : public wxWindow
{
private:

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnKey(wxKeyEvent& event);

    /// The Game
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// How long the program has been running
    wxTimer mRectTimer;

    /// filename for the level
    int mLevel = 1;

public:

    void Initialize(wxFrame *mainFrame);

    /**
     * Stop the timer so the window can close
     */
    void Stop() { mTimer.Stop(); mRectTimer.Stop(); }

    void OnOpenZero(wxCommandEvent &event);

    void OnOpenOne(wxCommandEvent &event);

    void OnOpenTwo(wxCommandEvent &event);

    void OnOpenThree(wxCommandEvent &event);

    void Solve(wxCommandEvent &event);

};

#endif //PROJECT1_SUDOKULIB_SUDOKUVIEW_H
