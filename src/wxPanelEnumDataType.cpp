#include "wxPanelEnumDataType.h"

#include <opcutils.h>
#include <opcglobal.h>
#include <wxPanelType.h>
#include <wxPanelNode.h>
#include <wxEnumDialog.h>
#include <synthesis/opc.hxx>

#include <wx/wx.h>

//(*InternalHeaders(wxPanelEnumDataType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelEnumDataType)
const long wxPanelEnumDataType::ID_PANEL_TYPE = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelEnumDataType,wxPanel)
	//(*EventTable(wxPanelEnumDataType)
	//*)
END_EVENT_TABLE()

using namespace std;

wxPanelEnumDataType::wxPanelEnumDataType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelEnumDataType)
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
    Connect(this->m_fieldListView->GetId(), wxEVT_COMMAND_RIGHT_CLICK, (wxObjectEventFunction)&wxPanelEnumDataType::OnListFieldRightClick);
}

wxPanelEnumDataType::~wxPanelEnumDataType()
{
	//(*Destroy(wxPanelEnumDataType)
	//*)
}


bool wxPanelEnumDataType::UpdateData()
{
    bool retVal = false;

    retVal = this->panelType->UpdateData("EnumDataType");
    if (retVal)
    {
        //Replace the actual data type with the temporary one.
        this->m_dataType->Fields()->Field().erase(this->m_dataType->Fields()->Field().begin(),
                                                  this->m_dataType->Fields()->Field().end());

        //Copy all values from temp to the actual data type.
        for (ListOfFields::Field_iterator i(this->m_tempDataType->Fields()->Field().begin());
             i != this->m_tempDataType->Fields()->Field().end();
             ++i)
        {
             this->m_dataType->Fields()->Field().push_back(*i);
        }
    }

    return retVal;
}

void wxPanelEnumDataType::PopulateData()
{
    //TODO: Populate own fields here

    //TODO: Handle Enum Differently

    this->PopulateChildrenFields();

    this->panelType->PopulateData(NodeTypeEnumDataType);
}

void wxPanelEnumDataType::Init(DataTypeDesign* dataType, ModelDesign *model, wxTreeItemId treeItemId,
                               wxFrameMain *mainFrame, bool userOwner)
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
    col1.SetText( _("Value") );
    this->m_fieldListView->InsertColumn(1, col1);

    // Add 3rd
    wxListItem col2;
    col2.SetWidth(300);
    col2.SetText( _("Description") );
    this->m_fieldListView->InsertColumn(2, col2);


    this->m_dataType        = dataType;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;
    this->m_userOwner       = userOwner;

    //Make sure Fields sequence is set
    if (this->m_dataType->Fields() == 0)
    {
        ListOfFields fields;
        this->m_dataType->Fields(fields);
    }

    this->panelType->Init(m_dataType, model, treeItemId, mainFrame, userOwner, false, true);

    auto_ptr<DataTypeDesign> tempDataType(new DataTypeDesign(*m_dataType));
    this->m_tempDataType = tempDataType;
}

void wxPanelEnumDataType::PopulateChildrenFields()
{
    this->m_fieldListView->DeleteAllItems();

    int nodeId = 0;

    //Add own children to the list control
    //DataTypeDesign *dataTypeNode = static_cast<DataTypeDesign*>(*m_tempDataType);
    PopulateChildrenFieldsListCtrl(&m_tempDataType->Fields(), nodeId, false);
}

void wxPanelEnumDataType::PopulateChildrenFieldsListCtrl(DataTypeDesign::Fields_optional *children, int &nodeId, bool disabled)
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

void wxPanelEnumDataType::SetChildrenFieldItemNodeValues(Parameter *field, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    item.SetData(field);

    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    item.SetText(OPCUtils::GetString(field->Name()));                                           //column 0
    m_fieldListView->InsertItem(item);

    //Identifier is the enum value 0,1,2
    m_fieldListView->SetItem(nodeId, 1, OPCUtils::GetString(field->Identifier()));               //column 1

    m_fieldListView->SetItem(nodeId, 2, OPCUtils::GetString(field->Description()));               //column 1
}

void wxPanelEnumDataType::OnListFieldRightClick(wxCommandEvent& event)
{
    if (!m_userOwner)
        return;

    wxMenu treeItemMenu;
    treeItemMenu.SetClientData(this->m_fieldListView);
    treeItemMenu.Append(MenuPopup_ID_ADD, "Add");

    bool enable = m_fieldListView->GetFirstSelected() >= 0;
    treeItemMenu.Append(MenuPopup_ID_EDIT, "Edit")->Enable(enable);
    treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable(enable);
    treeItemMenu.Append(MenuPopup_ID_MOVE_UP, "Move Up")->Enable(enable);
    treeItemMenu.Append(MenuPopup_ID_MOVE_DOWN, "Move Down")->Enable(enable);

    treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxPanelEnumDataType::OnPopupList), NULL, this);
    PopupMenu(&treeItemMenu);
}

