/**
 * @file DigitSpitVisitor.h
 * @author joshc
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_DIGITSPITVISITOR_H
#define PROJECT1_SUDOKULIB_DIGITSPITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"

/**
 * Visitor that aids in sparty spitting
 */
class DigitSpitVisitor : public ItemVisitor
{
private:
    /// Value that the user intends to spit
    int mTargetVal;

    /// If the digit is found
    bool mDigFound = false;

    /// Digit the user will spit
    Digit* mDigit;

public:

    DigitSpitVisitor(int targetVal);

    void VisitDigit(Digit* dig) override;

    /**
     *  @return Getter for DigFound
     */
    bool GetDigFound() { return mDigFound; }

    /**
     * @return the digit the user should spit
     */
    Digit* GetDigToSpit() { return mDigit; }

};

#endif //PROJECT1_SUDOKULIB_DIGITSPITVISITOR_H
