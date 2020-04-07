#include <wxPanelVariable.h>
#include <wxPanelInstance.h>
#include <synthesis/opc.hxx>
#include <opcutils.h>
#include <wxTreeDialog.h>

#include <vector>

//(*InternalHeaders(wxPanelVariable)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelVariable)
const long wxPanelVariable::ID_CUSTOM1 = wxNewId();
const long wxPanelVariable::ID_lblDataType = wxNewId();
const long wxPanelVariable::ID_COMBOBOX1 = wxNewId();
const long wxPanelVariable::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelVariable,wxPanel)
	//(*EventTable(wxPanelVariable)
	//*)
END_EVENT_TABLE()

using namespace std;

wxPanelVariable::wxPanelVariable(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelVariable)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* boxSizerDataType;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	panelInstance = new wxPanelInstance(this,ID_CUSTOM1);
	BoxSizer2->Add(panelInstance, 1, wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND, 5);
	boxSizerDataType = new wxBoxSizer(wxHORIZONTAL);
	lblDataType = new wxStaticText(this, ID_lblDataType, _("DataType"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_lblDataType"));
	lblDataType->SetMinSize(wxSize(150,-1));
	lblDataType->SetMaxSize(wxSize(150,-1));
	boxSizerDataType->Add(lblDataType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cboDataType = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	boxSizerDataType->Add(cboDataType, 1, wxALL|wxEXPAND, 5);
	bntLookupDataType = new wxButton(this, ID_BUTTON1, _("..."), wxDefaultPosition, wxSize(32,21), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	bntLookupDataType->SetMinSize(wxSize(32,21));
	bntLookupDataType->SetMaxSize(wxSize(32,-1));
	boxSizerDataType->Add(bntLookupDataType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(boxSizerDataType, 0, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPanelVariable::OnbntLookupDataTypeClick);
	//*)

    this->m_boxSizerDataType = boxSizerDataType;
    wxArrayString cboList;
    cboList.Add("String");
    cboList.Add("Boolean");
    cboList.Add("Double");
    cboList.Add("UInt32");
    cboList.Add("Byte");
    //cboList.push_back("...");
	this->cboDataType->Set(cboList);


}

wxPanelVariable::~wxPanelVariable()
{
	//(*Destroy(wxPanelVariable)
	//*)
}


bool wxPanelVariable::UpdateData(const char *nodePrefix)
{
    //if (retVal)
        //TODO: Update fields here

    if (this->m_nodeType == NodeTypeChildProperty)
    {
        //Save Datatype, ignore/remove typedef
        this->panelInstance->txtTypeDefinition->SetValue("");

        if (!OPCUtils::IsStringValidQName(this->cboDataType, this->cboDataType->GetValue().ToStdString(), "Data Type"))
            return false;

        //Find the actual element so we can get the prefix
        bool userOwner = true; //By default we make it a user owner just in case we could not find it.
        xml_schema::ncname nc(this->cboDataType->GetValue().ToStdString());
        ITERATE_MODELLIST(DataType, i, m_model)
        {
            string dataTypeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
            cout << this->cboDataType->GetValue().ToStdString() << " == " << dataTypeSymName ;
            if (this->cboDataType->GetValue().ToStdString() == dataTypeSymName)
            {
                userOwner = OPCUtils::IsUserNodeOwner(&(*i));
                break;
            }
        }
        xml_schema::qname qn((userOwner ? "" : "http://opcfoundation.org/UA/"), nc);
        PropertyDesign::DataType_optional dataType(qn);
        this->m_var->DataType(dataType);
    }
    else
    {
        //Ignore/Remove Datatype, save typedef
        this->cboDataType->SetValue("");
    }

    //Call instance update after own fields, since depending on the node type some values will be cleared.
    return this->panelInstance->UpdateData(nodePrefix);
}

void wxPanelVariable::Init(VariableDesign* var, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                            bool userOwner, const enum NodeType nodeType)
{
    this->m_var             = var;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;
    this->m_nodeType        = nodeType;

    this->panelInstance->Init(var, model, treeItemId, mainFrame, userOwner, nodeType);

    this->cboDataType->Enable(userOwner);
    this->bntLookupDataType->Enable(userOwner);

    if (nodeType == NodeTypeChildProperty)
    {
        ShowDataType(true);
        this->panelInstance->ShowTypeDefinition(false);
    }
    else
    {
        ShowDataType(false);
        this->panelInstance->ShowTypeDefinition(true);
    }

}

void wxPanelVariable::PopulateData()
{
    //TODO: Populate fields here
    if (this->m_nodeType == NodeTypeChildProperty)
    {
        wxString dataType = OPCUtils::GetName<VariableTypeDesign::DataType_optional>(this->m_var->DataType(), string(""));

        if (dataType.compare(NO_VALUE) !=0)
            this->cboDataType->SetValue(dataType);
        else
            this->cboDataType->SetValue("");
    }

    this->panelInstance->PopulateData(this->m_nodeType);
}

void wxPanelVariable::OnbntLookupDataTypeClick(wxCommandEvent& event)
{
    int mask = 0;

    if (this->m_nodeType == NodeTypeChildProperty)
        mask = RootMaskShowDataType;
    else //NodeTypeVariable
        mask = RootMaskShowVariableType;

    wxTreeDialog treeDlg(this, this->m_model, false, false, mask);
    treeDlg.ShowModal();

    if (treeDlg.GetReturnCode() == 0)
        this->cboDataType->SetValue(treeDlg.SelectedSymbolicName);
}

void wxPanelVariable::ShowDataType(bool show)
{
    if (show)
    {
        this->m_boxSizerDataType->Show(this->lblDataType, true);
        this->m_boxSizerDataType->Show(this->cboDataType, true);
        this->m_boxSizerDataType->Show(this->bntLookupDataType, true);
    }
    else
    {
        this->m_boxSizerDataType->Hide(this->lblDataType, true);
        this->m_boxSizerDataType->Hide(this->cboDataType, true);
        this->m_boxSizerDataType->Hide(this->bntLookupDataType, true);
    }
}

