/**
 * @file Sparty.h
 * @author trang
 *
 *
 */
#include "Item.h"

#include <wx/graphics.h>
#ifndef PROJECT1_SUDOKULIB_SPARTY_H
#define PROJECT1_SUDOKULIB_SPARTY_H

/**
 * a sparty item in the game
 */
class Sparty : public Item
{
private:

    /// Max number in degrees sparty can roate his mouth to
    double mMaxMouthPivotAngle;

    /// Current angle sparty's mouth is pivoted at
    double mMouthPivotAngle;

    /// Sparty's mouth pivot as a wxPoint2DDouble
    wxPoint2DDouble mMouthPivot;

    /// Max number in degrees sparty can roate his head to
    double mMaxHeadPivotAngle;

    /// Current angle sparty's head is pivoted at
    double mHeadPivotAngle;

    /// Sparty's head pivot as a wxPoint2DDouble
    wxPoint2DDouble mHeadPivot;

    /// Time it takes sparty to finish the eating animation
    double mEatingTime;

    /// Time it takes sparty to finish the headbut animation
    double mHeadbuttTime;

    /// X value for sparty to move to
    wxDouble mTargetX;

    /// Y value for sparty to move to
    wxDouble mTargetY;

    /// The front of sparty
    int mFront;

    /// flag for if sparty needs to move his mouth
    bool mMouthFlag = false ;

    /// flag for if sparty needs to move his head
    bool mHeadFlag = false;

    /// Filename of sparty's first image
    std::wstring mImage1Filename;

    /// Filename of sparty's second image
    std::wstring mImage2Filename;

    /// The head image
    std::shared_ptr<wxImage>mHeadImage;

    /// The head bitmap
    wxGraphicsBitmap mHeadBitmap;

    /// The  mouth image
    std::shared_ptr<wxImage>mMouthImage;

    /// The mouth bitmap
    wxGraphicsBitmap mMouthBitmap;

    /// The current location of Sparty
    wxPoint2DDouble mLocation;

    /// Where we want Sparty to go
    wxPoint2DDouble mTarget;

    /// flag for if sparty is trying to spit
    int mSpit;

public:

    Sparty(Game *game, const std::wstring &image1Filename, const std::wstring &image2Filename, std::string id, double height, double width,wxString type, double mouthPivotAngle, int mouthPivotX, int mouthPivotY, double headPivotAngle, int headPivotX, int headPivotY, wxDouble targetX, wxDouble targetY, int front);

    Sparty(Game *game,
           const std::wstring &filename,
           std::shared_ptr<wxImage> itemImage,
           std::shared_ptr<wxImage> itemImage2,
           wxGraphicsBitmap itemBitmap,
           std::string id,
           double col,
           double row,
           double height,
           double width,
           wxString type,
           double mouthPivotAngle,
           int mouthPivotX,
           int mouthPivotY,
           double headPivotAngle,
           int headPivotX,
           int headPivotY,
           int targetX,
           int targetY,
           int front);

    /**
     * Gets the image for sparty's mouth
     * @return a shared ptr to the wxImage of sparty's mouth
     */
    std::shared_ptr<wxImage> GetMouthImage() { return mMouthImage; }

    /**
     * Gets the flag for sparty's head
     * @return integer of either 0 or 1 for if sparty's head should be rotated
     */
    bool GetHeadFlag() {return mHeadFlag;}

    /**
     * Sets the target for sparty to move to
     * @param target the x and y coordinates for sparty to move to
     */
    void SetTarget(wxPoint2DDouble target) { mTarget.m_x = target.m_x-mTargetX  ; mTarget.m_y = target.m_y-mTargetY*3; }

    /**
     * Sets a flag for if sparty is about to spit
     * @param spit an int thats saying which number sparty is trying to spit
     */
    void SetSpit(int spit) {mSpit = spit;}

    /**
     * gets whether or not sparty is trying to spit
     * @return an int that is either 0 or 1 saying if sparty is trying to spit
     */
    int GetSpit() {return mSpit;}

    void Initialize(std::vector<std::shared_ptr<Item>> *item, double col, double row, wxXmlNode *PNode) override ;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void Update(double elapsed) override;
    void RotateMouth();
    void HeadButt();
};


#endif //PROJECT1_SUDOKULIB_SPARTY_H
