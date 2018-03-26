#ifndef wxPanelDataType_H
#define wxPanelDataType_H

//(*Headers(wxPanelDataType)
#include <wx/sizer.h>
#include <wx/panel.h>
//*)

#include <synthesis/opc.hxx>

#include <map>
#include <wx/treebase.h>


class wxPanelType;
class wxListView;
class wxFrameMain;

class wxPanelDataType: public wxPanel
{
	public:

		wxPanelDataType(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelDataType();

		//(*Declarations(wxPanelDataType)
		wxPanelType* panelType;
		//*)

	protected:

		//(*Identifiers(wxPanelDataType)
		static const long ID_PANEL_TYPE;
		//*)

	private:

		//(*Handlers(wxPanelDataType)
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void SetChildrenFieldItemNodeValues(const Parameter *field, int nodeId, bool disabled);
        void PopulateChildrenFieldsListCtrl(DataTypeDesign::Fields_optional *inheritedChildren, int &nodeId, bool disabled);
            
    public:
        bool UpdateData();
        void PopulateData();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(DataTypeDesign *dataType, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                  std::map<std::string, std::string> *stringIdMap);
        
        void PopulateChildrenFields();                  

    private:
        DataTypeDesign* m_dataType;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        wxListView *m_fieldListView;
};

#endif
