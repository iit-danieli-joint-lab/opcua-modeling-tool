#ifndef WXPANELINSTANCE_H
#define WXPANELINSTANCE_H

//(*Headers(wxPanelInstance)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)
#include "opcglobal.h"
#include "synthesis/opc.hxx"

#include <wx/treebase.h>

class wxPanelNode;
class InstanceDesign;
class ModelDesign;
class TypeDesign;
class wxFrameMain;

class wxPanelInstance: public wxPanel
{
	public:

		wxPanelInstance(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelInstance();

		//(*Declarations(wxPanelInstance)
		wxTextCtrl* txtTypeDefinition;
		wxStaticText* lblTypeDefinition;
		wxStaticText* StaticText3;
		wxComboBox* cboModeling;
		wxButton* btnLookup;
		wxPanelNode* panelNode;
		//*)

	protected:

		//(*Identifiers(wxPanelInstance)
		static const long ID_CUSTOM1;
		static const long ID_lblTypeDefinition;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT3;
		static const long ID_cboModeling;
		//*)

	private:

		//(*Handlers(wxPanelInstance)
		void OnbtnLookupClick(wxCommandEvent& event);
		void OntxtTypeDefinitionText(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
         void Clear();

         //This will copy recursively the Children and References upward of the hierarchy
         //of the BaseType up to the BaseObjectType.
         void CopyParent(TypeDesign *type, NodeDesign::Children_optional *inheritedChildren, NodeDesign::References_optional *inheritedReferences);

    public:
        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(InstanceDesign *node, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                  bool userOwner, enum NodeType m_nodeType,
                  bool hideEnum=true, bool hideChildren=false, bool hideRefereces=false, bool hideInstance=false);
        void PopulateData(const enum NodeType nodeType);
        bool UpdateData(const char *nodePrefix);

        //Allowing this to be exposed since some of the opc instances
        //such as Property does not use this, thus allowing it to
        //control its visibility. opc ua design quirk.
        void ShowTypeDefinition(bool show);

    private:
        InstanceDesign *m_instance;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        enum NodeType m_nodeType;

        wxSizer *m_mainSizer;
        wxSizer *m_nodeSizer;
        wxSizer *m_instanceSizer;
        wxSizer *m_instanceInternalSizer;
        wxSizer *m_boxSizerTypeDefinition;

        NodeDesign *m_typeDefNodeSelected;
};

#endif
