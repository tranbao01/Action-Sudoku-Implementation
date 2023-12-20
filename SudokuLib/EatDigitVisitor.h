/**
 * @file EatDigitVisitor.h
 * @author joshc
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_EATDIGITVISITOR_H
#define PROJECT1_SUDOKULIB_EATDIGITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"
#include "Sparty.h"
#include "Game.h"

/**
 * Visitor that assists in sparty eating
 */
class EatDigitVisitor : public ItemVisitor
{
private:

    /// The games sparty
    std::shared_ptr<Sparty> mSparty;

    /// The game's Xray
    std::shared_ptr<Xray> mXray;
    /// If the Digit has been eaten
    bool mAte = false;

    /// Digit to eat
    Digit* eatenDig;


public:

    EatDigitVisitor(std::shared_ptr<Sparty> sparty,std::shared_ptr<Xray> xray);

    void VisitDigit(Digit* dig) override;

    /**
     * Get the digit to eat
     * @return the digit for the sparty to eat
     */
    Digit* GetEatenDig() { return eatenDig; };

    /**
     * see if the digit has already been eaten
     * @return boolean value that is true if the value has already been eaten
     */
    bool GetAte() { return mAte; }

};

#endif //PROJECT1_SUDOKULIB_EATDIGITVISITOR_H
