#ifndef WXTREEDIALOG_H
#define WXTREEDIALOG_H

//(*Headers(wxTreeDialog)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "opcglobal.h"

#include <map>

class ModelDesign;
class NodeDesign;

class wxTreeDialog: public wxDialog
{
	public:

		wxTreeDialog(wxWindow* parent, ModelDesign* model,
                     bool showChildrenAndReferences, bool showReferences,
                     int showRootMask = (  RootMaskShowDataType
                                         | RootMaskShowEventType
                                         | RootMaskShowObjectType
                                         | RootMaskShowReferenceType
                                         | RootMaskShowVariableType
                                         | RootMaskShowMethod
                                         | RootMaskShowObject),
                     wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxTreeDialog();

		//(*Declarations(wxTreeDialog)
		wxButton* btnCancel;
		wxTreeCtrl* treeOPCCtrl;
		wxButton* btnOK;
		//*)

	protected:

		//(*Identifiers(wxTreeDialog)
		static const long ID_TREECTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(wxTreeDialog)
		void OnButton2Click(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OntreeOPCCtrlBeginDrag(wxTreeEvent& event);
		void OntreeOPCCtrlItemActivated(wxTreeEvent& event);
		void OntreeOPCCtrlSelectionChanged(wxTreeEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    public:
        NodeDesign* GetSelectedNode();
        std::string GetTargetId(wxTreeItemId node, std::string targetId);

    public:
        std::string SelectedStringId;
        std::string SelectedSymbolicName;
        std::string SelectedNamespace;

    private:
        ModelDesign* m_model;
        NodeDesign* m_selectedNode;
};

#endif
