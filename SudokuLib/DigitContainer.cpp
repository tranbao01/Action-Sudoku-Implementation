/**
 * @file DigitContainer.cpp
 * @author trang
 */

#include "pch.h"
#include "DigitContainer.h"
#include "Game.h"
#include <wx/graphics.h>

/**
 * Constructor for DigitContainer as an Item
 * @param game game associated with the container
 * @param backFilename Filename of back image
 * @param frontFilename Filename of front image
 * @param id id of the container
 * @param height height of the image on screen
 * @param width width of the image on screen
 * @param type type of the DigitContainer
 * @param special
 */
DigitContainer::DigitContainer(Game *game, const std::wstring &backFilename, const std::wstring &frontFilename, std::string id, double height, double width, wxString type, bool special) : Item(
    game,
    backFilename,
    id,
    height,
    width,
    type)
{
    const std::wstring path1 = L"images/" + backFilename;
    const std::wstring path2 = L"images/" + frontFilename;
    mBackImage = std::make_shared<wxImage>(path1, wxBITMAP_TYPE_ANY);
    mFrontImage = std::make_shared<wxImage>(path2, wxBITMAP_TYPE_ANY);
    mSpecial = special;
}

/**
 * Constructor for DigitContainer
 * @param game game associated with the container
 * @param filename filename of the container
 * @param backImage the image of the back of the container
 * @param frontImage the image to be displayed as the front of the container
 * @param itemBitmap Bitmap of the container
 * @param id id of the container
 * @param col where the container is located on the x axis
 * @param row where the container is located on the y axis
 * @param height height of the image on screen
 * @param width width of the image on screen
 * @param type type of the DigitContainer
 * @param special
 */
DigitContainer::DigitContainer(Game *game,
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
                               bool special) : Item(game, filename, backImage, itemBitmap, id, col, row, height, width, type)
{
    mBackImage = backImage;
    mFrontImage = frontImage;
    mSpecial = special;
}

/**
 * Initializer for the DigitContainer
 * @param items items to put into the container
 * @param col x location of the DigitContainer
 * @param row y location of the DigitContainer
 * @param node node to populate the DigitContainer
 */
void DigitContainer::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode* node)
{
    std::shared_ptr<DigitContainer> Item;

    Item = std::make_shared<DigitContainer>(GetGame(),
                                            GetFileName(),
                                            GetItemImage(),
                                            GetFrontImage(),
                                            GetItemBitmap(),
                                            GetID(),
                                            col,
                                            row,
                                            GetHeight(),
                                            GetWidth(),
                                            GetType(),
                                            mSpecial);
    wxXmlNode* containerChild;
    containerChild = node->GetChildren();
    for( ; containerChild; containerChild=containerChild->GetNext())
    {
        GetGame()->XmlItem(containerChild);
        Item->AddDigit(items->at(items->size()-1));
        items->pop_back();
    }
    items->push_back(Item);
}

/**
 * Adds a digit to the container
 * @param digit Digit to add to the container
 */
void DigitContainer::AddDigit(std::shared_ptr<Item> digit)
{
    mDigits.push_back(digit);
}

/**
 * Draws the container
 * @param gc wxGraphicsContext to draw the DigitContainer on
 */
void DigitContainer::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    gc->PushState();
    if(mBackBitmap.IsNull())
    {
        mBackBitmap = gc->CreateBitmapFromImage(*mBackImage);
    }
    if(mFrontBitmap.IsNull())
    {
        mFrontBitmap = gc->CreateBitmapFromImage(*mFrontImage);
    }
    gc->DrawBitmap(mBackBitmap,GetCol() * GetGame()->GetTileWidth(), (GetRow() + 1) * GetGame()->GetTileHeight() - GetHeight(),GetWidth(),GetHeight());
    for (std::shared_ptr<Item> i : mDigits)
        {
            i->Draw(gc);
        }
    gc->DrawBitmap(mFrontBitmap,GetCol() * GetGame()->GetTileWidth(), (GetRow() + 1) * GetGame()->GetTileHeight() - GetHeight(),GetWidth(),GetHeight());

    if (GetGame()->GetSparty()->GetHeadFlag()== true && this->HitTest(GetGame()->GetSparty()->GetCol()-this->GetWidth()*3/4, GetGame()->GetSparty()->GetRow()-this->GetHeight()))
    {
        this->Break();
    }
    gc->PopState();
}

/**
 * Breaks the DigitContainer depending on the type of container
 */
void DigitContainer::Break()
{
    if (mSpecial && mStopWatch.Time() > 1000 && mDigits.size() != 0)
    {
        GetGame()->Add(std::make_shared<Digit>(GetGame(),
                                               mDigits.at(mDigits.size()-1)->GetFileName(),
                                               mDigits.at(mDigits.size()-1)->GetItemImage(),
                                               mDigits.at(mDigits.size()-1)->GetItemBitmap(),
                                               mDigits.at(mDigits.size()-1)->GetID(),
                                               mDigits.at(mDigits.size()-1)->GetCol() + mColOffset-2,
                                               mDigits.at(mDigits.size()-1)->GetRow(),
                                               mDigits.at(mDigits.size()-1)->GetHeight(),
                                               mDigits.at(mDigits.size()-1)->GetWidth(),
                                               mDigits.at(mDigits.size()-1)->GetType(),
                                               mDigits.at(mDigits.size()-1)->GetVal()));
        mDigits.pop_back();
        mStopWatch = wxStopWatch();
    }
    else if (!mSpecial)
    {
        for(auto i : mDigits)
        {
            mColOffset -= 4;
            mColOffset *= -.85;
            mRowOffset -= .5;
            auto g = std::make_shared<Digit>(GetGame(),
                                             i->GetFileName(),
                                             i->GetItemImage(),
                                             i->GetItemBitmap(),
                                             i->GetID(),
                                             i->GetCol() + mColOffset,
                                             i->GetRow() + mRowOffset,
                                             i->GetHeight(),
                                             i->GetWidth(),
                                             i->GetType(),
                                             i->GetVal());
            GetGame()->Add(g);
        }
        mDigits.clear();
    }
}