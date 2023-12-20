/**
 * @file Sparty.cpp
 * @author trang
 */

#include "pch.h"
#include "Sparty.h"
#include "Game.h"
#include <wx/graphics.h>
#include <wx/geometry.h>

using namespace std;

/// Character speed in pixels per second
const double maxSpeed =400.00;

/// The time for an eating cycles in seconds
const double eatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double headbuttTime = 0.5;

/**
 * Constructor for the sparty item
 * @param game game associated with the item
 * @param image1Filename filename of sparty's head
 * @param image2Filename filename of sparty's mouth
 * @param id item id
 * @param height height of the image
 * @param width width of the image
 * @param type type of the item
 * @param mouthPivotAngle angle sparty's mouth is set to
 * @param mouthPivotX pivot of sparty's mouth horizontally
 * @param mouthPivotY pivot of spart'y mouth vertically
 * @param headPivotAngle angle sparty's head is set to
 * @param headPivotX pivot of sparty's head horizontally
 * @param headPivotY pivot of spart'y head vertically
 * @param targetX target location x to move to
 * @param targetY target location y to move to
 * @param front front of sparty's head
 */
Sparty::Sparty(Game *game, const std::wstring &image1Filename, const std::wstring &image2Filename, std::string id, double height, double width,wxString type, double mouthPivotAngle, int mouthPivotX, int mouthPivotY, double headPivotAngle, int headPivotX, int headPivotY, wxDouble targetX, wxDouble targetY, int front)
    : Item(game, image1Filename, id, height, width,type)
{
    const std::wstring path1 = L"images/" + image1Filename;
    const std::wstring path2 = L"images/" + image2Filename;
    mImage1Filename = path1;
    mImage2Filename = path2;
    mHeadImage = make_shared<wxImage>(path1, wxBITMAP_TYPE_ANY);
    mMouthImage = make_shared<wxImage>(path2, wxBITMAP_TYPE_ANY);

    mMouthPivot.m_x = mouthPivotX;
    mMouthPivot.m_y = mouthPivotY;

    mHeadPivot.m_x = headPivotX;
    mHeadPivot.m_y = headPivotY;
    mMaxMouthPivotAngle = mouthPivotAngle;
    mMaxHeadPivotAngle = headPivotAngle;
    mTargetX = targetX;
    mTargetY = targetY;
    mFront = front;

    mLocation = wxPoint2DDouble(GetCol(),GetRow());
    mTarget = mLocation;
}

/**
 * Initialization constructor
 * @param game the game this sparty is associated with
 * @param filename filename for the sparty image
 * @param itemImage image of sparty
 * @param itemBitmap bitmap for sparty
 * @param id the id of the sparty item
 * @param col x location of sparty
 * @param row y location of sparty
 * @param height height of the image
 * @param width width of the image
 * @param mouthPivotAngle angle sparty's mouth is set to
 * @param mouthPivotX pivot of sparty's mouth horizontally
 * @param mouthPivotY pivot of spart'y mouth vertically
 * @param headPivotAngle angle sparty's head is set to
 * @param headPivotX pivot of sparty's head horizontally
 * @param headPivotY pivot of spart'y head vertically
 * @param targetX target location x to move to
 * @param targetY target location y to move to
 * @param front front of sparty's head
 */
Sparty::Sparty(Game *game,
               const std::wstring &filename,
               std::shared_ptr<wxImage> itemImage1,
               std::shared_ptr<wxImage> itemImage2,
               wxGraphicsBitmap itemBitmap,
               std::string id,
               double col,
               double row,
               double height,
               double width,
               wxString type,
               double mouthPivotAngle, int mouthPivotX,
               int mouthPivotY, double headPivotAngle,
               int headPivotX,
               int headPivotY,
               int targetX,
               int targetY,
               int front) : Item(game, filename, itemImage1, itemBitmap, id, col, row, height, width,type)
{
    mMaxMouthPivotAngle = mouthPivotAngle;
    mMouthPivot.m_x = mouthPivotX;
    mMouthPivot.m_y = (mouthPivotY);

    mMaxHeadPivotAngle = headPivotAngle;
    mHeadPivot.m_x = headPivotX;
    mHeadPivot.m_y = headPivotY;

    mTargetX = targetX;
    mTargetY = targetY;
    mFront = front;

    mHeadImage = itemImage1;
    mMouthImage = itemImage2;

    SetLocation(GetCol() * GetGame()->GetTileWidth(), (GetRow()+1)  * GetGame()->GetTileHeight()-GetHeight());
    mTarget = wxPoint2DDouble(GetCol(), GetRow());
    mLocation = wxPoint2DDouble(GetCol(),GetRow());
}

