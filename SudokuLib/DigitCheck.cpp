/**
 * @file DigitCheck.cpp
 * @author gymna
 */

#include "pch.h"
#include "DigitCheck.h"
#include "Digit.h"

/**
 * Constructor
 * @param targetX
 * @param targetY
 */
DigitCheck::DigitCheck(double targetX, double targetY)
{
    mTargetX = targetX;
    mTargetY = targetY;
}
void DigitCheck::VisitDigit(Digit* digit)
{
    if(!mDigitFound && digit->GetCol() == mTargetX && digit->GetRow() == mTargetY)
    {
        mDigitFound = true;
        mVal = digit->GetVal();
    }
}


