#include <wxPanelMethod.h>
#include <wxPanelInstance.h>
#include <wxFrameMain.h>
#include <opcglobal.h>
#include <opcutils.h>
#include <wxFieldDialog.h>

#include <wx/menu.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <sstream>

//(*InternalHeaders(wxPanelMethod)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelMethod)
const long wxPanelMethod::ID_STATICTEXT1 = wxNewId();
const long wxPanelMethod::ID_TEXTCTRL1 = wxNewId();
const long wxPanelMethod::ID_STATICTEXT4 = wxNewId();
const long wxPanelMethod::ID_CHECKBOX1 = wxNewId();
const long wxPanelMethod::ID_STATICTEXT2 = wxNewId();
const long wxPanelMethod::ID_LISTVIEW_INPUT = wxNewId();
const long wxPanelMethod::ID_STATICTEXT3 = wxNewId();
const long wxPanelMethod::ID_LISTVIEW_OUTPUT = wxNewId();
const long wxPanelMethod::ID_STATICTEXT5 = wxNewId();
const long wxPanelMethod::ID_COMBOBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelMethod,wxPanel)
	//(*EventTable(wxPanelMethod)
	//*)
END_EVENT_TABLE()

using namespace std;

wxPanelMethod::wxPanelMethod(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelMethod)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer10;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* methodSizer;
	wxBoxSizer* BoxSizer2;
	wxGridBagSizer* mainSizer;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMinSize(wxSize(150,-1));
	mainSizer = new wxGridBagSizer(0, 0);
	mainSizer->AddGrowableCol(0);
	mainSizer->AddGrowableRow(0);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Symbolic Name"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText1->SetMinSize(wxSize(150,-1));
	StaticText1->SetMaxSize(wxSize(150,-1));
	BoxSizer2->Add(StaticText1, 1, wxALL, 5);
	txtSymbolicName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(txtSymbolicName, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxEXPAND, 5);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Non-Executable"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT4"));
	StaticText4->SetMinSize(wxSize(150,-1));
	StaticText4->SetMaxSize(wxSize(150,-1));
	BoxSizer9->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkNonExecutable = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkNonExecutable->SetValue(false);
	BoxSizer9->Add(chkNonExecutable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer9, 0, wxEXPAND, 5);
	methodSizer = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _(" INPUT Parameters"), wxDefaultPosition, wxSize(405,183), wxALIGN_LEFT|wxRAISED_BORDER, _T("ID_STATICTEXT2"));
	StaticText2->SetMinSize(wxSize(-1,21));
	StaticText2->SetMaxSize(wxSize(-1,21));
	BoxSizer5->Add(StaticText2, 1, wxEXPAND, 5);
	BoxSizer3->Add(BoxSizer5, 0, wxEXPAND, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	listInput = new wxListView(this, ID_LISTVIEW_INPUT, wxDefaultPosition, wxSize(405,190), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW_INPUT"));
	BoxSizer8->Add(listInput, 1, wxEXPAND, 5);
	BoxSizer3->Add(BoxSizer8, 1, wxEXPAND, 5);
	methodSizer->Add(BoxSizer3, 1, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _(" OUTPUT Parameters"), wxDefaultPosition, wxSize(-1,21), wxALIGN_LEFT|wxRAISED_BORDER, _T("ID_STATICTEXT3"));
	StaticText3->SetMinSize(wxSize(-1,21));
	StaticText3->SetMaxSize(wxSize(-1,21));
	BoxSizer6->Add(StaticText3, 1, wxLEFT|wxEXPAND, 5);
	BoxSizer4->Add(BoxSizer6, 0, wxEXPAND, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	listOutput = new wxListView(this, ID_LISTVIEW_OUTPUT, wxDefaultPosition, wxSize(405,225), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW_OUTPUT"));
	BoxSizer7->Add(listOutput, 1, wxLEFT|wxEXPAND, 5);
	BoxSizer4->Add(BoxSizer7, 1, wxEXPAND, 5);
	methodSizer->Add(BoxSizer4, 1, wxEXPAND, 5);
	BoxSizer1->Add(methodSizer, 0, wxEXPAND, 5);
	BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Type Definition"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT5"));
	StaticText5->SetMinSize(wxSize(150,-1));
	StaticText5->SetMaxSize(wxSize(150,-1));
	BoxSizer10->Add(StaticText5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cboTypeDefinition = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY|wxCB_DROPDOWN, wxDefaultValidator, _T("ID_COMBOBOX1"));
	BoxSizer10->Add(cboTypeDefinition, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer10, 0, wxALL|wxEXPAND, 5);
	mainSizer->Add(BoxSizer1, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);
	//*)

	Connect(ID_LISTVIEW_INPUT, wxEVT_COMMAND_RIGHT_CLICK, (wxObjectEventFunction)&wxPanelMethod::OnlistInputItemRClick);
    Connect(ID_LISTVIEW_OUTPUT, wxEVT_COMMAND_RIGHT_CLICK, (wxObjectEventFunction)&wxPanelMethod::OnlistOutputItemRClick);

    wxListItem colIn0;
    colIn0.SetWidth(150);
    colIn0.SetId(0);
    colIn0.SetText( _("Name") );
    this->listInput->InsertColumn(0, colIn0);

    wxListItem colIn1;
    colIn1.SetWidth(150);
    colIn1.SetText( _("Type") );
    this->listInput->InsertColumn(1, colIn1);

    wxListItem colIn2;
    colIn2.SetWidth(200);
    colIn2.SetText( _("Description") );
    this->listInput->InsertColumn(2, colIn2);

    wxListItem colIn3;
    colIn3.SetWidth(100);
    colIn3.SetText( _("ValueRank") );
    this->listInput->InsertColumn(3, colIn3);

    wxListItem colIn4;
    colIn4.SetWidth(100);
    colIn4.SetText( _("ArrayDimension") );
    this->listInput->InsertColumn(4, colIn4);

    wxListItem colOut0;
    colOut0.SetWidth(150);
    colOut0.SetId(0);
    colOut0.SetText( _("Name") );
    this->listOutput->InsertColumn(0, colOut0);

    wxListItem colOut1;
    colOut1.SetWidth(150);
    colOut1.SetText( _("Type") );
    this->listOutput->InsertColumn(1, colOut1);

    wxListItem colOut2;
    colOut2.SetWidth(200);
    colOut2.SetText( _("Description") );
    this->listOutput->InsertColumn(2, colOut2);

    wxListItem colOut3;
    colOut3.SetWidth(100);
    colOut3.SetText( _("ValueRank") );
    this->listOutput->InsertColumn(3, colOut3);

    wxListItem colOut4;
    colOut4.SetWidth(100);
    colOut4.SetText( _("ArrayDimension") );
    this->listOutput->InsertColumn(4, colOut4);
}

wxPanelMethod::~wxPanelMethod()
{
	//(*Destroy(wxPanelMethod)
	//*)
}

void wxPanelMethod::Init(MethodDesign *method, ModelDesign *model, wxTreeItemId treeItemId,
                         wxFrameMain *mainFrame, bool userOwner, bool showTypeDef)
{
    this->m_method          = method;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;
    this->m_showTypeDef     = showTypeDef;
    this->m_userOwner       = userOwner;

    this->cboTypeDefinition->Enable(showTypeDef & userOwner);
    this->chkNonExecutable->Enable(userOwner);
    this->txtSymbolicName->Enable(userOwner);
    this->cboTypeDefinition->Clear();

    if (showTypeDef)
    {
        this->cboTypeDefinition->Append("");
        int currentValueIndex = 0;
        string currentTypeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(this->m_method->TypeDefinition(), "");
        ITERATE_MODELLIST(Method, i, m_model)
        {
            string typeDef = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
            this->cboTypeDefinition->Append(typeDef, &(*i));
            if (currentTypeDef == typeDef)
                currentValueIndex = this->cboTypeDefinition->GetCount() - 1;
        }
        this->cboTypeDefinition->SetSelection(currentValueIndex);
        //If we sort the drop down box(wxCB_SORT), we can't use the index in determing the current type definition.
        //Index is only usable after all the values are added to the list.
    }

    if (this->m_method->InputArguments() == 0)
    {
        ListOfArguments args;
        this->m_method->InputArguments(args);
    }

    if (this->m_method->OutputArguments() == 0)
    {
        ListOfArguments args;
        this->m_method->OutputArguments(args);
    }

    auto_ptr<MethodDesign> tempMethod(new MethodDesign(*method));
    this->m_tempMethod = tempMethod;
    this->Clear();
}

void wxPanelMethod::PopulateData()
{
    this->txtSymbolicName->SetValue(OPCUtils::GetName(this->m_tempMethod->SymbolicName()));

    //I don't know why this doesn't work unlike the rest of the code with the same type (:xml_schema::boolean).
    //The only difference I could see, for e.g. comparing with Reference::IsOneWay, is that it has a false default value.
    //this->chkNonExecutable->SetValue(this->m_method->NonExecutable());
    stringstream sstrm;
    sstrm << this->m_method->NonExecutable();
    this->chkNonExecutable->SetValue((sstrm.str() == "1"));

    PopulateInputArgs();
    PopulateOutputArgs();
}

void wxPanelMethod::Clear()
{
    this->txtSymbolicName->SetValue("");
}

void wxPanelMethod::PopulateInputArgs()
{
    long nodeId = 0;
    this->listInput->DeleteAllItems();
    for (ListOfArguments::Argument_iterator i(this->m_tempMethod->InputArguments()->Argument().begin());
         i != this->m_tempMethod->InputArguments()->Argument().end();
         ++i)
    {
        SetListItemParameter(&(*i),this->listInput, nodeId, false);
        ++nodeId;
    }
    //Show inherited input arguments.
    //Method hierarchical level is only one, so there's no need to recursively find the parent.
    string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(this->m_tempMethod->TypeDefinition(), "");

    ITERATE_MODELLIST(Method, i, m_model)
    {
        wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //Find what the method has typedef'd from.
        if (0 == symName.compare(typeDef))
        {
            if (i->InputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator inherited(i->InputArguments()->Argument().begin());
                     inherited != i->InputArguments()->Argument().end();
                     ++inherited)
                {
                    SetListItemParameter(&(*inherited),this->listInput, nodeId, true);
                    ++nodeId;
                }
            }
            break;
        }
    }
}

