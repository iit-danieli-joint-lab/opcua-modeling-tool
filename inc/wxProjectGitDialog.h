#ifndef WXPROJECTGITDIALOG_H
#define WXPROJECTGITDIALOG_H

//(*Headers(wxProjectGitDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class wxProjectGitDialog: public wxDialog
{
	public:

		wxProjectGitDialog(wxString &m_gitUsername, wxString &m_gitPassword, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxProjectGitDialog();

		//(*Declarations(wxProjectGitDialog)
		wxTextCtrl* txtRepoOwner;
		wxTextCtrl* txtProjectFile;
		wxButton* btnSave;
		wxStaticText* StaticText2;
		wxButton* btnClose;
		wxStaticText* StaticText6;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxTextCtrl* txtUsername;
		wxTextCtrl* txtBranch;
		wxStaticBox* StaticBox2;
		wxStaticText* StaticText5;
		wxTextCtrl* txtRepo;
		wxStaticBox* StaticBox3;
		wxTextCtrl* txtGithubFile;
		wxStaticText* StaticText4;
		wxButton* btnFileLookup;
		wxButton* btnOpen;
		//*)

	protected:

		//(*Identifiers(wxProjectGitDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_REPOOWNER;
		static const long ID_BRANCH;
		static const long ID_FILE;
		static const long ID_USERNAME;
		static const long ID_STATICTEXT5;
		static const long ID_PROJECTFILE;
		static const long ID_BUTTON1;
		static const long ID_STATICBOX3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_REPO;
		static const long ID_STATICTEXT6;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(wxProjectGitDialog)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnbtnCloseClick1(wxCommandEvent& event);
		void OnbtnSaveClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnbtnFileLookupClick(wxCommandEvent& event);
		void OnbtnOpenClick(wxCommandEvent& event);
		void OnbtnOpenClick1(wxCommandEvent& event);
		void OnbtnOpenClick2(wxCommandEvent& event);
		void OnbtnOpenClick3(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
        bool Save();

    public:
        wxString GitFileToOpen;
        wxString GitUsername;
        wxString GitPassword;
        wxString GitSHA;

    public:
        void OpenGitProjectFile(wxString projectFile);
};

#endif
