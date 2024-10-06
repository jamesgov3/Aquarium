/**
 * @file AquariumApp.cpp
 * @author James Gove
 */

#include "pch.h"
#include <MainFrame.h>
#include "AquariumApp.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif // WIN32

/**
 * Initialize the application.
 * @return
 */
bool AquariumApp::OnInit()
{
    // Memory leak detection
    #ifdef WIN32
    _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif // WIN32

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Initialize App Frame
    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