void wxPanelMethod::PopulateOutputArgs()
{
    long nodeId = 0;
    this->listOutput->DeleteAllItems();
    for (ListOfArguments::Argument_iterator i(this->m_tempMethod->OutputArguments()->Argument().begin());
         i != this->m_tempMethod->OutputArguments()->Argument().end();
         ++i)
    {
        SetListItemParameter(&(*i),this->listOutput, nodeId, false);
        ++nodeId;
    }
    //Show inherited output arguments.
    //Method hierarchical level is only one, so there's no need to recursively find the parent.
    string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(this->m_tempMethod->TypeDefinition(), "");

    ITERATE_MODELLIST(Method, i, m_model)
    {
        wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //Find what the method has typedef'd from.
        if (0 == symName.compare(typeDef))
        {
            if (i->OutputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator inherited(i->OutputArguments()->Argument().begin());
                     inherited != i->OutputArguments()->Argument().end();
                     ++inherited)
                {
                    SetListItemParameter(&(*inherited),this->listOutput, nodeId, true);
                    ++nodeId;
                }
            }
            break;
        }
    }
}

void wxPanelMethod::OnlistInputItemRClick(wxCommandEvent& event)
{
    if (!m_userOwner)
        return;

    wxMenu treeItemMenu;
    treeItemMenu.SetClientData(this->listInput); //TODO: Replace this with true/false to flag whether it is input/output.
    treeItemMenu.Append(MenuPopup_ID_ADD, "Add");

    bool enable = this->listInput->GetFirstSelected() >= 0;
    if (enable)
    {
        //Do not allow deletion for inherited fields.
        wxColour bgColor = this->listInput->GetItemBackgroundColour(this->listInput->GetFirstSelected());
        treeItemMenu.Append(MenuPopup_ID_EDIT, "Edit")->Enable((*wxLIGHT_GREY != bgColor));
        treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((*wxLIGHT_GREY != bgColor));
    }

    treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxPanelMethod::OnPopupList), NULL, this);
    PopupMenu(&treeItemMenu);
}