/**
 * Play the animation for sparty rotating his mouth
 */
void Sparty::RotateMouth()
{
    mMouthFlag = true;
    mEatingTime = 0;
}

/**
 * play the animation for sparty headbutting
 */
void Sparty::HeadButt()
{
    mHeadFlag = true;
    mHeadbuttTime = 0;
}

/**
 * Initialize sparty
 * @param items
 * @param col
 * @param row
 * @param PNode
 */
void Sparty::Initialize(std::vector<std::shared_ptr<Item>> *items, double col, double row, wxXmlNode *PNode)
{
    std::shared_ptr<Sparty> sparty = std::make_shared<Sparty>(GetGame(), GetFileName(), GetItemImage(), GetMouthImage(), GetItemBitmap(), GetID(), col, row, GetHeight(), GetWidth(),GetType(),mMaxMouthPivotAngle,mMouthPivot.m_x,mMouthPivot.m_y,mMaxHeadPivotAngle,mHeadPivot.m_x,mHeadPivot.m_y,mTargetX,mTargetY,mFront);
    items->push_back(sparty);
    GetGame()->SetSparty(sparty);
}

/**
 * Draws sparty
 * @param gc the wxGraphicsContext to draw on
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (mHeadImage == nullptr)
    {
        mHeadImage = make_shared<wxImage>(mImage1Filename, wxBITMAP_TYPE_ANY);
    }
    if (mMouthImage == nullptr)
    {
        mMouthImage = make_shared<wxImage>(mImage2Filename, wxBITMAP_TYPE_ANY);
    }
    mMouthBitmap = gc->CreateBitmapFromImage(*mMouthImage);
    mHeadBitmap = gc->CreateBitmapFromImage(*mHeadImage);
    gc->PushState();
    gc->Translate(mLocation.m_x,(mLocation.m_y));
    gc->Translate(mHeadPivot.m_x, mHeadPivot.m_y);
    gc->Rotate(mHeadPivotAngle);
    gc->Translate(-mHeadPivot.m_x, -mHeadPivot.m_y);

    gc->DrawBitmap(mHeadBitmap,0,0,GetWidth(),GetHeight());

    gc->Translate(mMouthPivot.m_x, mMouthPivot.m_y);
    gc->Rotate(mMouthPivotAngle);
    gc->Translate(-mMouthPivot.m_x, -mMouthPivot.m_y);

    gc->DrawBitmap(mMouthBitmap,0,0,GetWidth(),GetHeight());
    gc->PopState();
}

/**
 * Updates the sparty position before drawing
 * @param elapsed time in between last update
 */
void Sparty::Update(double elapsed)
{
    if(mMouthFlag)
    {
        double eatingTime2 = eatingTime / 2;

        mEatingTime += elapsed;
        if(mEatingTime < eatingTime2)
        {
            mMouthPivotAngle = (mEatingTime) / eatingTime2 * mMaxMouthPivotAngle;
        }

        if(mEatingTime >= eatingTime2)
        {
            mMouthPivotAngle = (eatingTime-mEatingTime) / eatingTime2 * mMaxMouthPivotAngle;
        }
        if (mEatingTime >= eatingTime)
        {
            mMouthFlag = false;
        }
    }
    if (mHeadFlag)
    {
        double headbuttTime2 = headbuttTime / 2;
        mHeadbuttTime += elapsed;
        if(mHeadbuttTime < headbuttTime2)
        {
            mHeadPivotAngle = (mHeadbuttTime) / headbuttTime2 * mMaxHeadPivotAngle;
        }
        if(mHeadbuttTime >= headbuttTime2)
        {
            mHeadPivotAngle = (headbuttTime - mHeadbuttTime) / headbuttTime2 * mMaxHeadPivotAngle;
        }
        if(mHeadbuttTime >= headbuttTime)
        {
            mHeadFlag = false;
        }
    }

    auto d = mTarget - mLocation;
    auto distanceToMove = d.GetVectorLength();
    d.Normalize();
    d = d * maxSpeed;
    auto distanceMoved  = d.GetVectorLength();
    if(distanceMoved * elapsed< distanceToMove)
    {
        mLocation += d*elapsed;
    }

    SetLocation(mLocation.m_x, mLocation.m_y);
}