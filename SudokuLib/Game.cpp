/**
 * @file Game.cpp
 * @author trang
 */
#include "pch.h"
#include <iostream>
#include <string>

#include <stdlib.h>
#include <algorithm>

#include "Game.h"
#include "Item.h"
#include "ItemVisitor.h"
#include "Digit.h"
#include "Background.h"
#include "Given.h"
#include "Xray.h"
#include "Sparty.h"
#include "DigitContainer.h"
#include <wx/graphics.h>
#include "EatDigitVisitor.h"
#include "DigitSpitVisitor.h"
#include "GivenCheck.h"
#include "DigitCheck.h"
#include "AnimatedText.h"
#include "SolveVisitor.h"

/**
 * Constructor for the game
*/
Game::Game()
{
    SetImagesDirectory(L".");
    Load(L"levels/level1.xml");

    std::random_device rd;
    mRandom.seed(rd());
    mTextBox = std::make_shared<AnimatedText>(this, "I'm Full");
}

/**
 * Set the directory the images are stored in
 * @param dir
 */
void Game::SetImagesDirectory(const std::wstring &dir)
{
    mImagesDirectory = dir + mImagesDirectory;
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Passed a pointer to an item that eats. We check to see
 * if there are any item it is currently next to.
 * @return true if the item is eaten
 */
bool Game::Eater()
{
    EatDigitVisitor visitor(mSparty,mXray);
    Accept(&visitor);

    if(visitor.GetAte() )
    {

        MoveToXray(visitor.GetEatenDig());
        visitor.GetEatenDig()->SetOnBoard(false);
        return true;
    }
    else if (mXray->GetSize() >=  mXray->GetCap())
    {
        if(!mTextBox->GetDrawText())
        {
            mTextBox->Reset("I'm Full!");
        }
        return false;
    }
    return false;

}
bool Game::AllTilesFilled()
{
    for (int x = mStartingCol; x < mStartingCol+9; x = x+1)
    {
        for (int y = mStartingRow; y < mStartingRow+9; y = y+1)
        {
            GivenCheck givencheck(x,y);
            Accept(&givencheck);
            DigitCheck digitcheck(x,y);
            Accept(&digitcheck);
            if (!givencheck.GetGivenFound() && !digitcheck.GetDigitFound())
            {
                return false;
            }
        }
    }
    return true;
}
bool Game::CheckCompleted()
{

    int count = -1;

    auto solution = mSolution.ToStdString();
    for (auto x :solution)
    {
        if(x != ' ')
        {
            count += 1;
            auto row = std::floor(count / 9);
            auto col = count - row * 9;
            DigitCheck digitcheck(col+mStartingCol, row+mStartingRow);
            GivenCheck givencheck(col+mStartingCol, row+mStartingRow);
            Accept(&digitcheck);
            Accept(&givencheck);
            if (digitcheck.GetDigitFound() == false)
            {
                digitcheck.SetVal(99);
            }
            if (givencheck.GetGivenFound() == false)
            {
                givencheck.SetVal(99);
            }
            auto z = std::to_string(givencheck.GetVal());
            auto y = std::to_string(digitcheck.GetVal());
            if(x != z && x != y)
            {
                return false;
            }

        }
    }

    return true;
}
/**
 * Attempts to spit a digit as long as it is in a valid location and
 * sparty has eaten the associated digit
 * @return true if the item has been spit-ed
 */
bool Game::Spit()
{
    auto x = AllTilesFilled();
    GivenCheck givenVisitor(round(mSparty->GetCol() / mTileWidth) + 1,
                            round((mSparty->GetRow() + (mSparty->GetHeight() / 2)) / mTileHeight));
    Accept(&givenVisitor);
    DigitCheck digitVisitor(round(mSparty->GetCol() / mTileWidth) + 1,
                            round((mSparty->GetRow() + (mSparty->GetHeight() / 2)) / mTileHeight));
    Accept(&digitVisitor);
    if(!givenVisitor.GetGivenFound()&&!digitVisitor.GetDigitFound())
    {

            DigitSpitVisitor visitor(mSparty->GetSpit());
            Accept(&visitor);
            if( visitor.GetDigFound())
            {
                mSparty->RotateMouth();
                MoveOutXray(visitor.GetDigToSpit());
                if(CheckDigOnBoard(visitor.GetDigToSpit()))
                {
                    visitor.GetDigToSpit()->SetOnBoard(true);
                }
            }

    }
    else
    {
        if(!mTextBox->GetDrawText())
        {
            mTextBox->Reset("There Is Already Something There!");
        }
    }



    return false;
}
/**
 * Hit test for the game board
 * Handles mouse click
 *
 * @param x
 * @param y
 * @return Return a pointer to the Item that passed the hit test
 */
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;

}

