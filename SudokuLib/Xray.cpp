/**
 * @file Xray.cpp
 * @author trang
 */

#include "pch.h"
#include "Xray.h"
#include "Game.h"

/**
 * Constructs an instance of Xray class using basic parameters
 *
 *  @param game
 * @param filename
 * @param id
 * @param height
 * @param width
 * @param cap
 */
Xray::Xray(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int cap) : Item(
    game,
    filename,
    id,
    height,
    width,type)
{
    mCapacity = cap;
}

/**
 * Invokes the base Item class to construct an instance of Xray object
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
 * @param cap
 */
Xray::Xray(Game *game,
             const std::wstring &filename,
             std::shared_ptr<wxImage> itemImage,
             wxGraphicsBitmap itemBitmap,
             std::string id,
             double col,
             double row,
             double height,
             double width,
             wxString type,
             int cap) : Item(game, filename, itemImage, itemBitmap, id, col, row, height, width,type)
{
    mCapacity = cap;
}

/**
 * Initializer for the Xray, adds to items
 *
 * @param items
 * @param col
 * @param row
 * @param PNode
 */
void Xray::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode)
{
    std::shared_ptr<Xray> xray = std::make_shared<Xray>(GetGame(), GetFileName(), GetItemImage(), GetItemBitmap(), GetID(), col, row, GetHeight(), GetWidth(),GetType(), mCapacity);
    items->push_back(xray);
    GetGame()->SetXray(xray);
}

/**
 * Adds an item to the xray
 * @return if the xray successfully added the item
 */
void Xray::Add()
{
    if(mSize <= mCapacity)
    {
        mSize++;

    }

}

/**
 * Removes an item from the xray
 * @return if the xray successfully removed the item
 */
bool Xray::Spit()
{
    if(mSize > 0)
    {
        mSize--;
        return true;
    }
    return false;
}
