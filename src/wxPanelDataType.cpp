#include "wxPanelDataType.h"

#include <opcutils.h>
#include <opcglobal.h>
#include <wxPanelType.h>
#include <wxPanelNode.h>
#include <synthesis/opc.hxx>

#include <wx/wx.h>

//(*InternalHeaders(wxPanelDataType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelDataType)
const long wxPanelDataType::ID_PANEL_TYPE = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelDataType,wxPanel)
	//(*EventTable(wxPanelDataType)
	//*)
END_EVENT_TABLE()

wxPanelDataType::wxPanelDataType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelDataType)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	panelType = new wxPanelType(this,ID_PANEL_TYPE);
	BoxSizer2->Add(panelType, 1, wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
    
    this->m_fieldListView = this->panelType->panelNode->GetFieldListView();
}

wxPanelDataType::~wxPanelDataType()
{
	//(*Destroy(wxPanelDataType)
	//*)
}


bool wxPanelDataType::UpdateData()
{
    bool retVal = false;

    retVal = this->panelType->UpdateData("DataType");
    //if (retVal)
        //TODO: Update fields here

    return retVal;
}

void wxPanelDataType::PopulateData()
{
    //TODO: Populate own fields here

    //TODO: Handle Enum Differently

    this->PopulateChildrenFields();
                
    this->panelType->PopulateData(NodeTypeDataType);
}

void wxPanelDataType::Init(DataTypeDesign* dataType, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                               std::map<std::string, std::string> *stringIdMap)
{
    this->m_fieldListView->ClearAll();
    
    //Enum Using ListView
    // Add 1st column
    wxListItem col0;
    col0.SetWidth(300);
    col0.SetId(0);
    col0.SetText( _("Name") );
    this->m_fieldListView->InsertColumn(0, col0);
    
    // Add 2nd column
    wxListItem col1;
    col1.SetWidth(200);
    col1.SetText( _("DataType") );
    this->m_fieldListView->InsertColumn(1, col1);

    // Add 3rd
    wxListItem col2;
    col2.SetWidth(300);
    col2.SetText( _("ValueRank") );
    this->m_fieldListView->InsertColumn(2, col2);
    
    
    this->m_dataType        = dataType;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;

    this->panelType->Init(dataType, model, treeItemId, mainFrame, stringIdMap, false, true);
}

void wxPanelDataType::PopulateChildrenFields()
{
    this->m_fieldListView->DeleteAllItems();

    int nodeId = 0;

    //Add own children to the list control
    DataTypeDesign *dataTypeNode = static_cast<DataTypeDesign*>(m_dataType);
    if(dataTypeNode->Fields() != 0)
        PopulateChildrenFieldsListCtrl(&dataTypeNode->Fields(), nodeId, false);
}

void wxPanelDataType::PopulateChildrenFieldsListCtrl(DataTypeDesign::Fields_optional *children, int &nodeId, bool disabled)
{
    //Fields
    for (ListOfFields::Field_iterator i((*children)->Field().begin());
         i != (*children)->Field().end();
         ++i)
    {
        SetChildrenFieldItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }
}

void wxPanelDataType::SetChildrenFieldItemNodeValues(const Parameter *field, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    item.SetText(OPCUtils::GetString(field->Name()));                                           //column 0
    //TODO: Other columns   
    m_fieldListView->InsertItem(item);
    
}