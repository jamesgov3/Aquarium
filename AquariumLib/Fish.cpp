/**
 * @file Fish.cpp
 * @author James Gove
 */

#include "pch.h"
#include "Aquarium.h"
#include "Fish.h"

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    // Set Y speed
    // (Sine wave amplitude and period depend on mSpeedX, which is randomly generated)
    mSpeedY = mSpeedX*sin(GetX()/(2*M_PI));

    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);

    const int maxX = GetAquarium()->GetWidth() - 10 - mItemImage->GetWidth()/2;
    const int minX = 10 + mItemImage->GetWidth()/2;
    const int maxY = GetAquarium()->GetHeight() - 10 - mItemImage->GetHeight()/2;
    const int minY = 10 + mItemImage->GetHeight()/2;

    // Set limits for X location
    if (mSpeedX > 0 && GetX() >= maxX)
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }
    else if (mSpeedX < 0 && GetX() <= minX)
    {
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }

    // Set limits for Y location
    if (GetY() >= maxY)
    {
        SetLocation(GetX(), maxY);
    }
    else if (GetY() <= minY)
    {
        SetLocation(GetX(), minY);
    }
}

/**
 * Sets the speed of this fish
 * @param speedX speed of fish in X direction in pixels per second
 * @param speedY speed of fish in Y direction in pixels per second
 */
void Fish::SetSpeed(const double speedX, const double speedY)
{
    mSpeedX = speedX;
    mSpeedY = speedY;
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Fish::XmlSave(wxXmlNode *node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"speedx", wxString::FromDouble(mSpeedX));
    itemNode->AddAttribute(L"speedy", wxString::FromDouble(mSpeedY));

    return itemNode;
}

/**
 * Load fish-related attributes from XML file
 *
 * @param node The parent node we are loading the item from
 */
void Fish::XmlLoad(wxXmlNode *node)
{
    // Load mSpeedX and check if it needs to be mirrored
    node->GetAttribute(L"speedx").ToDouble(&mSpeedX);
    if(mSpeedX < 0)
    {
        SetMirror(true);
    }

    // Load mSpeedY and upcall to base class load to load basic item attributes
    node->GetAttribute(L"speedy").ToDouble(&mSpeedY);
    Item::XmlLoad(node);
}

