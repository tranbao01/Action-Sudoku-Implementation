/**
 * @file Digit.h
 * @author trang
 *
 * Class describing digit items
 */

#ifndef PROJECT1_SUDOKULIB_DIGIT_H
#define PROJECT1_SUDOKULIB_DIGIT_H

#include "Item.h"
#include "ItemVisitor.h"

/**
 * Class describing digit items
 */
class Digit : public Item
{
private:
    /// Value of the number
    int mValue;
    /// flag holding if the digit is on the board
    bool mOnBoard = false;

public:

    Digit(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int val);

    /**
     * Constuctor for Digit used when reading from the xml file
     * @param game the game associated with the digit
     * @param filename The filename of the digit
     * @param itemImage the image of the digit
     * @param itemBitmap the bitmap of the image
     * @param id the id of the image
     * @param col the col on screen where the digit is
     * @param row the row on screen where the digit is
     * @param height the height of the digit image
     * @param width the width of the digit image
     * @param val the value stored in the digit (0-9)
     * @param type
     */
    Digit(Game *game,
          const std::wstring &filename,
          std::shared_ptr<wxImage> itemImage,
          wxGraphicsBitmap itemBitmap,
          std::string id,
          double col,
          double row,
          double height,
          double width,
          wxString type,
          int val) : Item(game, filename, itemImage, itemBitmap, id, col, row, height, width,type)
    {
      mValue = val;
    }

    void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *node) override;

    /**
     * function to get the value of the digit
     * @return Returns the value of the digit
     */
    int GetVal() const override {return mValue;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override;

    /**
     * Setter for mOnBoard
     * @param onBoard
     */
    void SetOnBoard(bool onBoard) { mOnBoard = onBoard; }
    /**
     * Getter for mOnBoard
     * @return mOnBoard
     */
    bool GetOnBoard() { return mOnBoard; }

};

#endif //PROJECT1_SUDOKULIB_DIGIT_H
