#ifndef wxEnumDialog_H
#define wxEnumDialog_H


#include "synthesis/opc.hxx"

#include <wx/validate.h>
#include <wx/textentry.h>
#include <wx/valnum.h>




//(*Headers(wxEnumDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/spinbutt.h>
//*)

class wxEnumDialog: public wxDialog
{
	public:

		wxEnumDialog(ModelDesign* model, wxWindow* parent, int value, int increment, Parameter* paramEdit = 0,
                     wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxEnumDialog();

		//(*Declarations(wxEnumDialog)
		wxSpinButton* btnValue;
		wxStaticText* StaticText2;
		wxButton* btnCancel;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxButton* btnOK;
		wxStaticBox* StaticBox2;
		wxTextCtrl* txtName;
		wxTextCtrl* txtValue;
		wxTextCtrl* txtDescription;
		//*)

	protected:

		//(*Identifiers(wxEnumDialog)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_SPINBUTTON1;
		//*)

	private:

		//(*Handlers(wxEnumDialog)
		void OnButton2Click(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OncboDataTypeSelected(wxCommandEvent& event);
		void OnbtnLookupClick(wxCommandEvent& event);
		void OnSpinButton1Change(wxSpinEvent& event);
		void OnbtnValueChangeUp(wxSpinEvent& event);
		void OnbtnValueChangeDown(wxSpinEvent& event);
		void OnbtnValueChange(wxSpinEvent& event);
		void OnbtnValueChange1(wxSpinEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    public:
        Parameter GetParameter();

    private:
        ModelDesign* m_model;
        int m_value;
        int m_increment;
        Parameter *m_param;
        Parameter m_paramNew;
        wxIntegerValidator<unsigned long> m_vldNum;
};

#endif
