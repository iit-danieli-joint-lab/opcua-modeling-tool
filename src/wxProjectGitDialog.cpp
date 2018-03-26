#include "opcutils.h"
#include "wxProjectGitDialog.h"
#include "wxLogin.h"
#include "simpleJSON/JSON.h"

#include <fstream>
#include <wx/msgdlg.h>
#include <wx/uri.h>
#include <wx/filedlg.h>
#include <wx/fileconf.h>
#include <wx/base64.h>
#include <wx/buffer.h>
#include <wx/stdpaths.h>

using namespace std;

//(*InternalHeaders(wxProjectGitDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxProjectGitDialog)
const long wxProjectGitDialog::ID_STATICBOX1 = wxNewId();
const long wxProjectGitDialog::ID_STATICBOX2 = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT1 = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT2 = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT3 = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT4 = wxNewId();
const long wxProjectGitDialog::ID_REPOOWNER = wxNewId();
const long wxProjectGitDialog::ID_BRANCH = wxNewId();
const long wxProjectGitDialog::ID_FILE = wxNewId();
const long wxProjectGitDialog::ID_USERNAME = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT5 = wxNewId();
const long wxProjectGitDialog::ID_PROJECTFILE = wxNewId();
const long wxProjectGitDialog::ID_BUTTON1 = wxNewId();
const long wxProjectGitDialog::ID_STATICBOX3 = wxNewId();
const long wxProjectGitDialog::ID_BUTTON2 = wxNewId();
const long wxProjectGitDialog::ID_BUTTON3 = wxNewId();
const long wxProjectGitDialog::ID_REPO = wxNewId();
const long wxProjectGitDialog::ID_STATICTEXT6 = wxNewId();
const long wxProjectGitDialog::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxProjectGitDialog,wxDialog)
	//(*EventTable(wxProjectGitDialog)
	//*)
END_EVENT_TABLE()

