#include "opcutils.h"
#include "wxLogin.h"
#include "simpleJSON/JSON.h"

#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/process.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/txtstrm.h>

using namespace std;
//(*InternalHeaders(wxLogin)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxLogin)
const long wxLogin::ID_STATICBOX1 = wxNewId();
const long wxLogin::ID_STATICBOX2 = wxNewId();
const long wxLogin::ID_STATICTEXT1 = wxNewId();
const long wxLogin::ID_STATICTEXT2 = wxNewId();
const long wxLogin::ID_TEXTCTRL1 = wxNewId();
const long wxLogin::ID_TEXTCTRL2 = wxNewId();
const long wxLogin::ID_BUTTON1 = wxNewId();
const long wxLogin::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxLogin,wxDialog)
	//(*EventTable(wxLogin)
	//*)
END_EVENT_TABLE()

wxLogin::wxLogin(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxLogin)
	Create(parent, id, _("Github Login"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,134));
	Move(wxDefaultPosition);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,0), wxSize(384,80), 0, _T("ID_STATICBOX1"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,80), wxSize(384,48), 0, _T("ID_STATICBOX2"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Username"), wxPoint(24,16), wxSize(80,13), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Password"), wxPoint(24,40), wxSize(80,13), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	txtUsername = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(120,16), wxSize(200,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	txtPassword = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(120,40), wxSize(200,21), wxTE_PROCESS_ENTER|wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("Ok"), wxPoint(192,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(296,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&wxLogin::OntxtPasswordTextEnter);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxLogin::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxLogin::OnbtnCancelClick);
	//*)

	this->txtPassword->SetFocus();
}

wxLogin::~wxLogin()
{
	//(*Destroy(wxLogin)
	//*)
}

void wxLogin::ExecuteLogin()
{
    LoginSuccessful = false;

    if (   this->txtUsername->GetValue() == ""
        || this->txtPassword->GetValue() == "" )
    {
        ::wxMessageBox("Username and Password are required.", "Login Error");
        return;
    }

    JSONValue *jsonValue = 0;
    if (OPCUtils::GithubConnect(this->txtUsername->GetValue(), this->txtPassword->GetValue(),
                                "https://api.github.com/",
                                &jsonValue))
    {
        JSONObject root = jsonValue->AsObject();
        if (   root.find(L"current_user_url") != root.end()
            && root[L"current_user_url"]->IsString())
        {
            LoginSuccessful = true;
            cout << "current_user_url: " << (root[L"current_user_url"]->AsString().c_str()) << "\n";
            wxMessageBox("Access granted.", "Github Login");
        }
    }

    if (jsonValue != 0)
        delete jsonValue;

    if (!LoginSuccessful)
    {
        wxMessageBox("Access denied.", "Github Login");
        this->txtPassword->SetFocus();
    }
    else
        this->EndModal(wxID_OK);
}

void wxLogin::OnbtnOKClick(wxCommandEvent& event)
{
    ExecuteLogin();
}

void wxLogin::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(wxID_CANCEL);
}

void wxLogin::OntxtPasswordTextEnter(wxCommandEvent& event)
{
    ExecuteLogin();
}
