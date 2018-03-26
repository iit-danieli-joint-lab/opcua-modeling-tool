#include "wxPanelStructDataType.h"

#include <opcutils.h>
#include <opcglobal.h>
#include <wxPanelType.h>
#include <wxPanelNode.h>
#include <wxFieldDialog.h>
#include <synthesis/opc.hxx>

#include <wx/wx.h>

//(*InternalHeaders(wxPanelStructDataType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelStructDataType)
const long wxPanelStructDataType::ID_PANEL_TYPE = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelStructDataType,wxPanel)
	//(*EventTable(wxPanelStructDataType)
	//*)
END_EVENT_TABLE()

using namespace std;

wxPanelStructDataType::wxPanelStructDataType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelStructDataType)
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
    Connect(this->m_fieldListView->GetId(), wxEVT_COMMAND_RIGHT_CLICK, (wxObjectEventFunction)&wxPanelStructDataType::OnListFieldRightClick);
}

wxPanelStructDataType::~wxPanelStructDataType()
{
	//(*Destroy(wxPanelStructDataType)
	//*)
}


bool wxPanelStructDataType::UpdateData()
{
    bool retVal = false;

    retVal = this->panelType->UpdateData("StructDataType");
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

void wxPanelStructDataType::PopulateData()
{
    //TODO: Populate own fields here

    //TODO: Handle Enum Differently

    this->PopulateChildrenFields();

    this->panelType->PopulateData(NodeTypeStructDataType);
}

void wxPanelStructDataType::Init(DataTypeDesign* m_dataType, ModelDesign *model, wxTreeItemId treeItemId,
                                 wxFrameMain *mainFrame, bool userOwner)
{
    this->m_fieldListView->ClearAll();

    //Enum Using ListView
    wxListItem col0;
    col0.SetWidth(150);
    col0.SetId(0);
    col0.SetText( _("Name") );
    this->m_fieldListView->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetWidth(150);
    col1.SetText( _("DataType") );
    this->m_fieldListView->InsertColumn(1, col1);

    wxListItem col2;
    col2.SetWidth(200);
    col2.SetText( _("Description") );
    this->m_fieldListView->InsertColumn(2, col2);

    wxListItem col3;
    col3.SetWidth(100);
    col3.SetText( _("ValueRank") );
    this->m_fieldListView->InsertColumn(3, col3);

    wxListItem col4;
    col4.SetWidth(100);
    col4.SetText( _("ArrayDimension") );
    this->m_fieldListView->InsertColumn(4, col4);

    this->m_dataType        = m_dataType;
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

void wxPanelStructDataType::PopulateChildrenFields()
{
    this->m_fieldListView->DeleteAllItems();
    PopulateChildrenFieldsListCtrl();
}

void wxPanelStructDataType::PopulateChildrenFieldsListCtrl()
{
    int nodeId = 0;

    //Display Own fields
    if (this->m_tempDataType->Fields() != 0)
    {
        for (ListOfFields::Field_iterator i(this->m_tempDataType->Fields()->Field().begin());
             i != this->m_tempDataType->Fields()->Field().end();
             ++i)
        {
            SetChildrenFieldItemNodeValues(&(*i), nodeId, false);
            ++nodeId;
        }
    }

    //Search parent typedef'd from so we can recursively get all inherited fields.
    ListOfFields fieldsList;
    DataTypeDesign::Fields_optional inheritedFields(fieldsList);

    wxString baseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(this->m_tempDataType->BaseType());
    for (ModelDesign::DataType_iterator i (this->m_model->DataType().begin());
         i != this->m_model->DataType().end();
         ++i)
    {
        wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //Find what the DataType has typedef'd from.
        if (0 == symName.compare(baseType))
        {
            this->CopyParent(&(*i), &inheritedFields);
            break;
        }
    }

    //Display Inherited fields
    for (ListOfFields::Field_iterator i(inheritedFields->Field().begin());
         i != inheritedFields->Field().end();
         ++i)
    {
        SetChildrenFieldItemNodeValues(&(*i), nodeId, true);
        ++nodeId;
    }
}

void wxPanelStructDataType::CopyParent(DataTypeDesign *dataType, DataTypeDesign::Fields_optional *inheritedFields)
{
    //TODO: Add a logic to check for cyclic BaseType where a parent inherits a Child.
    //      Store baseType in a map, if key is there already then we terminate recursion and show message

    //Fields
    if (dataType->Fields() != 0)
    {
        for (ListOfFields::Field_iterator i(dataType->Fields()->Field().begin());
             i != dataType->Fields()->Field().end();
             ++i)
        {
            (*inheritedFields)->Field().push_back(*i);
        }
    }

    //Get the BaseType and search the actual object
    wxString baseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(dataType->BaseType(), "Structure");

    //Recursion will stop at the BaseObjectType
    if (baseType.Cmp("Structure") == 0)
        return;


    DataTypeDesign *parentType = 0;

    //Search from DataType
    for (ModelDesign::DataType_iterator i (this->m_model->DataType().begin());
         i != this->m_model->DataType().end();
         ++i)
    {
        wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //Find the ObjectType that the Object has typedef'd from.
        if (0 == symName.compare(baseType))
        {
            parentType = &(*i);
            break;
        }
    }

    if (parentType != 0)
        this->CopyParent(parentType, inheritedFields);
}
void wxPanelStructDataType::SetChildrenFieldItemNodeValues(Parameter *field, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    item.SetData(field);

    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    item.SetText(OPCUtils::GetString(field->Name()));                                           //column 0

    m_fieldListView->InsertItem(item);
    m_fieldListView->SetItem(nodeId, 1, OPCUtils::GetName<Parameter::DataType_optional>(field->DataType()));

    wxString desc = OPCUtils::GetString(field->Description());
    if (desc.compare(NO_VALUE) !=0)
        m_fieldListView->SetItem(nodeId, 2, OPCUtils::GetString(field->Description()));

    wxString valueRank  = OPCUtils::GetString(field->ValueRank());
    if (valueRank.compare(NO_VALUE) !=0)
        m_fieldListView->SetItem(nodeId, 3, valueRank);

    wxString arrayDimension = OPCUtils::GetString(field->ArrayDimensions());
    if (arrayDimension.compare(NO_VALUE) !=0)
        m_fieldListView->SetItem(nodeId, 4, arrayDimension);

}

void wxPanelStructDataType::OnListFieldRightClick(wxCommandEvent& event)
{
    if (!m_userOwner)
        return;

    wxMenu treeItemMenu;
    treeItemMenu.SetClientData(this->m_fieldListView);
    treeItemMenu.Append(MenuPopup_ID_ADD, "Add");


    bool enable = m_fieldListView->GetFirstSelected() >= 0;
    if (enable)
    {
        //Do not allow deletion for inherited fields.
        wxColour bgColor = m_fieldListView->GetItemBackgroundColour(m_fieldListView->GetFirstSelected());
        treeItemMenu.Append(MenuPopup_ID_EDIT, "Edit")->Enable((*wxLIGHT_GREY != bgColor));
        treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((*wxLIGHT_GREY != bgColor));
    }

    //N.B:No need to move up/dwon because this is a struct, and their is inherited fields also.
    //treeItemMenu.Append(MenuPopup_ID_MOVE_UP, "Move Up")->Enable(enable);
    //treeItemMenu.Append(MenuPopup_ID_MOVE_DOWN, "Move Down")->Enable(enable);

    treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxPanelStructDataType::OnPopupList), NULL, this);
    PopupMenu(&treeItemMenu);
}

