/**
 * @file Background.h
 * @author Josh Costantino
 *
 * Background objects to be displayed in the scene
 */

#ifndef PROJECT1_SUDOKULIB_BACKGROUND_H
#define PROJECT1_SUDOKULIB_BACKGROUND_H

#include "Item.h"

/**
 * Background objects to be displayed in the scene
 */
class Background : public Item
{

private:

public:

    Background(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type);

    Background(Game *game, const std::wstring &filename, std::shared_ptr<wxImage> itemImage, wxGraphicsBitmap itemBitmap, std::string id, double col, double row, double height, double width,wxString type);

    void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode) override;

};

#endif //PROJECT1_SUDOKULIB_BACKGROUND_H