void wxPanelMethod::OnlistOutputItemRClick(wxCommandEvent& event)
{
    if (!m_userOwner)
        return;

    wxMenu treeItemMenu;
    treeItemMenu.SetClientData(this->listOutput);
    treeItemMenu.Append(MenuPopup_ID_ADD, "Add");

    bool enable = this->listOutput->GetFirstSelected() >= 0;
    if (enable)
    {
        //Do not allow deletion for inherited fields.
        wxColour bgColor = this->listOutput->GetItemBackgroundColour(this->listOutput->GetFirstSelected());
        treeItemMenu.Append(MenuPopup_ID_EDIT, "Edit")->Enable((*wxLIGHT_GREY != bgColor));
        treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((*wxLIGHT_GREY != bgColor));
    }

    treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxPanelMethod::OnPopupList), NULL, this);
    PopupMenu(&treeItemMenu);
}

void wxPanelMethod::OnPopupList(wxCommandEvent &evt)
{
    void *data = static_cast<wxMenu *>(evt.GetEventObject())->GetClientData();
    wxListView *listView = reinterpret_cast<wxListView*>(data);

    bool isInput = (listView == this->listInput); //If ClientData is this->listOutput then this will be false;
    string title = isInput ? "Input Parameter" : "Output Parameter";
	switch(evt.GetId()) {
 		case MenuPopup_ID_ADD:
            {
                wxFieldDialog dialog(this->m_model, this, title);
                dialog.ShowModal();
                if(dialog.GetReturnCode() == 0)
                {
                    Parameter param = dialog.GetParameter();
                    AddParameter(param, isInput);
                }
                break;
            }
        case MenuPopup_ID_EDIT:
            {
                long selectedItemIndex = listView->GetFirstSelected();
                if (selectedItemIndex >= 0)
                {
                    wxUIntPtr dataUIntPtr = listView->GetItemData(selectedItemIndex);
                    void *data            = wxUIntToPtr(dataUIntPtr);
                    Parameter *param      = reinterpret_cast<Parameter *>(data);

                    wxFieldDialog dialog(this->m_model, this, title, param);
                    dialog.ShowModal();
                }
                break;
            }
 		case MenuPopup_ID_DEL:
 		    {
 		        DeleteParameter(isInput);
                break;
 		    }
        default:
            cerr << "This is a bug. Popup menu selection not implemented.\n";
 	}

    //Repopulate
    PopulateInputArgs();
    PopulateOutputArgs();
}

