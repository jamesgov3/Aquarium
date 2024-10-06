/**
 * @file Fish.h
 * @author James Gove
 *
 * Describes the Fish class
 */

#ifndef FISH_H
#define FISH_H

#include "item.h"

/**
 * Base class for a fish
 * This applies to all the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

    void SetSpeed(const double speedX, const double speedY);

    wxXmlNode* XmlSave(wxXmlNode* node);
    void XmlLoad(wxXmlNode* node) override;

protected:
    Fish(Aquarium *aquarium, const std::wstring &filename);
    void Update(double elapsed);
};



#endif //FISH_H