/**
 * Moves Item to Xray
 * @param digit digit to move into the xray
 */
void Game::MoveToXray(Digit* digit)
{
        std::uniform_real_distribution<>
            distribution(mXray->GetCol(), mXray->GetCol() - 1 + mXray->GetHeight() / this->GetTileHeight());
        std::uniform_real_distribution<>
            distribution2(mXray->GetRow() + 1 - mXray->GetWidth() / this->GetTileWidth(), mXray->GetRow());
        double x = distribution(this->GetRandom());
        double y = distribution2(this->GetRandom());
        digit->SetLocation(x, y);
        digit->SetHeight(digit->GetHeight() / 2);
        digit->SetWidth(digit->GetWidth() / 2);



}

/**
 * draws level complete banners
 * @param graphics
 */
void Game::DrawLevelComplete(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxFont instructFont(wxSize(0, 90),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD);
    wxColour darkGreen(wxColour(0, 180, 0));
    wxGraphicsFont dgFont = graphics->CreateFont(instructFont, darkGreen);
    graphics->SetFont(dgFont);
    graphics->DrawText("Level Complete!", 170, 200);
}

/**
 * Renders the game state using the provided graphics context
 * @param graphics the wxGrapicsContext to draw to
 * @param width the width of the screen
 * @param height the height of the screen
 * @param level
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, int level)
{


    long elapsedTime = mStopWatch.Time();
    long elapsedTime2 = mStopWatch2.Time();
//    int elapsed2AsInt = static_cast<int>(elapsedTime2);
    int elapsedAsInt = static_cast<int>(elapsedTime);
    // Set the playing area size
    int pixelWidth = mCols * mTileWidth;
    int pixelHeight = mRows * mTileHeight;


    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    //
    // Sets up the drawing of the stopwatch
    //

    wxFont font(wxSize(0, 64),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);

    wxFont instructFont(wxSize(0, 90),
                        wxFONTFAMILY_SWISS,
                        wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD);

    wxFont boldFont(wxSize(0, 50),
                    wxFONTFAMILY_SWISS,
                    wxFONTSTYLE_NORMAL,
                    wxFONTWEIGHT_BOLD);

    if(elapsedAsInt <= 3000){
        mGameWatch.Pause();
        if(mLevel == 1)
        {
            // Draws initial white background
            wxBrush instructions(*wxWHITE);
            graphics->SetBrush(instructions);
            graphics->DrawRectangle(mRectArea.x, mRectArea.y, mRectArea.width, mRectArea.height);

            //Draws Level begin text
            wxColour darkGreen(wxColour(0, 180, 0));
            wxGraphicsFont dgFont = graphics->CreateFont(instructFont, darkGreen);
            graphics->SetFont(dgFont);
            graphics->DrawText("Level 1 Begin", 170, 200);

            //Draws black instructions text
            wxColour black(wxColour(0, 0, 0));
            wxGraphicsFont newFont = graphics->CreateFont(boldFont, black);
            graphics->SetFont(newFont);
            graphics->DrawText("space: Eat", 340, 325);
            graphics->DrawText("0-8: Regurgitate", 300, 375);
            graphics->DrawText("B: Headbutt", 330, 425);
        }else if(mLevel == 2){
            wxBrush instructions(*wxWHITE);
            graphics->SetBrush(instructions);
            graphics->DrawRectangle(mRectArea.x + 225, mRectArea.y + 100, mRectArea.width, mRectArea.height);

            //Draws Level begin text
            wxColour darkGreen(wxColour(0, 180, 0));
            wxGraphicsFont dgFont = graphics->CreateFont(instructFont, darkGreen);
            graphics->SetFont(dgFont);
            graphics->DrawText("Level 2 Begin", 395, 300);

            //Draws black instructions text
            wxColour black(wxColour(0, 0, 0));
            wxGraphicsFont newFont = graphics->CreateFont(boldFont, black);
            graphics->SetFont(newFont);
            graphics->DrawText("space: Eat", 565, 430);
            graphics->DrawText("0-8: Regurgitate", 525, 480);
            graphics->DrawText("B: Headbutt", 555, 530);

        }else if(mLevel == 3){
            wxBrush instructions(*wxWHITE);
            graphics->SetBrush(instructions);
            graphics->DrawRectangle(mRectArea.x, mRectArea.y, mRectArea.width, mRectArea.height);

            //Draws Level begin text
            wxColour darkGreen(wxColour(0, 180, 0));
            wxGraphicsFont dgFont = graphics->CreateFont(instructFont, darkGreen);
            graphics->SetFont(dgFont);
            graphics->DrawText("Level 3 Begin", 170, 200);

            //Draws black instructions text
            wxColour black(wxColour(0, 0, 0));
            wxGraphicsFont newFont = graphics->CreateFont(boldFont, black);
            graphics->SetFont(newFont);
            graphics->DrawText("space: Eat", 340, 325);
            graphics->DrawText("0-8: Regurgitate", 300, 375);
            graphics->DrawText("B: Headbutt", 330, 425);
        }

    }
    if(elapsedAsInt > 3000)
    {
        mGameWatch.Resume();
        wxGraphicsFont gfont = graphics->CreateFont(font, *wxWHITE);
        graphics->SetFont(gfont);
        graphics->DrawText(wxString(mGameWatch.Time()), 10, 10);
    }

    if (AllTilesFilled())
    {
        mStopWatch2.Pause();

        auto z = static_cast<int>(elapsedTime2);
        auto elapsed = elapsedAsInt -z;
        auto x = CheckCompleted();
        ;
        if (x == true)
        {
            if (elapsed <= mMilestone)
            {

                DrawLevelComplete(graphics);
            }
            else
            {

                mStopWatch2.Start();
                if (mLevel != 3)
                {
                    const wxString filename = L"levels/level"+std::to_string(mLevel+1)+".xml";
                    this->Load(filename);
                }
                else
                {
                    const wxString filename = L"levels/level1.xml";
                    this->Load(filename);
                }




            }

        }
        else if (x == false)
        {
            if (elapsed <= mMilestone)
            {
                wxFont instructFont(wxSize(0, 90),

                                    wxFONTFAMILY_SWISS,
                                    wxFONTSTYLE_NORMAL,
                                    wxFONTWEIGHT_BOLD);
                wxColour darkGreen(wxColour(0, 180, 0));
                wxGraphicsFont dgFont = graphics->CreateFont(instructFont, darkGreen);
                graphics->SetFont(dgFont);
                graphics->DrawText("Incorrect!", 170, 200);
            }
            else
            {
                mStopWatch2.Start();
                const wxString filename = L"levels/level"+std::to_string(mLevel)+".xml";
                this->Load(filename);
            }
        }
    }
    graphics->PopState();

    mTextBox->Draw(graphics);
}

/**
 * Initializes an item using declaration id
 * @param id the declaration id
 * @param col the column position
 * @param row the row position
 */
