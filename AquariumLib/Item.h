/**
 * @file Item.h
 * @author James Gove
 *
 * Defines the Item base class.
 */
 
#ifndef ITEM_H
#define ITEM_H

// Forward reference to Aquarium to avoid circular dependency
class Aquarium;

/**
 * Declaration of the Item base class.
 *
 * Base class for any item in our Aquarium.
 */
class Item {
private:
    /// The aquarium this Item is contained in
    Aquarium *mAquarium;

    /// X-Coordinate for this Item in the aquarium
    double mX = 0;

    /// Y-Coordinate for this Item in the aquarium
    double mY = 0;

    bool mMirror = false;   ///< True mirrors the item image

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    virtual ~Item();

     /**
      * Get the pointer to the Aquarium object
      * @return Pointer to Aquarium object
      */
     Aquarium *GetAquarium() { return mAquarium; }

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }



    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    virtual void Draw(wxDC *dc);
    virtual bool HitTest(int x, int y);
    void SetMirror(bool m);
    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);

   protected:
    /// Main constructor for Item
    Item(Aquarium *aquarium, const std::wstring &filename);

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can use to display this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

};


#endif //ITEM_H
