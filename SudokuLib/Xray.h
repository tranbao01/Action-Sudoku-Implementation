/**
 * @file Xray.h
 * @author trang
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_XRAY_H
#define PROJECT1_SUDOKULIB_XRAY_H
#include "Item.h"

/**
 * class for an xray item
 */
class Xray : public Item
{
private:

    /// The maximum number of digits this Xray can hold
    int mCapacity;

    /// The current number of digits in the Xray
    int mSize = 0;

public:

    Xray(Game *game, const std::wstring &filename, std::string id, double height, double width,wxString type, int cap);

    Xray(Game *game, const std::wstring &filename, std::shared_ptr<wxImage> itemImage, wxGraphicsBitmap itemBitmap, std::string id, double col, double row, double height, double width,wxString type, int cap);

    void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode) override;

    void Add();

    bool Spit();

    /**
     * getter for size
     * @return mSize
     */
    int GetSize() {return mSize;};

    /**
     * Getter for capacity
     * @return capacity
     */
    int GetCap()  {return mCapacity;};

};

#endif //PROJECT1_SUDOKULIB_XRAY_H
