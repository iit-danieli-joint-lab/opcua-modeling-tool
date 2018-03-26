#ifndef WXLOGIN_H
#define WXLOGIN_H

//(*Headers(wxLogin)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class wxLogin: public wxDialog
{
	public:

		wxLogin(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxLogin();

		//(*Declarations(wxLogin)
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxTextCtrl* txtUsername;
		wxStaticBox* StaticBox2;
		wxTextCtrl* txtPassword;
		//*)

	protected:

		//(*Identifiers(wxLogin)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(wxLogin)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OntxtPasswordText(wxCommandEvent& event);
		void OntxtPasswordTextEnter(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void ExecuteLogin();

    public:
        bool LoginSuccessful;
};

#endif
