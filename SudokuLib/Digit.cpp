/**
 * @file Digit.cpp
 * @author trang
 */

#include "pch.h"
#include "Digit.h"
#include "ItemVisitor.h"

/**
 * Constructs an instance of the Digit class with parameters
 * Invokes the base item class
 *
 * @param game
 * @param filename
 * @param id
 * @param height
 * @param width
 * @param val
 * @param type
 */
Digit::Digit(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int val) : Item(
    game,
    filename,
    id,
    height,
    width,type)
{
   mValue = val;
}

/**
 * Initialize the digit class and add to list of items
 *
 * @param items
 * @param col
 * @param row
 * @param node
 */
void Digit::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *node)
{
    items->push_back(std::make_shared<Digit>(GetGame(), GetFileName(), GetItemImage(), GetItemBitmap(), GetID(), col, row, GetHeight(), GetWidth(),GetType(), mValue));
}


void Digit::Accept(ItemVisitor *visitor)
{
    Item::Accept(visitor);
    visitor->VisitDigit(this);
}

