#ifndef WXPROJECTDIALOG_H
#define WXPROJECTDIALOG_H

//(*Headers(wxProjectDialog)
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class ModelDesign;
class wxProjectDialog: public wxDialog
{
	public:

		wxProjectDialog(ModelDesign* model,wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxProjectDialog();

		//(*Declarations(wxProjectDialog)
		wxButton* btnCancel;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxTextCtrl* txtFullURI;
		wxStaticBox* StaticBox2;
		wxStaticBox* StaticBox3;
		wxTextCtrl* txtName;
		wxTextCtrl* txtFilename;
		wxStaticText* StaticText4;
		wxListView* lstNamespaces;
		wxStaticBox* StaticBox4;
		//*)

	protected:

		//(*Identifiers(wxProjectDialog)
		static const long ID_STATICBOX1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICBOX3;
		static const long ID_STATICBOX4;
		static const long ID_LISTVIEW1;
		//*)

	private:

		//(*Handlers(wxProjectDialog)
		void OnInit(wxInitDialogEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnCancelClick1(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

	public:
        void SetEditable(bool editable);
        void LoadOtherNamespaces();

    private:
        ModelDesign* m_model;
};

#endif
