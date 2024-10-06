/**
 * @file AquariumView.cpp
 * @author James Gove
 */

#include "pch.h"
#include "ids.h"
#include <wx/dcbuffer.h>
#include "AquariumView.h"
#include "DecorCastle.h"
#include "FishBeta.h"
#include "FishSparty.h"
#include "FishBubbles.h"

using namespace std;

/**
 * Initialize the Aquarium View class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishSpartyFish, this, IDM_ADDFISHSPARTY);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBubblesFish, this, IDM_ADDFISHBUBBLES);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastleDecor, this, IDM_ADDDECORCASTLE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mAquarium.Update(elapsed);

    mAquarium.OnDraw(&dc);
}

/**
 * Event handler for wxTimer event
 *
 * Refreshes the window for each Timer event
 * @param event Timer event
 */
void AquariumView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Menu handler for Save As...
 * @param event Mouse event
 */
void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
            L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mAquarium.Save(filename);
}

/**
 * File > Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
            L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mAquarium.Load(filename);
    Refresh();
}

/**
 * Menu handler for Add Fish > Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu handler for Add Fish > Sparty Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishSpartyFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishSparty>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu handler for Add Fish > Bubbles Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBubblesFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBubbles>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu handler for Add Decor > Castle Decor
 * @param event Mouse event
 */
void AquariumView::OnAddDecorCastleDecor(wxCommandEvent& event)
{
    auto decor = make_shared<DecorCastle>(&mAquarium);
    mAquarium.Add(decor);
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        mAquarium.ReAdd(mGrabbedItem);
    }
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to move it while left button is down
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When left button released, release item too
            mGrabbedItem = nullptr;
        }

        // Force redraw
        Refresh();
    }
}

