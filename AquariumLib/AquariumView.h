/**
 * @file AquariumView.h
 * @author James Gove
 *
 * Defines the AquariumView class.
 */
 
#ifndef AQUARIUMVIEW_H
#define AQUARIUMVIEW_H


#include "Aquarium.h"

/// duration in milliseconds each "frame" will last before updating items
const int FrameDuration = 30;

/**
 * Declaration of the AquariumView class.
 *
 * Window class for our aquarium.
 */
class AquariumView : public wxWindow {
private:
    void OnPaint(wxPaintEvent &event);
    void OnTimer(wxTimerEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnAddFishBetaFish(wxCommandEvent& event);
    void OnAddFishSpartyFish(wxCommandEvent& event);
    void OnAddFishBubblesFish(wxCommandEvent& event);
    void OnAddDecorCastleDecor(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);

    /// An object that describes our aquarium
    Aquarium mAquarium;

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

    /// The timer to allow for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame *parent);

};


#endif //AQUARIUMVIEW_H
