/**
 * @file MainFrame.h
 * @author trang
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_MAINFRAME_H
#define PROJECT1_SUDOKULIB_MAINFRAME_H
#include <wx/filehistory.h>
#include <wx/config.h>

class SudokuView;

/**
 * Class for the game MainFrame
 */
class MainFrame : public wxFrame
{
private:
    /// Pointer the the SudokuView class associated with it
    SudokuView *mSudoku;

public:
    void Initialize();
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent &event);
};

#endif //PROJECT1_SUDOKULIB_MAINFRAME_H
