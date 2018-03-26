#ifndef WXPANELTYPE_H
#define WXPANELTYPE_H

//(*Headers(wxPanelType)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
//*)

#include "opcglobal.h"
#include "synthesis/opc.hxx"

#include <wx/treebase.h>

class wxPanelNode;
class wxFrameMain;


class wxPanelType: public wxPanel
{
	public:

		wxPanelType(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelType();

		//(*Declarations(wxPanelType)
		wxPanel* panelType;
		wxStaticText* StaticText2;
		wxCheckBox* chkAbstract;
		wxStaticText* StaticText3;
		wxCheckBox* chkNoClassGen;
		wxPanelNode* panelNode;
		//*)

	protected:

		//(*Identifiers(wxPanelType)
		static const long ID_STATICTEXT3;
		static const long ID_CHECKBOX2;
		static const long ID_STATICTEXT2;
		static const long ID_CHECKBOX1;
		static const long ID_PANEL1;
		static const long ID_CUSTOM1;
		//*)

	private:

		//(*Handlers(wxPanelType)
		void OncboBaseTypeSelected(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void CopyParent(TypeDesign *type, NodeDesign::Children_optional *inheritedChildren, NodeDesign::References_optional *inheritedReferences);

    public:
        bool UpdateData(const char *nodePrefix);
        void PopulateData(const enum NodeType nodeType);

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(TypeDesign *type, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                  bool userOwner, bool hideEnum=true, bool hideChildren=false);

    private:
        TypeDesign* m_type;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
};
#endif
