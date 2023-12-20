/**
 * @file SolveVisitor.cpp
 * @author joshc
 */
#include "pch.h"

#include "pch.h"
#include "SolveVisitor.h"

/**
 *
 * @param val
 */
SolveVisitor::SolveVisitor(int val)
{
    mTargetVal = val;
}

/**
 * Visitor for Solve, Sees if there is a digit at the target location and if its not eaten
 * @param digit
 */
void SolveVisitor::VisitDigit(Digit *digit)
{
    if(!mDigitFound && digit->GetVal() == mTargetVal && !digit->GetOnBoard() && !digit->GetEaten())
    {
        mDigitFound = true;
        mDig = digit;
    }
}