void Game::InitDeclaration(std::string id, double col, double row)
{
    if(mDeclarations.find(id) != mDeclarations.end())
    {
        mDeclarations[id].get()->Initialize(&mItems, col, row, nullptr);
    }
}

/**
 * Initializes an item using declaration id
 * @param id the declaration id
 * @param col the column position
 * @param row the row position
 * @param node the node to initialize
 */
void Game::InitDeclaration(std::string id, double col, double row, wxXmlNode *node)
{
    if(mDeclarations.find(id) != mDeclarations.end())
    {
        mDeclarations[id].get()->Initialize(&mItems, col, row, node);
    }
}

/**
 * Clear the game data.
 * Deletes all known items in the game.
 */
void Game::Clear()
{
    mItems.clear();
    mDeclarations.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlDeclare(wxXmlNode *node)
{

    // A pointer for the item we are loading
    std::shared_ptr<Item> item;

    auto type = node->GetName();

    double height;
    node->GetAttribute(L"height").ToDouble(&height);
    double width;

    node->GetAttribute(L"width").ToDouble(&width);
    if (type == L"background")
    {
        item = std::make_shared<Background>(this, node->GetAttribute(L"image").ToStdWstring(), node->GetAttribute(L"id").ToStdString(), height, width,type);
    }
    else if (type == L"digit")
    {
        int val;
        node->GetAttribute(L"value").ToInt(&val);
        item = std::make_shared<Digit>(this, node->GetAttribute(L"image").ToStdWstring(), node->GetAttribute(L"id").ToStdString(), height, width,type, val);
    }
    else if (type == L"given")
    {
        int val;
        node->GetAttribute(L"value").ToInt(&val);
        item = std::make_shared<Given>(this, node->GetAttribute(L"image").ToStdWstring(), node->GetAttribute(L"id").ToStdString(), height, width,type, val);
    }
    else if (type == L"xray")
    {
        int cap;
        node->GetAttribute(L"capacity").ToInt(&cap);
        item = std::make_shared<Xray>(this, node->GetAttribute(L"image").ToStdWstring(), node->GetAttribute(L"id").ToStdString(), height, width,type, cap);
    }
    else if (type == L"container")
    {
        const std::wstring backPath = node->GetAttribute(L"image").ToStdWstring();
        const std::wstring frontPath = node->GetAttribute(L"front").ToStdWstring();
        item = std::make_shared<DigitContainer>(this, backPath, frontPath, node->GetAttribute(L"id").ToStdString(), height, width, type, false);
    }
    else if (type == L"speccontainer")
    {
        const std::wstring backPath = node->GetAttribute(L"image").ToStdWstring();
        const std::wstring frontPath = node->GetAttribute(L"front").ToStdWstring();
        item = std::make_shared<DigitContainer>(this, backPath, frontPath, node->GetAttribute(L"id").ToStdString(), height, width, type, true);
    }
    else if (type == L"sparty")
    {
        double hpa;
        int hpx;
        int hpy;


        double mpa;
        int mpx;
        int mpy;

        int tx;
        int ty;
        int front;

        const std::wstring image1Path = node->GetAttribute(L"image1").ToStdWstring();
        const std::wstring image2Path = node->GetAttribute(L"image2").ToStdWstring();
        node->GetAttribute(L"head-pivot-angle").ToDouble(&hpa);
        node->GetAttribute(L"head-pivot-x").ToInt(&hpx);
        node->GetAttribute(L"head-pivot-y").ToInt(&hpy);


        node->GetAttribute(L"mouth-pivot-angle").ToDouble(&mpa);
        node->GetAttribute(L"mouth-pivot-x").ToInt(&mpx);
        node->GetAttribute(L"mouth-pivot-y").ToInt(&mpy);

        node->GetAttribute(L"front").ToInt(&front);
        node->GetAttribute(L"target-x").ToInt(&tx);
        node->GetAttribute(L"target-y").ToInt(&ty);
        item = std::make_shared<Sparty>(this,image1Path,image2Path,node->GetAttribute(L"id").ToStdString(),height,width,type,mpa,mpx,mpy,hpa,hpx,hpy,tx,ty,front);

    }

    if (item != nullptr)
    {
        item->XmlLoad(node, true);
        SetDeclaration(node->GetAttribute(L"id").ToStdString(), item);
    }

}

/**
 * Parses an XML Node to initialize a game item
 * @param node XML note used to initialize
 */
void Game::XmlItem(wxXmlNode *node)
{
    double col;
    node->GetAttribute(L"col").ToDouble(&col);
    double row;
    node->GetAttribute(L"row").ToDouble(&row);
    InitDeclaration(node->GetAttribute(L"id").ToStdString(), col, row, node);
}

/**
 * Load the sudoku from a level XML file.
 * Opens the XML file and reads the nodes, creating items as appropriate.
 * @param filename The filename of the file to load the level from.
 */
void Game::Load(const wxString &filename)
{

    if (filename == L"levels/level0.xml")
    {
        mLevel = 0;
    }
    if (filename == L"levels/level1.xml")
    {
        mLevel = 1;
    }
    if (filename == L"levels/level2.xml")
    {
        mLevel = 2;
    }
    if (filename == L"levels/level3.xml")
    {
        mLevel = 3;
    }
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Sudoku file");
        return;
    }

    Clear();
    mGameWatch = StopWatch();
    mGameWatch.Resume();

    mStopWatch = wxStopWatch();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    root->GetAttribute("width").ToInt(&mCols);
    root->GetAttribute("height").ToInt(&mRows);

    root->GetAttribute("tilewidth").ToInt(&mTileWidth);
    root->GetAttribute("tileheight").ToInt(&mTileHeight);

    //
    // Traverse the children of the root
    //
    auto section = root->GetChildren();

    // iterate through declarations
    auto child = section->GetChildren();
    for( ; child; child=child->GetNext())
    {
        XmlDeclare(child);
    }
    section = section->GetNext();

    // Get game data

    mSolution = section->GetChildren()->GetContent();
    section->GetAttribute("col").ToInt(&mStartingCol);
    section->GetAttribute("row").ToInt(&mStartingRow);
    section = section->GetNext();

    // iterate through items
    child = section->GetChildren();

    for( ; child; child=child->GetNext())
    {
        XmlItem(child);
    }

}

