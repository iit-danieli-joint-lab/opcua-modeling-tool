#include "wxAbout.h"
#include <fstream>
#include <iostream>
//(*InternalHeaders(wxAbout)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxAbout)
const long wxAbout::ID_BUTTON1 = wxNewId();
const long wxAbout::ID_STATICTEXT1 = wxNewId();
const long wxAbout::ID_STATICTEXT2 = wxNewId();
const long wxAbout::ID_STATICTEXT3 = wxNewId();
const long wxAbout::ID_STATICTEXT4 = wxNewId();
const long wxAbout::ID_STATICTEXT5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxAbout,wxDialog)
	//(*EventTable(wxAbout)
	//*)
END_EVENT_TABLE()

wxAbout::wxAbout(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxAbout)
	Create(parent, wxID_ANY, _("About UMX"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(400,146));
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(304,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	//txtBeeondLink = new wxHyperlinkCtrl(this, ID_STATICTEXT1, _("www.beeond.net"), wxPoint(184,72), wxSize(96,16), 0, _T("ID_STATICTEXT1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Copyright (c) 2017"), wxPoint(184,48), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	lblAppNameAndVersion = new wxStaticText(this, ID_STATICTEXT3, _("UA Model eXcelerator ver. unknown"), wxPoint(184,24), wxSize(208,13), 0, _T("ID_STATICTEXT3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("UMX"), wxPoint(8,16), wxSize(88,72), 0, _T("ID_STATICTEXT4"));
	wxFont StaticText3Font(48,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText3->SetFont(StaticText3Font);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT5, _("Label"), wxPoint(160,192), wxDefaultSize, 0, _T("ID_STATICTEXT5"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxAbout::OnbtnOKClick);
	//*)

	//Always comment txtBeeondLink inside the wxsmith generated code.
	txtBeeondLink = new wxHyperlinkCtrl(this, ID_STATICTEXT1, _("www.beeond.net"), _("www.beeond.net"), wxPoint(184,72), wxSize(96,16), 0, _T("ID_STATICTEXT1"));
    try
    {
        std::ifstream verFile;
        verFile.open("version.txt");

        std::string appVersion;
        std::getline(verFile, appVersion);
        appVersion.replace(appVersion.find(","), 1, ".");
        appVersion = "UA Model eXcelerator ver. " + appVersion;
        lblAppNameAndVersion->SetLabel(appVersion);
        verFile.close();
    }catch (...)
    {
        std::cerr << "wxAbout Error: Failed to open version.txt\n";
    }


}

wxAbout::~wxAbout()
{
	//(*Destroy(wxAbout)
	//*)
}


void wxAbout::OnbtnOKClick(wxCommandEvent& event)
{
    this->EndDialog(wxID_OK);
}