void wxPanelMethod::AddParameter(Parameter &param, bool isInput)
{
    if (isInput)
    {
        //SetListItemParameter(&param, this->listInput, this->listInput->GetItemCount()); //Insert to the last
        this->m_tempMethod->InputArguments()->Argument().push_back(param);
        PopulateInputArgs();
    }
    else
    {
        //SetListItemParameter(&param, this->listOutput, this->listOutput->GetItemCount()); //Insert to the last
        this->m_tempMethod->OutputArguments()->Argument().push_back(param);
        PopulateOutputArgs();
    }
}

void wxPanelMethod::DeleteParameter(bool isInput)
{
    wxListView *listView   = isInput ? this->listInput : this->listOutput;
    long selectedItemIndex = listView->GetFirstSelected();
    if (selectedItemIndex >= 0)
    {
        wxUIntPtr dataUIntPtr = listView->GetItemData(selectedItemIndex);
        void *data = wxUIntToPtr(dataUIntPtr);
        Parameter *param = reinterpret_cast<Parameter *>(data);

        if (isInput)
        {
            /*
            Find here seems not to work correctly. We need proper comparator.
            ListOfArguments::Argument_iterator i = std::find(this->m_tempMethod->InputArguments()->Argument().begin(),
                                                             this->m_tempMethod->InputArguments()->Argument().end(),
                                                             param);
            this->m_tempMethod->InputArguments()->Argument().erase(i);
            */
            for (ListOfArguments::Argument_iterator i(this->m_tempMethod->InputArguments()->Argument().begin());
                 i != this->m_tempMethod->InputArguments()->Argument().end();
                 )
            {
                if (&(*i) == param)
                    this->m_tempMethod->InputArguments()->Argument().erase(i);
                else
                    ++i; //Increment only when it's not found, since calling erase will move to the next item automatically.
            }
        }
        else
        {
            /*
            Find here seems not to work correctly. We need proper comparator.
            ListOfArguments::Argument_iterator i =std::find(this->m_tempMethod->OutputArguments()->Argument().begin(),
                                                            this->m_tempMethod->OutputArguments()->Argument().end(),
                                                            param);
            this->m_tempMethod->OutputArguments()->Argument().erase(i);
            */
            for (ListOfArguments::Argument_iterator i(this->m_tempMethod->OutputArguments()->Argument().begin());
                 i != this->m_tempMethod->OutputArguments()->Argument().end();
                 )
            {
                if (&(*i) == param)
                    this->m_tempMethod->OutputArguments()->Argument().erase(i);
                else
                    ++i; //Increment only when it's not found, since calling erase will move to the next item automatically.
            }
        }
        //listView->DeleteItem(selectedItemIndex);
    }
}

