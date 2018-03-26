#ifndef wxFieldDialog_H
#define wxFieldDialog_H

#include <synthesis/opc.hxx>

#include <map>

//(*Headers(wxFieldDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)


class wxFieldDialog: public wxDialog
{
	public:

		wxFieldDialog(ModelDesign *model, wxWindow* parent, std::string title,
                      Parameter* paramEdit = 0, wxWindowID id=wxID_ANY,
                      const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxFieldDialog();

		//(*Declarations(wxFieldDialog)
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxStaticBox* StaticBox2;
		wxStaticText* StaticText5;
		wxComboBox* cboDataType;
		wxTextCtrl* txtArraySize;
		wxTextCtrl* txtName;
		wxButton* btnLookup;
		wxStaticText* StaticText4;
		wxTextCtrl* txtDescription;
		wxComboBox* cboValueRank;
		//*)

	protected:

		//(*Identifiers(wxFieldDialog)
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
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL2;
		static const long ID_COMBOBOX2;
		//*)

	private:

		//(*Handlers(wxFieldDialog)
		void OnButton2Click(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OncboDataTypeSelected(wxCommandEvent& event);
		void OnbtnLookupClick(wxCommandEvent& event);
		void OntxtNameText(wxCommandEvent& event);
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
