/**
 * @file DigitCheck.h
 * @author gymna
 */

#ifndef PROJECT1_SUDOKULIB_DIGITVISITOR_H
#define PROJECT1_SUDOKULIB_DIGITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"

/**
 * visitor that checks the value of a digit in a particular location
 */
class DigitCheck : public ItemVisitor
{
private:
    /// The target column
    double mTargetX;
    /// The target row
    double mTargetY;

    /// True if digit is there
    bool mDigitFound = false;
    /// The value of the target
    int mVal;

public:

    DigitCheck(double targetX, double targetY);
    /**
     * Vists a Digit item
     * @param digit the Digit we are visiting
     */
    void VisitDigit(Digit* digit) override;

    /**
     * Getter for mDigitFound
     * @return mDigitFound
     */
    bool GetDigitFound() { return mDigitFound; }
    /**
     * Getter for mVal
     * @return mVal
     */
    int GetVal() {return mVal;}
    /**
     * Setter for mVal
     * @param x what to set the val to
     */
    void SetVal(int x) {mVal = x;}
    /**
     * Setter for the target position
     * @param x the col of the target
     * @param y the row of the target
     */
    void SetTarget(int x, int y) { mTargetX = x; mTargetY = y; }
    /**
     * Setter for digit found
     * @param found
     */
    void SetDigitFound(bool found) {  mDigitFound = found; }

};

#endif //PROJECT1_SUDOKULIB_DIGITVISITOR_H
