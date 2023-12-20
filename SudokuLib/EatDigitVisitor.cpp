/**
 * @file EatDigitVisitor.cpp
 * @author joshc
 */

#include "pch.h"
#include "EatDigitVisitor.h"

/// offset of every TilePixel
const int TilePixelOffset = 20;

/**
 * Digitor that visits a digit whenever the user intends to eat a digit
 * @param sparty the sparty Item in the game
 * @param xray
 */
EatDigitVisitor::EatDigitVisitor(std::shared_ptr<Sparty> sparty,std::shared_ptr<Xray> xray)
{
    mSparty = sparty;
    mXray = xray;
}

/**
 * Visit a Digit and eat it if it is not eaten, and not a given
 * @param dig digit we intend to visit
 */
void EatDigitVisitor::VisitDigit(Digit* dig)
{
    if (dig->HitTest((mSparty->GetCol())+TilePixelOffset , (mSparty->GetRow())+TilePixelOffset) && dig->GetEaten() == 0 && !mAte&& mXray->GetSize()<= mXray->GetCap())
    {
        dig->SetEaten(1);
        mAte = true;
        eatenDig = dig;
        mXray->Add();
    }
}

