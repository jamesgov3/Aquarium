/**
 * @file MainFrame.cpp
 * @author James Gove
 */

#include "pch.h"
#include "ids.h"
#include "AquariumView.h"
#include "MainFrame.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Aquarium",
           wxDefaultPosition, wxSize(1000,800));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto *aquariumView = new AquariumView();
    aquariumView->Initialize(this);

    // Add it to the sizer
    sizer->Add(aquariumView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto fishMenu = new wxMenu();
    auto decorMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save aquarium as...");
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open aquarium file...");

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::DisplayAbout, this, wxID_ABOUT);

    fishMenu->Append(IDM_ADDFISHBETA, L"&Beta Fish", L"Add a Beta Fish");
    fishMenu->Append(IDM_ADDFISHSPARTY, L"&Sparty Fish", L"Add a Sparty Fish");
    fishMenu->Append(IDM_ADDFISHBUBBLES, L"&Bubbles Fish", L"Add a Bubbles Fish");

    decorMenu->Append(IDM_ADDDECORCASTLE, L"&Castle Decor", L"Add a Decorative Castle");

    menuBar->Append( fileMenu, L"&File" );
    menuBar->Append( fishMenu, L"&AddFish" );
    menuBar->Append( decorMenu, L"&AddDecor" );
    menuBar->Append( helpMenu, L"&Help" );


    SetMenuBar( menuBar );

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

/**
 * Dialogue box for About menu
 * @param event
 */
void MainFrame::DisplayAbout(wxCommandEvent &event)
{
    wxMessageBox(L"Welcome to the Aquarium!",
    L"About Aquarium",
        wxOK,
        this);
}
