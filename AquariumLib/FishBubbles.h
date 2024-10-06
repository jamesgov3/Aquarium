/**
* @file FishBubbles.h
 * @author James Gove
 *
 * Defines the FishBubbles class
 */

#ifndef FISHBUBBLES_H
#define FISHBUBBLES_H

#include "Fish.h"

/**
 * Declaration of the FishBubbles class, which is a derivative of Item class.
 *
 * Initializes a FishBubbles Item which belongs to an Aquarium.
 */
class FishBubbles : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishBubbles() = delete;

    /// Copy constructor (disabled)
    FishBubbles(const FishBubbles &) = delete;

    /// Assignment operator (disabled)
    void operator=(const FishBubbles &) = delete;

    FishBubbles(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};


#endif //FISHBUBBLES_H
