#ifndef WXPANELREFERENCETYPE_H
#define WXPANELREFERENCETYPE_H

//(*Headers(wxPanelReferenceType)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
//*)

#include <map>
#include <wx/treebase.h>

class ModelDesign;
class ReferenceTypeDesign;
class wxFrameMain;
class wxPanelType;

class wxPanelReferenceType: public wxPanel
{
	public:

		wxPanelReferenceType(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelReferenceType();

		//(*Declarations(wxPanelReferenceType)
		wxCheckBox* chkSymmetric;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxTextCtrl* txtInverseName;
		wxPanelType* panelType;
		//*)

	protected:

		//(*Identifiers(wxPanelReferenceType)
		static const long ID_CUSTOM1;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX1;
		static const long ID_StaticText1;
		static const long ID_txtInverseName;
		//*)

	private:

		//(*Handlers(wxPanelReferenceType)
		//*)

		DECLARE_EVENT_TABLE()

    public:
        bool UpdateData();
        void PopulateData();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(ReferenceTypeDesign *refType, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner);

    private:
        ReferenceTypeDesign* m_refType;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
};

#endif