void wxPanelMethod::SetListItemParameter(Parameter *param, wxListView *listView, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    item.SetData(param);

    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    item.SetText(OPCUtils::GetString(param->Name()));

    listView->InsertItem(item);

    listView->SetItem(nodeId, 1, wxString(OPCUtils::GetName(param->DataType())));

    wxString desc = OPCUtils::GetString(param->Description());
    if (desc.compare(NO_VALUE) !=0)
        listView->SetItem(nodeId, 2, desc);

    wxString valueRank  = OPCUtils::GetString(param->ValueRank());
    if (valueRank.compare(NO_VALUE) !=0)
        listView->SetItem(nodeId, 3, valueRank);

    wxString arrayDimension = OPCUtils::GetString(param->ArrayDimensions());
    if (arrayDimension.compare(NO_VALUE) !=0)
        listView->SetItem(nodeId, 4, arrayDimension);
}

bool wxPanelMethod::UpdateData()
{
    //N.B:  Some of the common code from wxPanelNode has been duplicated because this is not
    //      a composite class containing wxPanelNode. It is not natural to subclass wxPanelNode
    //      if there are several functionalities missing and not applicable.

    string symName  = this->txtSymbolicName->GetValue().ToStdString();
    if (!OPCUtils::SetSymName(this->m_method, symName))
    {
        this->txtSymbolicName->SetFocus();
        return false;
    }

    //Replace the actual method input and output parameters with the temporary one.
    this->m_method->InputArguments()->Argument().erase(this->m_method->InputArguments()->Argument().begin(),
                                                       this->m_method->InputArguments()->Argument().end());
    this->m_method->OutputArguments()->Argument().erase(this->m_method->OutputArguments()->Argument().begin(),
                                                        this->m_method->OutputArguments()->Argument().end());

    //Copy all values from temp input/output to the acutal method object.
    for (ListOfArguments::Argument_iterator i(this->m_tempMethod->InputArguments()->Argument().begin());
         i != this->m_tempMethod->InputArguments()->Argument().end();
         ++i)
    {
         this->m_method->InputArguments()->Argument().push_back(*i);
    }

    for (ListOfArguments::Argument_iterator i(this->m_tempMethod->OutputArguments()->Argument().begin());
         i != this->m_tempMethod->OutputArguments()->Argument().end();
         ++i)
    {
         this->m_method->OutputArguments()->Argument().push_back(*i);
    }

    this->m_method->NonExecutable(this->chkNonExecutable->GetValue());

    //Set TypeDefinition - Applicable for Child Method only
    if (this->m_showTypeDef)
    {
        string currentTypeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(this->m_method->TypeDefinition(), "");
        cout << "currentTypeDef:" << currentTypeDef << " this->cboTypeDefinition->GetValue().ToStdString():" << this->cboTypeDefinition->GetValue().ToStdString() << "\n";
        if (currentTypeDef != this->cboTypeDefinition->GetValue().ToStdString())
        {
            void *pData = this->cboTypeDefinition->GetClientData(this->cboTypeDefinition->GetSelection());
            MethodDesign *methodTypeSelected = 0;
            if (pData != 0)
                methodTypeSelected = reinterpret_cast<MethodDesign*>(pData);
            OPCUtils::SetTypeDef(*this->m_method, this->cboTypeDefinition->GetValue().ToStdString(), OPCUtils::IsUserNodeOwner(methodTypeSelected));
        }
    }

    return true;
}
