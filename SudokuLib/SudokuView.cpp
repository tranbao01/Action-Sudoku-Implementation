/**
 * @file SudokuView.cpp
 * @author Josh Costantino
 */

#include "pch.h"
#include "SudokuView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include <wx/graphics.h>
#include "Sparty.h"
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the aquarium view class.
 * @param mainFrame The parent window for this class
 */
void SudokuView::Initialize(wxFrame *mainFrame)
{
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SudokuView::OnPaint, this);



    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnOpenZero, this, IDM_LEVELZERO);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnOpenOne, this, IDM_LEVELONE);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnOpenTwo, this, IDM_LEVELTWO);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnOpenThree, this, IDM_LEVELTHREE);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::Solve, this, IDM_SOLVE);

    Bind(wxEVT_TIMER, &SudokuView::OnTimer, this);
    Bind(wxEVT_LEFT_DOWN, &SudokuView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN,&SudokuView::OnKey,this);
    Bind(wxEVT_LEFT_UP,&SudokuView::OnLeftUp,this);
    mRectTimer.SetOwner(this);
    mRectTimer.Start(FrameDuration);


    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

}

/**
 * Determines what should happen whenever a key is pressed
 * @param event the key that was pressed
 */
void SudokuView::OnKey(wxKeyEvent &event)
{
    if (event.GetKeyCode()==32)//Spacebar key code is 32
    {
        mGame.GetSparty()->RotateMouth();
        mGame.Eater();
       
    }
    if (event.GetKeyCode() == 66 || event.GetKeyCode()==98)
    {
        mGame.GetSparty()->HeadButt();
    }
    if (event.GetKeyCode()== 48)
    {
        mGame.GetSparty()->SetSpit(0);
        mGame.Spit();

    }
    if (event.GetKeyCode()== 49)
    {
        mGame.GetSparty()->SetSpit(1);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 50)
    {
        mGame.GetSparty()->SetSpit(2);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 51)
    {
        mGame.GetSparty()->SetSpit(3);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 52)
    {
        mGame.GetSparty()->SetSpit(4);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 53)
    {
        mGame.GetSparty()->SetSpit(5);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 54)
    {
        mGame.GetSparty()->SetSpit(6);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 55)
    {
        mGame.GetSparty()->SetSpit(7);
        mGame.Spit();
    }
    if (event.GetKeyCode()== 56)
    {
        mGame.GetSparty()->SetSpit(8);
        mGame.Spit();
    }
}

/**
 * Lets the game know the left button has been clicked
 * @param event left mouse button is clicked
 */
void SudokuView::OnLeftDown(wxMouseEvent &event)
{
       mGame.OnLeftDown(event.GetX(), event.GetY());
}

void SudokuView::OnLeftUp(wxMouseEvent& event)
{

}

/**
 * Handles the paint event for the SudokuView
 *
 * @param event
 */
void SudokuView::OnPaint(wxPaintEvent& event) {
    auto newTime =  mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);

    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();

    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight(), mLevel);


}

/**
 * Handles the timer event for the SudokuView
 *
 * @param event
 */
void SudokuView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}


/**
 * Levels>level 0 menu handler
 * @param event Menu event
 */
void SudokuView::OnOpenZero(wxCommandEvent &event)
{
    mLevel =0;
    mGame.Load(L"levels/level0.xml");
}

/**
 * Levels>level 1 menu handler
 * @param event Menu event
 */
void SudokuView::OnOpenOne(wxCommandEvent &event)
{
    mLevel = 1;
    mGame.Load(L"levels/level1.xml");
}

/**
 * Levels>level 2 menu handler
 * @param event Menu event
 */
void SudokuView::OnOpenTwo(wxCommandEvent &event)
{
    mLevel = 2;
    mGame.Load(L"levels/level2.xml");
}

/**
 * Levels>level 3 menu handler
 * @param event Menu event
 */
void SudokuView::OnOpenThree(wxCommandEvent &event)
{
    mLevel = 3;
    mGame.Load(L"levels/level3.xml");
}

/**
 * Solves the game
 * @param event
 */
void SudokuView::Solve(wxCommandEvent &event)
{
    mGame.Solve();
}