/**
 * Update mItems each time the timer reaches a threshold
 * @param elapsed time from last update
 */
void Game::Update(double elapsed)
{
    mTextBox->Update(elapsed);
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
    mLeftX = (x - mXOffset) / mScale;
    mLeftY = (y - mYOffset) / mScale;
    if (mLeftX >= 48 && mLeftX <= mCols*mTileWidth && mLeftY >=0 && mLeftY <= mRows*mTileHeight-40 )
    {
        wxPoint2DDouble target(mLeftX,mLeftY);
        mSparty->SetTarget(target);
    }

}

/**
 * Moves a digit out of the xray
 * @param digit digit to remove from the xray
 */
void Game::MoveOutXray(Digit *digit)
{
    if(mXray->Spit())
    {
        digit->SetLocation(round(mSparty->GetCol() / mTileWidth) + 1,
                           round((mSparty->GetRow() + (mSparty->GetHeight() / 2)) / mTileHeight));
        digit->SetHeight(digit->GetHeight() * 2);
        digit->SetWidth(digit->GetWidth() * 2);
    }
}

/**
 * check if a digit is on the sudoku board
 * @param dig the digit to check
 * @return true if dig is on the board, false otherwise
 */
bool Game::CheckDigOnBoard(Digit* dig)
{
    int col = mStartingCol;
    int row = mStartingRow;

    int colCount = 0;
    int rowCount = 0;

    while(rowCount < 9)
    {
        if(dig->GetCol() == col && dig->GetRow() == row)
        {
            return true;
        }
        if(colCount < 9)
        {
            col++;
            colCount++;
        }
        else
        {
            col = mStartingCol;
            row++;
            rowCount++;
            colCount = 0;
        }
    }
    return false;
}

