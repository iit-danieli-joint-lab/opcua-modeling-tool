#include "../inc/wxNodePanel.h"

//(*InternalHeaders(wxNodePanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxNodePanel)
//*)

BEGIN_EVENT_TABLE(wxNodePanel,wxPanel)
	//(*EventTable(wxNodePanel)
	//*)
END_EVENT_TABLE()

wxNodePanel::wxNodePanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxNodePanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

wxNodePanel::~wxNodePanel()
{
	//(*Destroy(wxNodePanel)
	//*)
}

