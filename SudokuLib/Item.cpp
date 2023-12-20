/**
 * @file Item.cpp
 * @author trang
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <wx/graphics.h>

/**
 * Constructor for the item class
 * @param game
 * @param filename
 * @param id
 * @param height
 * @param width
 * @param type
 */
Item::Item(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type)
{
    mGame = game;
    const std::wstring path = L"images/" + filename;
    mItemImage = std::make_shared<wxImage>(path, wxBITMAP_TYPE_ANY);

    mID = id;
    mHeight = height;
    mWidth = width;
    mType = type;
}

/**
 * Constructor, initializes all values
 * @param game the game this item belongs to
 * @param filename the filename of the image to draw
 * @param itemImage the image to draw
 * @param itemBitmap the bitmap of the item
 * @param id the id of the item
 * @param col the x location of the item
 * @param row the y location of the item
 * @param height the hight of the item image
 * @param width the width of the item image
 * @param type the type of the item
 */
Item::Item(Game *game, const std::wstring &filename, std::shared_ptr<wxImage> itemImage, wxGraphicsBitmap itemBitmap, std::string id, double col, double row, double height, double width,wxString type)
{
    mGame = game;
    mFileName = filename;
    mItemImage = itemImage;
    mItemBitmap = itemBitmap;
    mID = id;
    mCol = col;
    mRow = row;
    mHeight = height;
    mWidth = width;
    mType = type;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 * @param decFlag a flag for a default bool
 */
void Item::XmlLoad(wxXmlNode *node, bool decFlag)
{
    node->GetAttribute(L"col", L"0").ToDouble(&mCol);
    node->GetAttribute(L"row", L"0").ToDouble(&mRow);

}

/**
 * Initializes a copy (except of image and bitmap) of this item at provided position (the image and bitmap are both passed as pointers to the created item)
 * @param items
 * @param col position
 * @param row position
 * @param PNode
 */
void Item::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode)
{
    items->push_back(std::make_shared<Item>(mGame, mFileName, mItemImage, mItemBitmap, mID, col, row, mHeight, mWidth,mType));
}

bool Item::HitTest(double x, double y)
{

    if(x <= mCol * mGame->GetTileWidth() && x >= mCol * mGame->GetTileWidth() - mWidth)
    {
        if(y <= ((mRow + 1) * mGame->GetTileHeight()) - (mHeight) && y >= ((mRow + 1) * mGame->GetTileHeight()) - (mHeight * 2))
        {
            return true;
        }
    }
    return false;
}

/**
 * Draw the tile.
 * @param gc Device context to draw the tile on
*/
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if(mItemBitmap.IsNull())
    {
        mItemBitmap = gc->CreateBitmapFromImage(*mItemImage);
    }
    gc->DrawBitmap(mItemBitmap, mCol * mGame->GetTileWidth(), (mRow + 1) * mGame->GetTileHeight() - mHeight, mWidth, mHeight);
}
