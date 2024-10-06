/**
 * @file FishSparty.cpp
 * @author James Gove
 */

#include "pch.h"
#include <random>
#include "FishSparty.h"
#include "Aquarium.h"

using namespace std;

/// Fish image pathname
const wstring FishSpartyImageName = L"images/sparty-fish.png";

/// Maximum speed in the X direction in
/// pixels per second
const double MaxSpeedX = 20;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 10;

/**
 * Constructor for a Sparty Fish
 * @param aquarium
 */
FishSparty::FishSparty(Aquarium* aquarium) : Fish(aquarium, FishSpartyImageName)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    SetSpeed(distributionX(aquarium->GetRandom()), 0);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishSparty::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);
 itemNode->AddAttribute(L"type", L"sparty");

 return itemNode;
}

