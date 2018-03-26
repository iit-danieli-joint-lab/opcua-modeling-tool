#ifndef WXCONFIG_H
#define WXCONFIG_H

//(*Headers(wxConfig)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class wxConfig: public wxDialog
{
	public:

		wxConfig(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxConfig();

		//(*Declarations(wxConfig)
		wxButton* btnSave;
		wxButton* btnClose;
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxTextCtrl* txtExecutable;
		wxButton* btnCompilerPath;
		//*)

	protected:

		//(*Identifiers(wxConfig)
		static const long ID_STATICBOX1;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON3;
		//*)

	private:

		//(*Handlers(wxConfig)
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnSaveClick(wxCommandEvent& event);
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnbtnCloseClick1(wxCommandEvent& event);
		void OnbtnCloseClick2(wxCommandEvent& event);
		void OnbtnSaveClick1(wxCommandEvent& event);
		void OnbtnCloseClick3(wxCommandEvent& event);
		void OnbtnCompilerPathClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
