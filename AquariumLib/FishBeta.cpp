/**
 * @file FishBeta.cpp
 * @author James Gove
 */

#include "pch.h"
#include <random>
#include "FishBeta.h"
#include "Aquarium.h"

using namespace std;

/// Fish image pathname
const wstring FishBetaImageName = L"images/beta.png";

/// Maximum speed in the X direction in
/// pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 40;

/**
 * Constructor for a Beta Fish
 * @param aquarium 
 */
FishBeta::FishBeta(Aquarium* aquarium) : Fish(aquarium, FishBetaImageName)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    SetSpeed(distributionX(aquarium->GetRandom()), 0);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"beta");

    return itemNode;
}

