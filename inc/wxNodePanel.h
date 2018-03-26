#ifndef WXNODEPANEL_H
#define WXNODEPANEL_H

//(*Headers(wxNodePanel)
#include <wx/panel.h>
//*)

class wxNodePanel: public wxPanel
{
	public:

		wxNodePanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxNodePanel();

		//(*Declarations(wxNodePanel)
		//*)

	protected:

		//(*Identifiers(wxNodePanel)
		//*)

	private:

		//(*Handlers(wxNodePanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
