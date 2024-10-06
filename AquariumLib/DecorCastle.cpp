/**
 * @file DecorCastle.cpp
 * @author James Gove
 */

#include "pch.h"
#include "DecorCastle.h"

using namespace std;

/// Castle image pathname
const wstring DecorCastleImageName = L"images/castle.png";

/**
 * Constructor for a Castle Decor Item
 * @param aquarium
 */
DecorCastle::DecorCastle(Aquarium* aquarium) : Item(aquarium, DecorCastleImageName)
{
}

/**
 * Save this decor to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* DecorCastle::XmlSave(wxXmlNode* node)
{
 auto itemNode = Item::XmlSave(node);
 itemNode->AddAttribute(L"type", L"castle");

 return itemNode;
}

