/**
* @file Background.cpp
* @author Josh Costantino
*/

#include "pch.h"
#include "Background.h"

/**
 * Constructs an instance of the Background class with parameters
 * Invokes the base item class
 *
 * @param game
 * @param filename
 * @param id
 * @param height
 * @param width
 * @param type
 */
Background::Background(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type) : Item(
    game,
    filename,
    id,
    height,
    width,type)
{

}
/**
 * Invokes the base Item class to construct an instance of Background object
 *
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
 */
Background::Background(Game *game,
                       const std::wstring &filename,
                       std::shared_ptr<wxImage> itemImage,
                       wxGraphicsBitmap itemBitmap,
                       std::string id,
                       double col,
                       double row,
                       double height,
                       double width,wxString type) : Item(game, filename, itemImage, itemBitmap, id, col, row, height, width,type)
{

}

/**
 * Initialize the background class and add to list of items
 *
 * @param items
 * @param col
 * @param row
 * @param PNode
 */
void Background::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode)
{
    items->push_back(std::make_shared<Background>(GetGame(), GetFileName(), GetItemImage(), GetItemBitmap(), GetID(), col, row, GetHeight(), GetWidth(),GetType()));
}

