/**
 * @file DecorCastle.h
 * @author James Gove
 *
 * Describes the DecorCastle class
 */
 
#ifndef DECORCASTLE_H
#define DECORCASTLE_H

#include "Item.h"


/**
 * Definition of the DecorCastle class
 */
class DecorCastle : public Item {
private:

public:
    /// Default constructor (disabled)
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle &) = delete;

    /// Assignment operator (disabled)
    void operator=(const DecorCastle &) = delete;

    DecorCastle(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};


#endif //DECORCASTLE_H