wxProjectGitDialog::wxProjectGitDialog(wxString &gitUsername, wxString &gitPassword, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) : GitUsername(gitUsername), GitPassword(gitPassword)
{
	//(*Initialize(wxProjectGitDialog)
	Create(parent, wxID_ANY, _("Project Settings (Github)"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(724,243));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,0), wxSize(704,144), 0, _T("ID_STATICBOX1"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,144), wxSize(704,40), 0, _T("ID_STATICBOX2"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Repo Owner"), wxPoint(40,16), wxSize(96,25), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Branch"), wxPoint(48,66), wxSize(88,25), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Github File Path"), wxPoint(16,92), wxSize(120,25), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Username"), wxPoint(40,114), wxSize(96,25), wxALIGN_RIGHT, _T("ID_STATICTEXT4"));
	txtRepoOwner = new wxTextCtrl(this, ID_REPOOWNER, wxEmptyString, wxPoint(152,16), wxSize(272,21), 0, wxDefaultValidator, _T("ID_REPOOWNER"));
	txtBranch = new wxTextCtrl(this, ID_BRANCH, wxEmptyString, wxPoint(152,64), wxSize(272,21), 0, wxDefaultValidator, _T("ID_BRANCH"));
	txtGithubFile = new wxTextCtrl(this, ID_FILE, wxEmptyString, wxPoint(152,88), wxSize(552,21), 0, wxDefaultValidator, _T("ID_FILE"));
	txtProjectFile = new wxTextCtrl(this, ID_USERNAME, wxEmptyString, wxPoint(152,156), wxSize(520,21), 0, wxDefaultValidator, _T("ID_USERNAME"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("UMX GIT Project File"), wxPoint(16,160), wxSize(122,21), wxALIGN_RIGHT, _T("ID_STATICTEXT5"));
	txtUsername = new wxTextCtrl(this, ID_PROJECTFILE, wxEmptyString, wxPoint(152,112), wxSize(272,21), 0, wxDefaultValidator, _T("ID_PROJECTFILE"));
	btnFileLookup = new wxButton(this, ID_BUTTON1, _("..."), wxPoint(680,156), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, wxEmptyString, wxPoint(8,184), wxSize(704,48), 0, _T("ID_STATICBOX3"));
	btnSave = new wxButton(this, ID_BUTTON2, _("Save"), wxPoint(520,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnClose = new wxButton(this, ID_BUTTON3, _("Close"), wxPoint(616,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	txtRepo = new wxTextCtrl(this, ID_REPO, wxEmptyString, wxPoint(152,40), wxSize(272,21), 0, wxDefaultValidator, _T("ID_REPO"));
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Repository"), wxPoint(48,42), wxSize(88,25), wxALIGN_RIGHT, _T("ID_STATICTEXT6"));
	btnOpen = new wxButton(this, ID_BUTTON4, _("Open Github FIle"), wxPoint(400,200), wxSize(107,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectGitDialog::OnbtnFileLookupClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectGitDialog::OnbtnSaveClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectGitDialog::OnbtnCloseClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectGitDialog::OnbtnOpenClick);
	//*)

	//Tab ordering
	txtRepo->MoveAfterInTabOrder(txtRepoOwner);
	txtBranch->MoveAfterInTabOrder(txtRepo);
	txtGithubFile->MoveAfterInTabOrder(txtBranch);
	txtUsername->MoveAfterInTabOrder(txtGithubFile);
	txtProjectFile->MoveAfterInTabOrder(txtUsername);

	txtRepoOwner->SetFocus();
}

wxProjectGitDialog::~wxProjectGitDialog()
{
	//(*Destroy(wxProjectGitDialog)
	//*)
}


void wxProjectGitDialog::OnbtnCloseClick(wxCommandEvent& event)
{
    this->EndModal(wxID_CANCEL);
}

bool wxProjectGitDialog::Save()
{
    if (this->txtRepoOwner->GetValue() == "")
    {
        ::wxMessageBox("Repository Owner is required.", "Error");
        this->txtRepoOwner->SetFocus();
        return false;
    }

    if (this->txtRepo->GetValue() == "")
    {
        ::wxMessageBox("Repository is required.", "Error");
        this->txtRepo->SetFocus();
        return false;
    }

    if (this->txtBranch->GetValue() == "")
    {
        ::wxMessageBox("Branch is required.", "Error");
        this->txtBranch->SetFocus();
        return false;
    }

    if (this->txtGithubFile->GetValue() == "")
    {
        ::wxMessageBox("Github file path is required.", "Error");
        this->txtGithubFile->SetFocus();
        return false;
    }

    if (this->txtUsername->GetValue() == "")
    {
        ::wxMessageBox("Username is required.", "Error");
        this->txtUsername->SetFocus();
        return false;
    }

    if (this->txtProjectFile->GetValue() == "")
    {
        ::wxMessageBox("UMX GIT Project File to save this project is required.", "Error");
        this->txtProjectFile->SetFocus();
        return false;
    }

    //TODO: Download bas64 file
    //      Save to temp file
    //      Open the temp file
    //      Add project type: github or local
    //      Set the global project settings with the type github so that save will behave differently
    wxFileConfig config(wxEmptyString, wxEmptyString, this->txtProjectFile->GetValue(),
                        wxEmptyString, wxCONFIG_USE_GLOBAL_FILE);
    config.Write("repo.owner", this->txtRepoOwner->GetValue());
    config.Write("repo", this->txtRepo->GetValue());
    config.Write("branch", this->txtBranch->GetValue());
    config.Write("github.file.path", this->txtGithubFile->GetValue());
    config.Write("username", this->txtUsername->GetValue());

    return true;
}
void wxProjectGitDialog::OnbtnSaveClick(wxCommandEvent& event)
{
    if (Save())
        ::wxMessageBox("Successfully saved.", "Project Settings (Github)");
}

void wxProjectGitDialog::OpenGitProjectFile(wxString projectFile)
{
    wxFileConfig config(wxEmptyString, wxEmptyString, projectFile,
                        wxEmptyString, wxCONFIG_USE_GLOBAL_FILE);
    wxString tempVal;
    if (config.Read("repo.owner", &tempVal))
        this->txtRepoOwner->SetValue(tempVal);
    if (config.Read("repo", &tempVal))
        this->txtRepo->SetValue(tempVal);
    if (config.Read("branch", &tempVal))
        this->txtBranch->SetValue(tempVal);
    if (config.Read("github.file.path", &tempVal))
        this->txtGithubFile->SetValue(tempVal);
    if (config.Read("username", &tempVal))
        this->txtUsername->SetValue(tempVal);
    this->txtProjectFile->SetValue(projectFile);
}

void wxProjectGitDialog::OnbtnFileLookupClick(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this,
                                _("Save As"), "", "",
                                _("Github UMX files (*.github.umx)|*.github.umx"), wxFD_SAVE);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    struct stat buffer;
    if (   stat(openFileDialog.GetPath().ToAscii(), &buffer) == 0
        && wxYES != wxMessageBox("File already exists. Do you want to overwrite it?", "Confirm Overwrite",
                                 wxYES_NO|wxNO_DEFAULT, this))
        return;

    this->txtProjectFile->SetValue(openFileDialog.GetPath());
}

void wxProjectGitDialog::OnbtnOpenClick(wxCommandEvent& event)
{
    bool successful = false;

    if (!Save())
        return;

    wxLogin login(this);
    login.txtUsername->SetValue(this->txtUsername->GetValue());
    if (   login.ShowModal() == wxID_OK
        && login.LoginSuccessful)
    {
        GitUsername = login.txtUsername->GetValue();
        GitPassword = login.txtPassword->GetValue();
        JSONValue *jsonValue = 0;
        wxURI url(wxString::Format("https://api.github.com/repos/%s/%s/contents/%s",
                                 this->txtRepoOwner->GetValue(),
                                 this->txtRepo->GetValue(),
                                 this->txtGithubFile->GetValue()
                                 ));
        if (OPCUtils::GithubConnect(this->txtUsername->GetValue(), login.txtPassword->GetValue(),
                                    wxString::Format("-X GET -d '{\"branch\": \"%s\"}' \"%s\"",
                                                     this->txtBranch->GetValue(), url.BuildURI()),
                                    &jsonValue))
        {
            JSONObject root = jsonValue->AsObject();
            if (   root.find(L"sha") != root.end()
                && root[L"sha"]->IsString())
            {
                successful = true;
                //File content
                wxMemoryBuffer memBuff = wxBase64Decode(root[L"content"]->AsString().c_str(), wxBase64DecodeMode_Relaxed);
                wxString uaXML = wxString(memBuff);

                //Get file sha which will be used for updating the file
                this->GitSHA = root[L"sha"]->AsString().c_str();
                cout << "sha:" << this->GitSHA << "\n";

                //Save github file to a temp file.
                wxFileName filename(wxStandardPaths::Get().GetTempDir(), "git_download.xml");
                ofstream file;
                file.open(filename.GetFullPath());
                file << uaXML.SubString(0, memBuff.GetDataLen()-1);
                file.close();

                GitFileToOpen = filename.GetFullPath();
            }
            else if (   root.find(L"message") != root.end()
                     && root[L"message"]->IsString())
                ::wxMessageBox(wxString::Format("Error: %s.", (root[L"message"]->AsString().c_str())), "Github");
            else
                ::wxMessageBox("Error: Unknown.", "Github");
        }

        if (jsonValue != 0)
            delete jsonValue;

        if (successful)
            this->EndDialog(0);
        else
            ::wxMessageBox("Failed to open github file.", "Github");
    }
}

