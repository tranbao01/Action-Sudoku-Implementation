/**
 * @file DigitSpitVisitor.cpp
 * @author joshc
 */

#include "pch.h"
#include "DigitSpitVisitor.h"

/**
 * Constructor for DigitSpitVisitor
 * @param targetVal target value to for sparty to spit
 */
DigitSpitVisitor::DigitSpitVisitor(int targetVal)
{
    mTargetVal = targetVal;
}

/**
 * visits a digit and spits if it is eaten, and if is the correct value
 * @param dig digit we are visiting
 */
void DigitSpitVisitor::VisitDigit(Digit *dig)
{
    if(dig->GetEaten() && !mDigFound && dig->GetVal() == mTargetVal)
    {
        mDigit = dig;
        dig->SetEaten(false);
        mDigFound = true;
    }
}
