/**
 * @file AnimatedText.cpp
 * @author gymna
 */

#include "pch.h"
#include "AnimatedText.h"
#include "Game.h"

/**
 * Constructor
 * @param phrase phrase to display in the box
 * @param game
 */
AnimatedText::AnimatedText(Game *game, std::string phrase)
{
    mGame = game;
    mPhrase = phrase;

    mCol = (mGame->GetWidth() * mGame->GetTileWidth()) * 0.5;
    mRow = (mGame->GetHeight() * mGame->GetTileHeight());
}

/**
 * Resets the text box location with a new message
 * @param newPhrase new message to have in the text box
 */
void AnimatedText::Reset(std::string newPhrase)
{
    mPhrase = newPhrase;
    mCol = (mGame->GetWidth() * mGame->GetTileWidth()) / 2;
    mRow = (mGame->GetHeight() * mGame->GetTileHeight());
    mDrawText = true;
}

/**
 * Update the position of the text box
 * @param elapsed time since last update
 */
void AnimatedText::Update(double elapsed)
{
    mRow -= 8;
    if(mRow <= -40)
    {
        mDrawText = false;
    }
}

/**
 * Draws the text box and text
 * @param dc pointer to the wxGraphicsContext to draw on
 */
void AnimatedText::Draw(std::shared_ptr<wxGraphicsContext> dc)
{
    if(mDrawText && mPhrase == "I'm Full!")
    {
        wxFont boldFont(wxSize(0, 25),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD);

        // Draws outer black background
        wxBrush instructions(*wxBLACK);
        dc->SetBrush(instructions);
        dc->DrawRectangle(mCol - 55, mRow - 5, 106, 40);

        // Draws initial white background
        wxBrush instructions2(*wxWHITE);
        dc->SetBrush(instructions2);
        dc->DrawRectangle(mCol - 50, mRow, 96, 30);

        //Draws red instructions text
        wxColour red(wxColour(255, 0, 0));
        wxGraphicsFont newFont = dc->CreateFont(boldFont, red);
        dc->SetFont(newFont);
        dc->DrawText(mPhrase, mCol - 48, mRow);
    }

    if(mDrawText && mPhrase == "There Is Already Something There!")
    {
        wxFont boldFont(wxSize(0, 25),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD);

        // Draws outer black background
        wxBrush instructions(*wxBLACK);
        dc->SetBrush(instructions);
        dc->DrawRectangle(mCol - 215, mRow - 5, 430, 40);

        // Draws initial white background
        wxBrush instructions2(*wxWHITE);
        dc->SetBrush(instructions2);
        dc->DrawRectangle(mCol - 210, mRow, 420, 30);

        //Draws red instructions text
        wxColour red(wxColour(255, 0, 0));
        wxGraphicsFont newFont = dc->CreateFont(boldFont, red);
        dc->SetFont(newFont);
        dc->DrawText(mPhrase, mCol - 208, mRow);
    }
}