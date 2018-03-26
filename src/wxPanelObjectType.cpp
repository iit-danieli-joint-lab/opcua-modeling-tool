#include <wxPanelObjectType.h>

#include <opcglobal.h>
#include <wxPanelType.h>
#include <wxPanelNode.h>
#include <synthesis/opc.hxx>

//(*InternalHeaders(wxPanelObjectType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelObjectType)
const long wxPanelObjectType::ID_CUSTOM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelObjectType,wxPanel)
	//(*EventTable(wxPanelObjectType)
	//*)
END_EVENT_TABLE()

wxPanelObjectType::wxPanelObjectType(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(wxPanelObjectType)
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(500,-1), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	panelType = new wxPanelType(this,ID_CUSTOM1);
	BoxSizer1->Add(panelType, 1, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	SetSizer(BoxSizer1);
	Layout();
	//*)
}

wxPanelObjectType::~wxPanelObjectType()
{
	//(*Destroy(wxPanelObjectType)
	//*)
}

bool wxPanelObjectType::UpdateData()
{
    bool retVal = false;

    retVal = this->panelType->UpdateData("ObjectType");
    //if (retVal)
        //TODO: Update fields here

    return retVal;
}

void wxPanelObjectType::PopulateData()
{
    //TODO: Populate own fields here

    this->panelType->PopulateData(NodeTypeObjectType);
}

void wxPanelObjectType::Init(ObjectTypeDesign* objectType, ModelDesign *model, wxTreeItemId treeItemId,
                             wxFrameMain *mainFrame, bool userOwner)
{
    this->m_objectType      = objectType;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;

    this->panelType->Init(objectType, model, treeItemId, mainFrame, userOwner);
}


