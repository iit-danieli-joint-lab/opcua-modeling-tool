#ifndef WXPANELVARIABLE_H
#define WXPANELVARIABLE_H

//(*Headers(wxPanelVariable)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "opcglobal.h"

#include <map>
#include <wx/treebase.h>

class wxPanelInstance;
class VariableDesign;
class ModelDesign;
class wxFrameMain;

class wxPanelVariable: public wxPanel
{
	public:

		wxPanelVariable(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelVariable();

		//(*Declarations(wxPanelVariable)
		wxButton* bntLookupDataType;
		wxComboBox* cboDataType;
		wxPanelInstance* panelInstance;
		wxStaticText* lblDataType;
		//*)

	protected:

		//(*Identifiers(wxPanelVariable)
		static const long ID_CUSTOM1;
		static const long ID_lblDataType;
		static const long ID_COMBOBOX1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(wxPanelVariable)
		void OnbntLookupDataTypeClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()


        //This is an opc quirk where datatype is a component of a Variable even though
        //it is used only by a Property subclass.
        //On the otherhand, Typedef is not used by Property.
        void ShowDataType(bool show);

    public:
        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(VariableDesign *var, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                  bool userOwner, const enum NodeType nodeType);

        void PopulateData();
        bool UpdateData(const char *nodePrefix);


    private:
        VariableDesign *m_var;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        enum NodeType m_nodeType;
        wxSizer *m_boxSizerDataType;
};

#endif
