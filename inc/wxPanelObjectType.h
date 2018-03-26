#ifndef WXPANELOBJECTTYPE_H
#define WXPANELOBJECTTYPE_H

//(*Headers(wxPanelObjectType)
#include <wx/sizer.h>
#include <wx/panel.h>
//*)

#include <map>
#include <wx/treebase.h>

class wxPanelType;
class ObjectTypeDesign;
class ModelDesign;
class wxFrameMain;

class wxPanelObjectType: public wxPanel
{
	public:

		wxPanelObjectType(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~wxPanelObjectType();

		//(*Declarations(wxPanelObjectType)
		wxPanelType* panelType;
		//*)

	protected:

		//(*Identifiers(wxPanelObjectType)
		static const long ID_CUSTOM1;
		//*)

	private:

		//(*Handlers(wxPanelObjectType)
		//*)

		DECLARE_EVENT_TABLE()

    public:
        bool UpdateData();
        void PopulateData();

        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        void Init(ObjectTypeDesign *objectType, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner);

    private:
        ObjectTypeDesign* m_objectType;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
};

#endif
