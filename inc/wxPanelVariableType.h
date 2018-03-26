#ifndef WXPANELVARIABLETYPE_H
#define WXPANELVARIABLETYPE_H

//(*Headers(wxPanelVariableType)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include <map>
#include <wx/treebase.h>

class wxPanelType;
class VariableTypeDesign;
class ModelDesign;
class wxFrameMain;

class wxPanelVariableType: public wxPanel
{
	public:

		wxPanelVariableType(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelVariableType();

		//(*Declarations(wxPanelVariableType)
		wxTextCtrl* txtArrayDimension;
		wxButton* btnDataTypeLookup;
		wxStaticText* StaticText2;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxComboBox* cboDataType;
		wxPanelType* panelType;
		wxComboBox* cboValueRank;
		//*)

	protected:

		//(*Identifiers(wxPanelVariableType)
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_COMBOBOX2;
		static const long ID_PANEL1;
		static const long ID_CUSTOM1;
		//*)

	private:

		//(*Handlers(wxPanelVariableType)
		void OnbtnDataTypeLookupClick(wxCommandEvent& event);
		void OnbtnDataTypeLookupClick1(wxCommandEvent& event);
		void OnpanelTypePaint(wxPaintEvent& event);
		void OntxtArrayDimensionText(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    public:
        bool UpdateData();
        void PopulateData();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(VariableTypeDesign *varType, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner, VariableTypeDesign *parentVarType);

    private:
        VariableTypeDesign* m_variableType;
        ModelDesign* m_model;
        wxTreeItemId m_parentItemId;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        VariableTypeDesign* m_parentVarType;
        bool m_userOwner;
};

#endif