void wxPanelEnumDataType::GetLastValueIncrement(int &lastValue, int &increment)
{
    lastValue = -1;
    increment = 1;

    if (m_fieldListView->GetItemCount() == 1)
    {
        ListOfFields::Field_iterator pLast = this->m_tempDataType->Fields()->Field().end()-1;
        lastValue = atoi(OPCUtils::GetString(pLast->Identifier()).c_str());
    }
    else if (m_fieldListView->GetItemCount() > 1)
    {
        ListOfFields::Field_iterator pLast      = this->m_tempDataType->Fields()->Field().end()-1;
        ListOfFields::Field_iterator p2ndToLast = this->m_tempDataType->Fields()->Field().end()-2;
        int numLast      = atoi(OPCUtils::GetString(pLast->Identifier()).c_str());
        int num2ndToLast = atoi(OPCUtils::GetString(p2ndToLast->Identifier()).c_str());
        lastValue        = numLast;
        increment        = (numLast - num2ndToLast);
    }
}

void wxPanelEnumDataType::OnPopupList(wxCommandEvent &evt)
{
	switch(evt.GetId()) {
 		case MenuPopup_ID_ADD:
            {
                int lastValue;
                int increment;
                GetLastValueIncrement(lastValue, increment);
                wxEnumDialog dialog(this->m_model, this, lastValue+increment, increment);
                dialog.ShowModal();
                if(dialog.GetReturnCode() == 0)
                {
                    Parameter param = dialog.GetParameter();
                    SetChildrenFieldItemNodeValues(&param, this->m_fieldListView->GetItemCount(), false); //Insert to the last
                    this->m_tempDataType->Fields()->Field().push_back(param);
                }
                break;
            }
 		case MenuPopup_ID_EDIT:
 		    {
                long selectedItemIndex = m_fieldListView->GetFirstSelected();
                if (selectedItemIndex >= 0)
                {
                    wxUIntPtr dataUIntPtr = m_fieldListView->GetItemData(selectedItemIndex);
                    void *data            = wxUIntToPtr(dataUIntPtr);
                    Parameter *param      = reinterpret_cast<Parameter *>(data);

                    wxEnumDialog dialog(this->m_model, this, 0, 1, param);
                    dialog.ShowModal();
                }
                break;
 		    }
 		case MenuPopup_ID_DEL:
 		    {
 		        DeleteParameter();
                break;
 		    }
 		case MenuPopup_ID_MOVE_UP:
 		    {
 		        MoveParameter(true);
 		        break;
 		    }
        case MenuPopup_ID_MOVE_DOWN:
            {
 		        MoveParameter(false);
                break;
            }
        default:
            cerr << "This is a bug. Popup menu selection not implemented.\n";
 	}

 	PopulateChildrenFields();
}

void wxPanelEnumDataType::DeleteParameter()
{
    long selectedItemIndex = m_fieldListView->GetFirstSelected();
    if (selectedItemIndex >= 0)
    {
        wxUIntPtr dataUIntPtr   = m_fieldListView->GetItemData(selectedItemIndex);
        void *data              = wxUIntToPtr(dataUIntPtr);
        Parameter *param        = reinterpret_cast<Parameter *>(data);

        //Fields
        for (ListOfFields::Field_iterator i(this->m_tempDataType->Fields()->Field().begin());
             i != this->m_tempDataType->Fields()->Field().end();
             )
        {
            if (&(*i) == param)
            {
                this->m_tempDataType->Fields()->Field().erase(i);
                break;
            }
            else
                ++i; //Increment only when it's not found, since calling erase will move to the next item automatically.
        }

        //m_fieldListView->DeleteItem(selectedItemIndex);
    }
}

void wxPanelEnumDataType::MoveParameter(bool moveUp)
{
    long selectedItemIndex = m_fieldListView->GetFirstSelected();

    //Only move not the first or last item depending on the direction to move.
    if (   (moveUp && (selectedItemIndex > 0) )
        || ( (!moveUp) && (selectedItemIndex < m_fieldListView->GetItemCount()-1) )
        )
    {
        wxUIntPtr dataUIntPtr   = m_fieldListView->GetItemData(selectedItemIndex);
        void *data              = wxUIntToPtr(dataUIntPtr);
        Parameter *param        = reinterpret_cast<Parameter *>(data);
        Parameter paramDup      = *param;

        //Fields
        for (ListOfFields::Field_iterator i(this->m_tempDataType->Fields()->Field().begin());
             i != this->m_tempDataType->Fields()->Field().end();
             )
        {
            if (&(*i) == param)
            {
                this->m_tempDataType->Fields()->Field().erase(i);

                if (moveUp)
                    --i;    //Move back before inserting
                else
                    ++i;    //Move forward before inserting

                this->m_tempDataType->Fields()->Field().insert(i, paramDup);

                break;
            }
            else
                ++i; //Increment only when it's not found, since calling erase will move to the next item automatically.
        }
    }
}
