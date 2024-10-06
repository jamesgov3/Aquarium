/**
 * @file Aquarium.h
 * @author James Gove
 *
 * Describes the Aquarium class.
 */
 
#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <memory>
#include <vector>
#include <random>

class Item;

/**
 * Declaration of Aquarium, the main representation of the aquarium application
 */
class Aquarium {
private:
    /// Background image to use when drawn
    std::unique_ptr<wxBitmap> mBackground;

    /// All the items that populate this aquarium
    std::vector<std::shared_ptr<Item>> mItems;

    /// Random number generator
    std::mt19937 mRandom;

    void XmlItem(wxXmlNode* node);

public:
    Aquarium();

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * Get the width of the aquarium
     * @return Aquarium width in pixels
     */
    int GetWidth() const { return mBackground->GetWidth(); }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in pixels
     */
    int GetHeight() const { return mBackground->GetHeight(); }

    void OnDraw(wxDC* dc);
    void Add(std::shared_ptr<Item> item);
    void ReAdd(std::shared_ptr<Item> item);
    void Clear();
    void Update(double elapsed);
    void Save(const wxString& filename);
    void Load(const wxString& filename);
    std::shared_ptr<Item> HitTest(int x, int y);
};


#endif //AQUARIUM_H
