/**
* @file Item.h
* @author trang
*
*
*/

#ifndef PROJECT1_SUDOKULIB_ITEM_H
#define PROJECT1_SUDOKULIB_ITEM_H

#include <wx/xml/xml.h>
#include <string>
#include <map>
#include <wx/graphics.h>

class Game;
class ItemVisitor;

/**
 * Base class for any item in the game.
 */
class Item
{
protected:

    Item(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type);

private:

    /// The Game this Item is in
    Game *mGame;

    /// The filename for this Item's image
    std::wstring mFileName;

    /// The underlying image
    std::shared_ptr<wxImage> mItemImage;

    /// The item bitmap
    wxGraphicsBitmap mItemBitmap;

    /// This Items ID
    std::string mID;

    /// This Items col position in tiles
    double mCol = 50;

    /// This Items row position in tiles
    double mRow = 10.8333;

    /// This Items height
    double mHeight;

    /// This Items width
    double mWidth;

    /// The type of item this is
    wxString mType;

    /// Eaten or not
    int mEatenFlag = 0;

public:

    Item(Game *game, const std::wstring &filename, std::shared_ptr<wxImage> itemImage, wxGraphicsBitmap itemBitmap, std::string id, double col, double row, double height, double width,wxString type);

    /**
     * Getter for ID
     * @return mID
     */
    std::string GetID() const { return mID; }

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetCol() const { return mCol; }

    /**
     * Gets the type of the ite,
     * @return returns a wxString of the type of the item
     */
    wxString GetType() const { return mType;}

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetRow() const { return mRow; }

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetWidth() const { return mWidth; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetHeight() const { return mHeight; }

    /**
     * The value of the item
     * @return value of item from 0-9
     */
    virtual int GetVal() const {return 0;}


    /**
     * get if the the item has been eaten
     * @return an int of whether or not the item has been eaten
     */
    int GetEaten(){return mEatenFlag ;}

    /**
     * gets the game the item is associated with
     * @return pointer to the game the item is in
     */
    Game* GetGame() const { return mGame; }

    /**
     * gets the filename of the image
     * @return std::wstring of the filename of the image
     */
    std::wstring GetFileName() const { return mFileName; }

    /**
     * Get the image of the item
     * @return std::shared_ptr<wxImage> of the image of the item
     */
    std::shared_ptr<wxImage> GetItemImage() const { return mItemImage; }

    /**
     * Get the bitmap of the item
     * @return wxGraphicsBitmap of the bitmap of the item
     */
    wxGraphicsBitmap GetItemBitmap() const { return mItemBitmap; }


    /**
     * Set the item location
     * @param x X location in tiles
     * @param y Y location in tile
     */
    virtual void SetLocation(double x, double y) { mCol = x; mRow = y; }

    /**
     * Sets the height of the item
     * @param height the new height of the item
     */
    virtual void SetHeight(double height){mHeight = height;}

    /**
     * Sets the width of the item
     * @param width the new width of the item
     */
    virtual void SetWidth(double width){mWidth = width;}

    /**
     * Sets the eaten value of the item
     * @param eaten new int to set mEatenFlag to
     */
    virtual void SetEaten(int eaten){mEatenFlag = eaten;}

    /**
     * Load the data in the XML file
     * @param node
     * @param decFlag
     */
    virtual void XmlLoad(wxXmlNode *node, bool decFlag);

    virtual void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode);

    /**
     * Test this item to see if it has been clicked on
     * @param x X location on the game to test
     * @param y Y location on the game to test
     * @return true if clicked on
     */
    virtual bool HitTest(double x, double y);

    ///  Handle updates for animation
    /// @param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);

    /**
     * Accept a visitor
      * @param visitor The visitor we accept
      */
    virtual void Accept(ItemVisitor* visitor) {}

};

#endif //PROJECT1_SUDOKULIB_ITEM_H
