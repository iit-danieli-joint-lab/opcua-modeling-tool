#ifndef WXABOUT_H
#define WXABOUT_H

#include <wx/hyperlink.h>

//(*Headers(wxAbout)
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class wxAbout: public wxDialog
{
	public:

		wxAbout(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxAbout();

		//(*Declarations(wxAbout)
		wxHyperlinkCtrl* txtBeeondLink;
		wxStaticText* StaticText2;
		wxStaticText* lblAppNameAndVersion;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* btnOK;
		//*)

	protected:

		//(*Identifiers(wxAbout)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		//*)

	private:

		//(*Handlers(wxAbout)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnOKClick1(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnInit1(wxInitDialogEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
