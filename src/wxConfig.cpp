#include "wxConfig.h"

#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>

//(*InternalHeaders(wxConfig)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxConfig)
const long wxConfig::ID_STATICBOX1 = wxNewId();
const long wxConfig::ID_STATICBOX2 = wxNewId();
const long wxConfig::ID_BUTTON1 = wxNewId();
const long wxConfig::ID_BUTTON2 = wxNewId();
const long wxConfig::ID_STATICTEXT1 = wxNewId();
const long wxConfig::ID_TEXTCTRL1 = wxNewId();
const long wxConfig::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxConfig,wxDialog)
	//(*EventTable(wxConfig)
	//*)
END_EVENT_TABLE()

using namespace std;

wxConfig::wxConfig(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxConfig)
	Create(parent, wxID_ANY, _("UMX Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(536,167));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,0), wxSize(520,112), 0, _T("ID_STATICBOX1"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,112), wxSize(520,48), 0, _T("ID_STATICBOX2"));
	btnSave = new wxButton(this, ID_BUTTON1, _("Save"), wxPoint(328,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnClose = new wxButton(this, ID_BUTTON2, _("Close"), wxPoint(424,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Compiler Executable"), wxPoint(16,34), wxSize(112,16), 0, _T("ID_STATICTEXT1"));
	txtExecutable = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(128,32), wxSize(352,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	btnCompilerPath = new wxButton(this, ID_BUTTON3, _("..."), wxPoint(488,32), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfig::OnbtnSaveClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfig::OnbtnCloseClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxConfig::OnbtnCompilerPathClick);
	//*)

    wxFileConfig config("umx_config.ini");
    wxString compilerBin = config.Read("compiler.executable", "");
    if (compilerBin == "")
    {
        wxFileName fCompiler(wxStandardPaths::Get().GetExecutablePath());

        #ifdef __WXMSW__
            compilerBin = wxString::Format("%s\\ModelCompiler\\Opc.Ua.ModelCompiler.exe", fCompiler.GetPath());
        #else
            compilerBin = wxString::Format("%sModelCompiler/Opc.Ua.ModelCompiler", fCompiler.GetPathWithSep());
        #endif // __WXMSW__

        cout <<"compilerBin using default: " << compilerBin << endl;
    }

    this->txtExecutable->SetValue(compilerBin);
}

wxConfig::~wxConfig()
{
	//(*Destroy(wxConfig)
	//*)
}

void wxConfig::OnbtnSaveClick(wxCommandEvent& event)
{
    wxFileConfig config("umx_config.ini");
    config.Write("compiler.executable", this->txtExecutable->GetValue());
    ::wxMessageBox("Successfully saved.", "UMX Settings");
}

void wxConfig::OnbtnCloseClick(wxCommandEvent& event)
{
     this->EndDialog(0);
}

void wxConfig::OnInit(wxInitDialogEvent& event)
{
}

void wxConfig::OnbtnCompilerPathClick(wxCommandEvent& event)
{
     wxFileDialog openFileDialog(this,
                                _("Compiler Executable"), "", "",
                                _("*"), wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
    this->txtExecutable->SetValue(openFileDialog.GetPath());
}
