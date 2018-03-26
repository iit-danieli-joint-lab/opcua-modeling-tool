#ifndef WXCOMPILEDIALOG_H
#define WXCOMPILEDIALOG_H

#include <synthesis/opc.hxx>

#include <map>

//(*Headers(wxParameterDialog)
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

class wxCompileDialog: public wxDialog
{
	public:

		wxCompileDialog(std::string projectFile, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxCompileDialog();

		//(*Declarations(wxCompileDialog)
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxCheckBox* chkForceOverwrite;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxStaticBox* StaticBox2;
		wxComboBox* cboOutputType;
		wxTextCtrl* txtIdentifiersOutput;
		wxTextCtrl* txtOutputDir;
		wxButton* btnLookup;
		//*)

	protected:

		//(*Identifiers(wxCompileDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_BUTTON3;
		static const long ID_CHECKBOX1;
		//*)

	private:

		//(*Handlers(wxCompileDialog)
		void OnButton2Click(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OncboDataTypeSelected(wxCommandEvent& event);
		void OnbtnLookupClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        std::string m_projectFile;

};

#endif