void Game::Solve()
{
    int count = 0;

    // set col and row variables equal to the position
    // of the first cell of the sudoku board
    int col = mStartingCol;
    int row = mStartingRow;

    auto solution = mSolution.ToStdString();

    // used to get a pointer to a digit of specified value
    SolveVisitor digVisitor(0);
    // used to check if a given is already at
    // specified position
    GivenCheck givenCheck(0, 0);

    DigitCheck digCheck(0, 0);

    // iterate through all solution digits
    for (char solutionDig : solution)
    {
        if(solutionDig != ' ')
        {
            count++;
            // reset visitor found flags
            digVisitor.SetDigitFound(false);
            givenCheck.SetGivenFound(false);
            digCheck.SetDigitFound(false);
            // set new targets for visitors to look for
            digVisitor.SetTarget(int(solutionDig - '0'));
            givenCheck.SetTarget(col, row);
            digCheck.SetTarget(col, row);
            // acccept visitors
            Accept(&digVisitor);
            Accept(&givenCheck);
            Accept(&digCheck);

            // check if cell does not have a given and if the correct
            // digit has been found and has not been eaten
            if(!givenCheck.GetGivenFound() && digVisitor.GetDigitFound() && !digVisitor.GetDigit()->GetEaten() && !digCheck.GetDigitFound())
            {
                // location of digit to the correct position on the sudoku board
                digVisitor.GetDigit()->SetLocation(col, row);
                digVisitor.GetDigit()->SetOnBoard(true);
            }
            // adjust current col and row
            // move to next col
            if(count != 9)
            {
                col++;
            }
            // move to next row
            else
            {
                col = mStartingCol;
                row++;
                count = 0;
            }
        }
    }
}


