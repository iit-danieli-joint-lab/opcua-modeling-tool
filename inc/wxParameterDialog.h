#ifndef WXPARAMETERDIALOG_H
#define WXPARAMETERDIALOG_H

#include "synthesis/opc.hxx"

#include <map>

//(*Headers(wxParameterDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

class wxParameterDialog: public wxDialog
{
	public:

		wxParameterDialog(ModelDesign *model, wxWindow* parent, Parameter* paramEdit = 0,
                          wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxParameterDialog();

		//(*Declarations(wxParameterDialog)
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxStaticBox* StaticBox2;
		wxComboBox* cboDataType;
		wxTextCtrl* txtName;
		wxButton* btnLookup;
		wxTextCtrl* txtDescription;
		//*)

	protected:

		//(*Identifiers(wxParameterDialog)
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
		//*)

	private:

		//(*Handlers(wxParameterDialog)
		void OnButton2Click(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OncboDataTypeSelected(wxCommandEvent& event);
		void OnbtnLookupClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    public:
        Parameter GetParameter();

    private:
        ModelDesign* m_model;
        Parameter m_paramNew;
        Parameter *m_param;
};

#endif
