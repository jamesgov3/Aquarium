/**
 * @file FishSparty.h
 * @author James Gove
 *
 * Defines the FishSparty class
 */
 
#ifndef FISHSPARTY_H
#define FISHSPARTY_H

#include "Fish.h"

/**
 * Declaration of the FishSparty class, which is a derivative of Item class.
 *
 * Initializes a FishSparty Item which belongs to an Aquarium.
 */
class FishSparty : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishSparty() = delete;

    /// Copy constructor (disabled)
    FishSparty(const FishSparty &) = delete;

    /// Assignment operator (disabled)
    void operator=(const FishSparty &) = delete;

    FishSparty(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};


#endif //FISHSPARTY_H
