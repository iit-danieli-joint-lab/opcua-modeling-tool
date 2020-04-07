#include "wxCompileDialog.h"
#include "wxTreeDialog.h"
#include "opcglobal.h"
#include "opcutils.h"

#include <vector>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/dirdlg.h>

//(*InternalHeaders(wxCompileDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(wxCompileDialog)
const long wxCompileDialog::ID_STATICBOX1 = wxNewId();
const long wxCompileDialog::ID_STATICTEXT1 = wxNewId();
const long wxCompileDialog::ID_TEXTCTRL1 = wxNewId();
const long wxCompileDialog::ID_STATICTEXT2 = wxNewId();
const long wxCompileDialog::ID_STATICBOX2 = wxNewId();
const long wxCompileDialog::ID_BUTTON1 = wxNewId();
const long wxCompileDialog::ID_BUTTON2 = wxNewId();
const long wxCompileDialog::ID_TEXTCTRL3 = wxNewId();
const long wxCompileDialog::ID_STATICTEXT3 = wxNewId();
const long wxCompileDialog::ID_COMBOBOX1 = wxNewId();
const long wxCompileDialog::ID_BUTTON3 = wxNewId();
const long wxCompileDialog::ID_CHECKBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxCompileDialog,wxDialog)
	//(*EventTable(wxCompileDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxCompileDialog::wxCompileDialog(std::string projectFile, wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size) : m_projectFile(projectFile)
{
	//(*Initialize(wxCompileDialog)
	Create(parent, wxID_ANY, _("UA Model Compiler"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(421,197));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,8), wxSize(408,128), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Output Directory"), wxPoint(16,32), wxSize(90,15), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	txtOutputDir = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(112,32), wxSize(256,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Identifiers Output"), wxPoint(15,64), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,136), wxSize(408,48), 0, _T("ID_STATICBOX2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("Compile"), wxPoint(256,152), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Exit"), wxPoint(336,152), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	txtIdentifiersOutput = new wxTextCtrl(this, ID_TEXTCTRL3, _("Identifiers.csv"), wxPoint(112,64), wxSize(176,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Output Type"), wxPoint(39,96), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	cboOutputType = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(112,96), wxSize(256,21), 0, 0, wxCB_READONLY|wxCB_DROPDOWN, wxDefaultValidator, _T("ID_COMBOBOX1"));
	btnLookup = new wxButton(this, ID_BUTTON3, _("..."), wxPoint(376,32), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	chkForceOverwrite = new wxCheckBox(this, ID_CHECKBOX1, _("Force Overwrite"), wxPoint(296,70), wxSize(108,13), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkForceOverwrite->SetValue(false);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCompileDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCompileDialog::OnbtnCancelClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxCompileDialog::OnbtnLookupClick);
	//*)

    //Tab ordering
	txtIdentifiersOutput->MoveAfterInTabOrder(txtOutputDir);
	cboOutputType->MoveAfterInTabOrder(txtIdentifiersOutput);
	txtOutputDir->SetFocus();

    wxArrayString cboList;
    cboList.Add("C#");
    cboList.Add("AnsiC");
    cboList.Add("Stack");
    this->cboOutputType->Set(cboList);
    this->cboOutputType->SetSelection(0);

    //Default output directory
    wxFileName fOutDir(wxStandardPaths::Get().GetDocumentsDir());
	this->txtOutputDir->SetValue(wxString::Format("%soutput", fOutDir.GetPathWithSep()));
}

wxCompileDialog::~wxCompileDialog()
{
	//(*Destroy(wxCompileDialog)
	//*)
}

void wxCompileDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void wxCompileDialog::OnbtnOKClick(wxCommandEvent& event)
{
    if (this->txtOutputDir->GetValue() == "")
    {
        ::wxMessageBox("Output directory is required.", "UA Model Compiler");
        txtOutputDir->SetFocus();
        return;
    }

    if (this->txtIdentifiersOutput->GetValue() == "")
    {
        ::wxMessageBox("Identifier Output file is required.", "UA Model Compiler");
        txtIdentifiersOutput->SetFocus();
        return;
    }

    /* Output command line switch */
    string outputSwitch = " ";
    string outputSubDir = " ";
    if (cboOutputType->GetValue() == "C#")
    {
        outputSwitch = " -o ";
        outputSubDir = "CSharp";
    }
    else if (cboOutputType->GetValue() == "AnsiC")
    {
        outputSwitch = " -ansic ";
        outputSubDir = "AnsiC";
    }
    else if (cboOutputType->GetValue() == "Stack")
    {
        outputSwitch = " -stack ";
        outputSubDir = "Stack";
    }

    /* Output directory */
    string outDirectory = txtOutputDir->GetValue().ToStdString();
    //Make sure we append path separator at the end, otherwise it will be treated as a file.
    if (outDirectory.size()-1 !=  outDirectory.rfind(wxString::Format("%c", wxFileName::GetPathSeparator())))
        outDirectory = wxString::Format("%s%c", outDirectory, wxFileName::GetPathSeparator()).ToStdString();
    cout << "outDirectory : " << outDirectory << endl;
    wxFileName fOutDir(outDirectory);
	if (!fOutDir.DirExists())
    {
        if (!wxFileName::Mkdir(outDirectory))
        {
            ::wxMessageBox("Failed creating output directory.", "UA Model Compiler");
            return;
        }
    }

    /* Output subdirectory */
    string outSubDirectory = wxString::Format("%s%s%c", outDirectory, outputSubDir, wxFileName::GetPathSeparator()).ToStdString();
    cout << "outSubDirectory : " << outSubDirectory << endl;
    wxFileName fOutSubDir(outSubDirectory);
	if (!fOutSubDir.DirExists())
    {
        if (!wxFileName::Mkdir(outSubDirectory))
        {
            ::wxMessageBox("Failed creating output subdirectory.\n", "UA Model Compiler");
            return;
        }
    }

    string outUniqueIdentFile = "Identifier.csv";
    if (this->txtIdentifiersOutput->GetValue() != "")
        outUniqueIdentFile = this->txtIdentifiersOutput->GetValue();

    wxFileConfig config("umx_config.ini");
    wxString compilerBin = config.Read("compiler.executable", "");
    cout << "compilerBin from config: " << compilerBin << endl;
    if (compilerBin == "")
    {
        wxFileName fCompiler(wxStandardPaths::Get().GetExecutablePath());

        #ifdef __WXMSW__
            compilerBin = wxString::Format("%s\\ModelCompiler\\Opc.Ua.ModelCompiler.exe", fCompiler.GetPath());
        #else
            compilerBin = wxString::Format("%sModelCompiler/Opc.Ua.ModelCompiler", fCompiler.GetPathWithSep());
        #endif //

        cout <<"compilerBin using default: " << compilerBin << endl;
    }

    wxFileName fCompilerBin(compilerBin);
    if (!fCompilerBin.Exists())
    {
        ::wxMessageBox(wxString::Format("Could not locate compiler: %s\nMake sure to specify the full path and the filename.",compilerBin), "UA Model Compiler");
        return;
    }

    wxString identSwitch;
    wxFileName fIdentifier(fOutDir.GetFullPath(), outUniqueIdentFile);
    if (   this->chkForceOverwrite->GetValue()
        || !fIdentifier.FileExists())
        identSwitch = "-cg";
    else
        identSwitch = "-c";

    wxString compilerCmd = wxString::Format("\"%s\" -d2 \"%s\" %s \"%s\" %s \"%s%s\"",
                                            compilerBin, m_projectFile, outputSwitch, fOutSubDir.GetFullPath(), identSwitch, fOutDir.GetFullPath(), outUniqueIdentFile);
    cout << "compilerCmd: " << compilerCmd << endl;

    this->SetCursor(wxCursor(wxCURSOR_WAIT));

    /* TODO: If we may want to run it asynchronously. May be not, this runs fast enough.
    wxEvtHandler *eventHandler = NULL;
    wxProcess *proc = new wxProcess(eventHandler);
    proc->Redirect();
    wxInputStream* stdErr = proc->GetErrorStream();
    wxInputStream* stdOut = proc->GetInputStream();
    */

    /* Execute command synchronously. */
    long runResult = wxExecute(compilerCmd, wxEXEC_SYNC);
    cout << "runResult: " << runResult << endl;
    this->SetCursor(wxCursor(wxCURSOR_DEFAULT));

    if (runResult == 0)
        ::wxMessageBox("Compilation successful.\n", "UA Model Compiler");
    else
        ::wxMessageBox("Compilation failed.\n", "UA Model Compiler");
}


void wxCompileDialog::OnbtnLookupClick(wxCommandEvent& event)
{
    wxDirDialog selectDirDialog(this);

    if (selectDirDialog.ShowModal() == wxID_CANCEL)
        return;

    this->txtOutputDir->SetValue(selectDirDialog.GetPath());
}
