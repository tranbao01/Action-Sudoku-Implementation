/**
 * @file GivenCheck.h
 * @author joshc
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_GIVENCHECK_H
#define PROJECT1_SUDOKULIB_GIVENCHECK_H

#include "ItemVisitor.h"
#include "Given.h"

/**
 * Visitor that checks if a given item is in a particular location
 */
class GivenCheck : public ItemVisitor
{
private:

    /// The col to check
    double mTargetX;
    /// The row to check
    double mTargetY;

    /// true if given is at that location
    bool mGivenFound = false;

    /// The value of the digit found
    int mVal;

public:

    GivenCheck(double targetX, double targetY);

    void VisitGiven(Given* given) override;

    /**
     * Getter for mGivenFound
     * @return mGivenFound
     */
    bool GetGivenFound() { return mGivenFound; }

    /**
     * Setter for mGivenFound
     * @param found
     */
    void SetGivenFound(bool found) {  mGivenFound = found; }

    /**
     * Getter for val
     * @return mVal
     */
    int GetVal() {return mVal;}

    /**
     * Setter target
     * @param x
     * @param y
     */
    void SetTarget(int x, int y) { mTargetX = x; mTargetY = y; }

    /**
     * Setter for val
     * @param x
     */
    void SetVal(int x) {mVal = x;}

};

#endif //PROJECT1_SUDOKULIB_GIVENCHECK_H
