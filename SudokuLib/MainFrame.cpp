/**
 * @file MainFrame.cpp
 * @author trang
 */

#include "pch.h"
#include "MainFrame.h"
#include "SudokuView.h"
#include "ids.h"

/**
 * Initializes the mainframe and all the menu options at the top
 */
void MainFrame::Initialize() {
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition,  wxSize( 1000,800 ));
    auto sizer = new wxBoxSizer(wxVERTICAL);
    auto sudokuView = new SudokuView();
    sudokuView->Initialize(this);
    mSudoku = sudokuView;
    sizer->Add(sudokuView,1,wxEXPAND | wxALL);
    SetSizer(sizer);
    Layout();

    auto menuBar = new wxMenuBar;
    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");



    SetMenuBar( menuBar );
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    fileMenu->Append(IDM_SOLVE, "Solve", L"Solve Sudoku");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVELZERO, L"&Level 0", L"Level 0");
    levelMenu->Append(IDM_LEVELONE, L"&Level 1", L"Level 1");
    levelMenu->Append(IDM_LEVELTWO, L"&Level 2", L"Level 2");
    levelMenu->Append(IDM_LEVELTHREE, L"&Level 3", L"Level 3");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

}

/**
 * Close the program when the exit button is clicked
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Pop up a messageBox when the about menu option is clicked
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event){
    wxMessageBox(L"Action Sudoku",
                 L"Action Sudoku",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mSudoku->Stop();
    Destroy();
}
