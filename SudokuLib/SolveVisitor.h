/**
 * @file SolveVisitor.h
 * @author joshc
 */

#ifndef PROJECT1_SUDOKULIB_SOLVEVISITOR_H
#define PROJECT1_SUDOKULIB_SOLVEVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"

/**
 * Visitor that assisits with Game::Solve
 */
class SolveVisitor : public ItemVisitor
{
private:

    /// if digit has been found
    bool mDigitFound = false;
    /// The target value to search for
    int mTargetVal;
    /// The digit found
    Digit* mDig = nullptr;

public:

    /// Constructor
    SolveVisitor(int val);

    /**
     * Vists a Digit item
     * @param digit the Digit we are visiting
     */
    void VisitDigit(Digit* digit) override;

    /**
     * Getter for digit found
     * @return mDigitFound
     */
    bool GetDigitFound() { return mDigitFound; }

    /**
     * Getter for val
     * @return mVal
     */
    int GetVal() {return mTargetVal;}

    /**
     * Setter for the target value
     * @param x
     */
    void SetTarget(int x) {mTargetVal = x;}

    /**
     * Setter for digit found
     * @param found
     */
    void SetDigitFound(bool found) {  mDigitFound = found; }

    /**
     * Getter for the found digit
     * @return
     */
    Digit* GetDigit() { return mDig; }
};

#endif //PROJECT1_SUDOKULIB_SOLVEVISITOR_H
