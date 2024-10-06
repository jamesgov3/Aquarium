/**
* @file FishBubbles.cpp
 * @author James Gove
 */

#include "pch.h"
#include <random>
#include "FishBubbles.h"
#include "Aquarium.h"

using namespace std;

/// Fish image pathname
const wstring FishBubblesImageName = L"images/bubbles.png";

/// Maximum speed in the X direction in
/// pixels per second
const double MaxSpeedX = 100;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 80;

/**
 * Constructor for a Bubbles Fish
 * @param aquarium
 */
FishBubbles::FishBubbles(Aquarium* aquarium) : Fish(aquarium, FishBubblesImageName)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    SetSpeed(distributionX(aquarium->GetRandom()), 0);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBubbles::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);
 itemNode->AddAttribute(L"type", L"bubbles");

 return itemNode;
}

