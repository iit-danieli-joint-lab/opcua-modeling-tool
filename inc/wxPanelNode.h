#ifndef WXPANELNode_H
#define WXPANELNode_H

//(*Headers(wxPanelNode)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
//*)

#include "synthesis/opc.hxx"

#include <wx/treebase.h>

class wxFrameMain;

class wxPanelNode: public wxPanel
{
	public:

		wxPanelNode(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelNode();

		//(*Declarations(wxPanelNode)
		wxPanel* panelField;
		wxListView* referenceListViewCtrl;
		wxListView* childrenListViewCtrl;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxListView* fieldListViewCtrl;
		wxPanel* panelReference;
		wxTextCtrl* txtSymbolicName;
		wxStaticText* StaticText4;
		wxPanel* panelChildren;
		//*)

	protected:

		//(*Identifiers(wxPanelNode)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_LISTVIEW1;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT4;
		static const long ID_LISTVIEW3;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT3;
		static const long ID_LISTVIEW2;
		static const long ID_PANEL3;
		//*)

	private:

		//(*Handlers(wxPanelNode)
		void OnListView1BeginDrag(wxListEvent& event);
		void OnfieldListViewCtrlBeginDrag(wxListEvent& event);
		void OnfieldListViewCtrlBeginDrag1(wxListEvent& event);
		void OnchildrenListViewCtrlBeginDrag(wxListEvent& event);
		void OnreferenceListViewCtrlBeginDrag(wxListEvent& event);
		void OnchildrenListViewCtrlBeginDrag1(wxListEvent& event);
		void OnreferenceListViewCtrlBeginDrag1(wxListEvent& event);
		void OnPaint(wxPaintEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:

        void SetChildrenItemNodeValues(const NodeDesign *node, int nodeId, bool disabled);
        void SetReferenceItemNodeValues(const Reference *ref, int nodeId, bool disabled);

        void PopulateChildrenListCtrl(NodeDesign::Children_optional *inheritedChildren, int &nodeId, bool disabled);
        void PopulateReferencesListCtrl(NodeDesign::References_optional *inheritedReferences, int &nodeId, bool disabled);

    public:
        void Clear();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(NodeDesign *node, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                  bool usreOwner, bool Hidefield=true, bool hideChildren=false, bool hideRefereces=false);

        bool UpdateData(const char *nodePrefix);

        void PopulateData();
        void PopulateChildren(NodeDesign::Children_optional *inheritedChildren);
        void PopulateReferences(NodeDesign::References_optional *inheritedReferences);

        void DeleteChildren();
        void DeleteReferences();

        //This will copy children and references from the source node to the parameters.
        void CopyParent(NodeDesign *sourceNode, NodeDesign::Children_optional *inheritedChildren, NodeDesign::References_optional *inheritedReferences);

        void HideField(bool hide);
        void HideChildren(bool hide);
        void HideReferences(bool hide);
        void Refresh();

        //The field List control has been placed in this base Node panel even though it is specific only to fieldDataType.
        //OPC design of Node elements is not a strict object oriented implementation, as it has several quirks to it.
        //One of which is that the field Data Type does not use the Children, instead has a special list for Fields.
        //In order to accomodate this special behavior without creating a new Panel from scratch for fieldDataType,
        //we declare the field List View in this base Node panel and just allow it to be hidden/shown.
        //By exposing the UI control here, we will allow the field Data Type panel to access this and have its custom implementation from its own panel.
        wxListView *GetFieldListView();

    private:
        NodeDesign* m_node;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;

        wxBoxSizer* m_mainSizer;
        wxBoxSizer* m_boxSizerChildren;
        wxBoxSizer* m_boxSizerReferences;
        wxBoxSizer* m_boxSizerField;
};
#endif
