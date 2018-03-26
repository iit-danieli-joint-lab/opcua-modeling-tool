#ifndef wxPanelStructDataType_H
#define wxPanelStructDataType_H

//(*Headers(wxPanelStructDataType)
#include <wx/sizer.h>
#include <wx/panel.h>
//*)

#include "synthesis/opc.hxx"

#include <map>
#include <wx/treebase.h>


class wxPanelType;
class wxListView;
class wxFrameMain;

class wxPanelStructDataType: public wxPanel
{
	public:

		wxPanelStructDataType(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelStructDataType();

		//(*Declarations(wxPanelStructDataType)
		wxPanelType* panelType;
		//*)

	protected:

		//(*Identifiers(wxPanelStructDataType)
		static const long ID_PANEL_TYPE;
		//*)

	private:

		//(*Handlers(wxPanelStructDataType)
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void DeleteParameter();
        void SetChildrenFieldItemNodeValues(Parameter *field, int nodeId, bool disabled);
        void PopulateChildrenFieldsListCtrl();
        void CopyParent(DataTypeDesign *type, DataTypeDesign::Fields_optional *inheritedFields);
        void OnPopupList(wxCommandEvent &evt);

        //Custom Event Handlers
        void OnListFieldRightClick(wxCommandEvent& event);


    public:
        bool UpdateData();
        void PopulateData();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(DataTypeDesign *dataType, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner);

        void PopulateChildrenFields();

    private:
        DataTypeDesign* m_dataType;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        wxListView *m_fieldListView;
        bool m_userOwner;

        //This will store temporarily the input/output parameters to allow the user to manually Update the changes.
        std::auto_ptr<DataTypeDesign> m_tempDataType;
};

#endif
