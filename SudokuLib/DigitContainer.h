/**
 * @file DigitContainer.h
 * @author trang
 *
 *
 */
#include "Item.h"
#include "Digit.h"
#include "Game.h"
#ifndef PROJECT1_SUDOKULIB_DIGITCONTAINER_H
#define PROJECT1_SUDOKULIB_DIGITCONTAINER_H

/**
 * Class for digit container items
 */
class DigitContainer : public Item
{
private:
    /// The list of digits stored in the DigitContainer
    std::vector<std::shared_ptr<Item>> mDigits;

    /// The front image
    std::shared_ptr<wxImage>mBackImage;

    /// The front bitmap
    wxGraphicsBitmap mBackBitmap;

    /// The  back image
    std::shared_ptr<wxImage>mFrontImage;

    /// The back bitmap
    wxGraphicsBitmap mFrontBitmap;

    /// Offset of the columns when drawing the DigitContainer
    double mColOffset = -1;

    /// Offset of the rows when drawing the DigitContainer
    double mRowOffset = -2;

    /// Flag to determine breaking sequence
    bool mSpecial;

    /// Stopwatch to measure time between breaks
    wxStopWatch mStopWatch;


public:
    DigitContainer(Game *game, const std::wstring &filename, const std::wstring &frontFilename, std::string id, double height, double width, wxString type, bool special);
    DigitContainer(Game *game,
                   const std::wstring &filename,
                   std::shared_ptr<wxImage> backImage,
                   std::shared_ptr<wxImage> frontImage,
                   wxGraphicsBitmap itemBitmap,
                   std::string id,
                   double col,
                   double row,
                   double height,
                   double width,
                   wxString type,
                   bool special);

    void Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode* node) override;

    virtual void Break();

    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

    void AddDigit(std::shared_ptr<Item> digit);

    /**
     * Gets the front image of the DigitContainer
     * @return a pointer to the front image of the DigitContainer
     */
    std::shared_ptr<wxImage> GetFrontImage() { return mFrontImage; }
};

#endif //PROJECT1_SUDOKULIB_DIGITCONTAINER_H
