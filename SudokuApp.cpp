/**
 * @file SudokuApp.cpp
 * @author Joseph Khalaf
 */

#include "pch.h"
#include "SudokuApp.h"
#include "MainFrame.h"

/**
 * Innitialize the application
 * @return
 */
bool SudokuApp::OnInit()
{

    #ifdef WIN32
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    ///Tabbed out while waiting for MainFrame
    auto frame = new MainFrame();
    frame->Initialize();


    frame->Show(true);

    return true;
}

