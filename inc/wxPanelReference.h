#ifndef WXPANELREFERENCE_H
#define WXPANELREFERENCE_H

//(*Headers(wxPanelReference)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
//*)

#include "synthesis/opc.hxx"

#include <map>
#include <wx/treebase.h>

class wxFrameMain;

class wxPanelReference: public wxPanel
{
	public:

		wxPanelReference(wxWindow* parent, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelReference();

		//(*Declarations(wxPanelReference)
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* btnLookupRefType;
		wxTextCtrl* txtReferenceType;
		wxCheckBox* chkInverse;
		wxTextCtrl* txtTargetId;
		wxCheckBox* chkOneWay;
		wxButton* btnShowTree;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(wxPanelReference)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT4;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT3;
		static const long ID_CHECKBOX2;
		//*)

	private:

		//(*Handlers(wxPanelReference)
		void OnbtnShowTreeClick(wxCommandEvent& event);
		void OnbtnShowTreeClick1(wxCommandEvent& event);
		void OnbtnShowTreeClick2(wxCommandEvent& event);
		void OnbtnLookupRefTypeClick(wxCommandEvent& event);
		void OnbtnLookupRefTypeClick1(wxCommandEvent& event);
		void OncboReferenceTypeSelected(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void Clear();

    public:
        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(Reference *reference, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner);
        void PopulateData();
        bool UpdateData();

    private:
        Reference *m_reference;
        std::string m_refTargetRefTypeNS;
        std::string m_refTargetIdNS;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
};

#endif