void wxPanelStructDataType::OnPopupList(wxCommandEvent &evt)
{
	switch(evt.GetId()) {
 		case MenuPopup_ID_ADD:
            {
                wxFieldDialog dialog(this->m_model, this, "Struct Field");
                dialog.ShowModal();
                if(dialog.GetReturnCode() == 0)
                {
                    Parameter param = dialog.GetParameter();
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

                    wxFieldDialog dialog(this->m_model, this, "Struct Field", param);
                    dialog.ShowModal();
                }
                break;
 		    }
 		case MenuPopup_ID_DEL:
 		    {
 		        DeleteParameter();
                break;
 		    }
        default:
            cerr << "This is a bug. Popup menu selection not implemented.\n";
 	}

 	PopulateChildrenFields(); //Repopulate
}

void wxPanelStructDataType::DeleteParameter()
{
    long selectedItemIndex = m_fieldListView->GetFirstSelected();
    if (selectedItemIndex >= 0)
    {
        wxUIntPtr dataUIntPtr   = m_fieldListView->GetItemData(selectedItemIndex);
        void *data              = wxUIntToPtr(dataUIntPtr);
        Parameter *param        = reinterpret_cast<Parameter *>(data);


        /*
        Find here seems not to work correctly. We need proper comparator.
        ListOfArguments::Argument_iterator i =std::find(this->m_tempMethod->OutputArguments()->Argument().begin(),
                                                        this->m_tempMethod->OutputArguments()->Argument().end(),
                                                        param);
        this->m_tempMethod->OutputArguments()->Argument().erase(i);
        */
        //Fields
        for (ListOfFields::Field_iterator i(this->m_tempDataType->Fields()->Field().begin());
             i != this->m_tempDataType->Fields()->Field().end();
             )
        {
            if (&(*i) == param)
                this->m_tempDataType->Fields()->Field().erase(i);
            else
                ++i; //Increment only when it's not found, since calling erase will move to the next item automatically.
        }

        //m_fieldListView->DeleteItem(selectedItemIndex);
    }
}
