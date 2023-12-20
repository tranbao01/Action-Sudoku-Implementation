/**
 * @file Given.cpp
 * @author joshc
 */

#include "pch.h"
#include "Given.h"


/**
 * Constructs an instance of the Given class with parameters
 * Invokes the base item class
 *
 * @param game
 * @param filename
 * @param id
 * @param height
 * @param width
 * @param type
 * @param val
 */
Given::Given(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int val) : Item(
    game,
    filename,
    id,
    height,
    width,type)
{
    mValue = val;
}

/**
 * Invokes the base Item class to construct an instance of Given object
 *
 * @param game
 * @param filename
 * @param itemImage
 * @param itemBitmap
 * @param id
 * @param col
 * @param row
 * @param height
 * @param width
 * @param type
 * @param val
 */
Given::Given(Game *game,
             const std::wstring &filename,
             std::shared_ptr<wxImage> itemImage,
             wxGraphicsBitmap itemBitmap,
             std::string id,
             double col,
             double row,
             double height,
             double width,wxString type,
             int val) : Item(game, filename, itemImage, itemBitmap, id, col, row, height, width,type)
{
    mValue = val;
}

/**
 * Initialize the givens class and add to list of items
 * @param items
 * @param col
 * @param row
 * @param PNode
 */

void Given::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode)
{
    items->push_back(std::make_shared<Given>(GetGame(), GetFileName(), GetItemImage(), GetItemBitmap(), GetID(), col, row, GetHeight(), GetWidth(),GetType(), mValue));
}

/**
 * accepts visitors
 * @param visitor the visitor to accept
 */
void Given::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitGiven(this);
}
