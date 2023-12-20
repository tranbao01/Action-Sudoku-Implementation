/**
 * @file Game.h
 * @author trang
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_GAME_H
#define PROJECT1_SUDOKULIB_GAME_H

#include <map>
#include "StopWatch.h"
#include "Sparty.h"
#include "Digit.h"
#include "Xray.h"
#include <random>

class Item;
class ItemVisitor;
class Xray;
class AnimatedText;

/**
 * the sudoku game class
 */
class Game
{
private:

    /// All of the items in the game
    std::vector<std::shared_ptr<Item>> mItems;

    /// A map that stores the information of all IDs
    std::map<std::string, std::shared_ptr<Item>> mDeclarations;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    /// The number of columns in the playing area
    int mCols = 20;

    /// The number of rows in the playing area
    int mRows = 15;
    /// The time at which the game starts
    int mMilestone = 3000;

    /// X location where left clicked
    double mLeftX;

    /// Y location where left clicked
    double mLeftY;

    /// Height of each tile
    int mTileHeight = 48;

    /// Width of each tile
    int mTileWidth = 48;

    /// Area of the screen as a rectangle
    wxRect mRectArea = wxRect(150,190,620,300);

    /// Offset of the x location on screen
    double mXOffset;

    /// Offset of the y location on screen
    double mYOffset;

    /// Scale of the game, changes as the frame changes
    double mScale;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// Stopwatch used in the game
    wxStopWatch mStopWatch2;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// The Scoreboard for the game
    StopWatch mGameWatch;

    /// The solution to the game (temporarily a wxString)
    wxString mSolution;

    /// The sparty head that the player controls
    std::shared_ptr<Sparty> mSparty;

    /// The xray
    std::shared_ptr<Xray> mXray;

    /// Random number generator
    std::mt19937 mRandom;

    /// shared pointer to a textbox in the game
    std::shared_ptr<AnimatedText> mTextBox;

    /// The column position of the game board
    int mStartingCol;
    /// The current level the game is on
    int mLevel;
    /// the row position of the game board
    int mStartingRow;

public:
    Game();
    /**
     * Getter for mStopWatch
     * @return mStopWatch
     */
    wxStopWatch GetStopWatch() { return mStopWatch; }
    /**
     * Getter for mStopWatch2
     * @return mStopWatch2
     */
    wxStopWatch GetStopWatch2() { return mStopWatch2; }

    /**
     * starts the timer
     */
    void InitializeTimer(){mTimer.Start(100);}

    /**
     * get the solution to the game for the solve button and seeing if the level is complete
     * @return the solution of the game
     */
    wxString GetSolution() { return mSolution; }

    /**
     * Gets the Sparty Item the user controls
     * @return Returns a pointer to Sparty
     */
    std::shared_ptr<Sparty> GetSparty() { return mSparty; }

    /**
     * Sets sparty to a new sparty Item
     * @param sparty the new sparty to use in the game
     */
    void SetSparty(std::shared_ptr<Sparty> sparty) { mSparty = sparty; }

    /**
     * Set the xray to a new xray Item
     * @param xray the new xray to use in the game
     */
    void SetXray(std::shared_ptr<Xray> xray) { mXray = xray; }

    /**
     * Gets the height of the screen
     * @return an int of the size of the screen in rows
     */
    int GetHeight() { return mRows; }

    /**
     * Gets the width of the screen
     * @return an int of the size of the screen in cols
     */
    int GetWidth() { return mCols; }

    /**
     * Get the height of each tile on screen
     * @return an int of the height of each tile
     */
    int GetTileHeight() { return mTileHeight; }

    /**
     * Get the width of each tile on screen
     * @return an int of the width of each tile
     */
    int GetTileWidth() { return mTileWidth; }

    /**
     * Gets a declaration at a given id
     * @param id
     * @return the declaration at the id
     */
    std::shared_ptr<Item> GetDeclaration(std::string id) { return mDeclarations[id]; }

    /**
     * Deconstructor
     */
    virtual ~Game() = default;

    void SetImagesDirectory(const std::wstring &dir);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToXray(Digit* digit);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, int level);
    void DrawLevelComplete(std::shared_ptr<wxGraphicsContext> graphics);
    /**
   * Get the random number generator
   * @return Pointer to the random number generator
   */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * Setter for mDeclarations
     * @param id the id to set
     * @param item the declaration item
     */
    void SetDeclaration(std::string id, std::shared_ptr<Item> item) { mDeclarations[id] = item; }

    void InitDeclaration(std::string id, double col, double row);
    void InitDeclaration(std::string id, double col, double row, wxXmlNode *node);

    void XmlItem(wxXmlNode *node);

    void XmlDeclare(wxXmlNode *node);

    void Clear();

    void Load(const wxString &filename);

    void Update(double elapsed);

    void Accept(ItemVisitor* visitor);

    void OnLeftDown(int x, int y);

    bool Eater();
    bool Spit();

    void MoveOutXray(Digit* digit);
    /**
     * checks if all tiles are filled
     * @return if all tiles are filled
     */
    bool AllTilesFilled();
    /**
     * Check the correctness of the board
     * @return the correctness of the board
     */
    bool CheckCompleted();

    bool CheckDigOnBoard(Digit* dig);

    /**
     * Solves the board
     */
    void Solve();
};

#endif //PROJECT1_SUDOKULIB_GAME_H
