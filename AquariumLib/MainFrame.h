/**
 * @file MainFrame.h
 * @author James Gove
 *
 * Defines the MainFrame class.
 */
 
#ifndef MAINFRAME_H
#define MAINFRAME_H


/**
 * Declaration of the MainFrame class.
 *
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    void OnExit(wxCommandEvent&);
    void DisplayAbout(wxCommandEvent&);

public:
    void Initialize();

};


#endif //MAINFRAME_H
