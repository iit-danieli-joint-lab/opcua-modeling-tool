/***************************************************************
 * Name:      wxOPCUAApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2017-04-22
 * Copyright:  ()
 * License:
 **************************************************************/

#include <wxOPCUAApp.h>

//(*AppHeaders
#include "wxFrameMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxOPCUAApp);

bool wxOPCUAApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxFrameMain* Frame = new wxFrameMain(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    #ifndef DEBUG_CONSOLE
    #ifdef __WIN32__
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif
    #endif

    return wxsOK;

}
