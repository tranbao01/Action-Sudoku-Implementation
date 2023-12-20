/**
 * @file GivenCheck.cpp
 * @author joshc
 */

#include "pch.h"
#include "GivenCheck.h"

/**
 * constructor for GivenCheck
 * @param targetX
 * @param targetY
 */
GivenCheck::GivenCheck(double targetX, double targetY)
{
    mTargetX = targetX;
    mTargetY = targetY;
}

/**
 * visits a given
 * @param given the given being visited
 */
void GivenCheck::VisitGiven(Given *given)
{
    if(!mGivenFound && given->GetCol() == mTargetX && given->GetRow() == mTargetY)
    {
        mGivenFound = true;
        mVal = given->GetVal();
    }

}
