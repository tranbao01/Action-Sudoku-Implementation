/**
 * @file ItemVisitor.h
 * @author trang
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEMVISITOR_H
#define PROJECT1_SUDOKULIB_ITEMVISITOR_H

class Item;
class Digit;
class Given;


/**
 * Base call for all visitors to items
 */
class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:
    /**
     * Deconstructor
     */
    virtual ~ItemVisitor() {}

    /**
     * Visits a Digit item
     * @param digit the Digit we are visiting
     */
    virtual void VisitDigit(Digit* digit){}

    /**
     * Visits a Given item
     * @param given the Given we are visiting
     */
    virtual void VisitGiven(Given* given){}


};

#endif //PROJECT1_SUDOKULIB_ITEMVISITOR_H
