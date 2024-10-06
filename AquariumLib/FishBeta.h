/**
 * @file FishBeta.h
 * @author James Gove
 *
 * Defines the FishBeta class
 */
 
#ifndef FISHBETA_H
#define FISHBETA_H

#include "Fish.h"

/**
 * Declaration of the FishBeta class, which is a derivative of Item class.
 *
 * Initializes a FishBeta Item which belongs to an Aquarium.
 */
class FishBeta : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator (disabled)
    void operator=(const FishBeta &) = delete;

    FishBeta(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};


#endif //FISHBETA_H
