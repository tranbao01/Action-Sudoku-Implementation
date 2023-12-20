/**
 * @file Given.h
 * @author joshc
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_GIVEN_H
#define PROJECT1_SUDOKULIB_GIVEN_H

#include "Item.h"
#include "ItemVisitor.h"

/**
 * Describes a given item
 */
class Given : public Item
{
private:

    /// Value of the given
    int mValue;

public:

    Given(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int val);

    Given(Game *game, const std::wstring &filename, std::shared_ptr<wxImage> itemImage, wxGraphicsBitmap itemBitmap, std::string id, double col, double row, double height, double width,wxString type, int val);

    void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode) override;

    void Accept(ItemVisitor* visitor) override;

    /**
     * Getter for val
     * @return mValue
     */
    int GetVal() {return mValue;}
};

#endif //PROJECT1_SUDOKULIB_GIVEN_H
