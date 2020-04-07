#include <wxPanelVariableType.h>

#include <opcglobal.h>
#include <opcutils.h>
#include <wxPanelType.h>
#include <synthesis/opc.hxx>
#include <wxTreeDialog.h>

#include <vector>

using namespace std;
//(*InternalHeaders(wxPanelVariableType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelVariableType)
const long wxPanelVariableType::ID_STATICTEXT3 = wxNewId();
const long wxPanelVariableType::ID_TEXTCTRL2 = wxNewId();
const long wxPanelVariableType::ID_STATICTEXT1 = wxNewId();
const long wxPanelVariableType::ID_COMBOBOX1 = wxNewId();
const long wxPanelVariableType::ID_BUTTON1 = wxNewId();
const long wxPanelVariableType::ID_STATICTEXT2 = wxNewId();
const long wxPanelVariableType::ID_COMBOBOX2 = wxNewId();
const long wxPanelVariableType::ID_PANEL1 = wxNewId();
const long wxPanelVariableType::ID_CUSTOM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelVariableType,wxPanel)
	//(*EventTable(wxPanelVariableType)
	//*)
END_EVENT_TABLE()

wxPanelVariableType::wxPanelVariableType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelVariableType)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(-50,-1), wxSIMPLE_BORDER|wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer1->AddGrowableCol(0);
	GridBagSizer1->AddGrowableRow(0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	GridBagSizer2->AddGrowableCol(0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Array Dimensions"), wxDefaultPosition, wxSize(172,13), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	StaticText3->SetMaxSize(wxSize(150,-1));
	BoxSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtArrayDimension = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(236,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer1->Add(txtArrayDimension, 1, wxALL|wxEXPAND, 5);
	GridBagSizer2->Add(BoxSizer1, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Data Type"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText1->SetMaxSize(wxSize(150,-1));
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	cboDataType = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	BoxSizer5->Add(cboDataType, 1, wxALL, 5);
	btnDataTypeLookup = new wxButton(Panel1, ID_BUTTON1, _("..."), wxDefaultPosition, wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnDataTypeLookup->SetMaxSize(wxSize(32,23));
	BoxSizer5->Add(btnDataTypeLookup, 1, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer5, 1, wxEXPAND, 5);
	GridBagSizer2->Add(BoxSizer2, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Value Rank"), wxDefaultPosition, wxSize(180,13), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	StaticText2->SetMaxSize(wxSize(150,-1));
	BoxSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cboValueRank = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	BoxSizer3->Add(cboValueRank, 1, wxALL|wxEXPAND, 5);
	GridBagSizer2->Add(BoxSizer3, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND, 5);
	Panel1->SetSizer(GridBagSizer2);
	GridBagSizer2->Fit(Panel1);
	GridBagSizer2->SetSizeHints(Panel1);
	GridBagSizer1->Add(Panel1, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	panelType = new wxPanelType(this,ID_CUSTOM1);
	BoxSizer4->Add(panelType, 1, wxEXPAND, 5);
	GridBagSizer1->Add(BoxSizer4, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	SetSizer(GridBagSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPanelVariableType::OnbtnDataTypeLookupClick);
	//*)

    wxArrayString cboList;
    cboList.Add("String");
    cboList.Add("Boolean");
    cboList.Add("Double");
    cboList.Add("UInt32");
    cboList.Add("Byte");
	this->cboDataType->Set(cboList);

    wxArrayString cboValueRankList;
    cboValueRankList.Add("Scalar");
    cboValueRankList.Add("Array");
    cboValueRankList.Add("ScalarOrArray");
    cboValueRankList.Add("OneOrMoreDimensions");
	this->cboValueRank->Set(cboValueRankList);
}

wxPanelVariableType::~wxPanelVariableType()
{
	//(*Destroy(wxPanelVariableType)
	//*)
}

bool wxPanelVariableType::UpdateData()
{
    bool retVal = false;

    string baseType = OPCUtils::GetName<VariableTypeDesign::BaseType_optional>(m_variableType->BaseType());

    if ( (   baseType == "BaseVariableType"
          || baseType == "BaseDataVariableType"
          || baseType == "PropertyType")
         && m_userOwner)
    {
        //if (!OPCUtils::IsStringValidQName(this->cboDataType, this->cboDataType->GetValue().ToStdString(), "Data Type"))
        //    return false;

        if (this->cboDataType->GetValue().ToStdString() != "")
        {
            //Find the actual element so we can get the prefix
            bool userOwner = true; //By default we make it a user owner just in case we could not find it.
            xml_schema::ncname nc(this->cboDataType->GetValue().ToStdString());
            ITERATE_MODELLIST(DataType, i, m_model)
            {
                string dataTypeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
                if (this->cboDataType->GetValue().ToStdString() == dataTypeSymName)
                {
                    userOwner = OPCUtils::IsUserNodeOwner(&(*i));
                    break;
                }
            }
            xml_schema::qname qn((userOwner ? "" : "http://opcfoundation.org/UA/"), nc);
            VariableTypeDesign::DataType_optional dataType(qn);
            this->m_variableType->DataType(dataType);
        }

        string valueRank = this->cboValueRank->GetValue().ToStdString();
        if (valueRank.compare("") != 0)
            this->m_variableType->ValueRank(valueRank);

        string arrayDimension = this->txtArrayDimension->GetValue().ToStdString();
        if (arrayDimension.compare("") != 0)
            this->m_variableType->ArrayDimensions(arrayDimension);
    }

    retVal = this->panelType->UpdateData("VariableType");

    return retVal;
}

void wxPanelVariableType::PopulateData()
{
    string baseType = OPCUtils::GetName<VariableTypeDesign::BaseType_optional>(m_variableType->BaseType());

    VariableTypeDesign *varTypeToDisplay = 0;
     if ( (  baseType == "BaseVariableType"
           || baseType == "BaseDataVariableType"
           || baseType == "PropertyType")
          && m_userOwner)
    {
       varTypeToDisplay = this->m_variableType;
    }
    else if (m_parentVarType != 0)
    {
        varTypeToDisplay = m_parentVarType;
    }

    //These is only applicable to these 3 fields that can possibly be inherited.
    //Other fields in the future may directly display using m_variableType.
    if (varTypeToDisplay != 0)
    {
        wxString dataType = OPCUtils::GetName<VariableTypeDesign::DataType_optional>(varTypeToDisplay->DataType());
        if (dataType.compare(NO_VALUE) !=0)
            this->cboDataType->SetValue(dataType);

        wxString valueRank  = OPCUtils::GetString(varTypeToDisplay->ValueRank());
        if (valueRank.compare(NO_VALUE) !=0)
            this->cboValueRank->SetValue(valueRank);

        wxString arrayDimension  = OPCUtils::GetString(varTypeToDisplay->ArrayDimensions());
        if (arrayDimension.compare(NO_VALUE) !=0)
            this->txtArrayDimension->SetValue(arrayDimension);
    }

    this->panelType->PopulateData(NodeTypeVariableType);
}

void wxPanelVariableType::Init(VariableTypeDesign* variableType, ModelDesign *model, wxTreeItemId treeItemId,
                               wxFrameMain *mainFrame, bool userOwner, VariableTypeDesign *parentVarType)
{
    this->m_variableType  = variableType;
    this->m_model         = model;
    this->m_treeItemId    = treeItemId;
    this->m_mainFrame     = mainFrame;
    this->m_parentVarType = parentVarType;
    this->m_userOwner     = userOwner;

    this->panelType->Init(variableType, model, treeItemId, mainFrame, userOwner);

    this->cboDataType->SetValue(""); //TODO: set the value
    this->cboValueRank->SetValue("");
    this->txtArrayDimension->SetValue("");

    //      Subtypes should always inherit the data type from
    //      their parent and don't need to populate the value for this attribute.
    //      Unless they are direct sub types of BaseDataType and BaseDataVariableType, they are the only elements
    //      allowed to change its DataType related fields.
    string baseType = OPCUtils::GetName<VariableTypeDesign::BaseType_optional>(variableType->BaseType());

    bool enable = (   baseType == "BaseVariableType"
                    || baseType == "BaseDataVariableType"
                    || baseType == "PropertyType")
                  && userOwner;

    this->btnDataTypeLookup->Enable(enable);
    this->txtArrayDimension->Enable(enable);
    this->cboValueRank->Enable(enable);
    this->cboDataType->Enable(enable);
}

void wxPanelVariableType::OnbtnDataTypeLookupClick(wxCommandEvent& event)
{
    wxTreeDialog treeDlg(this, this->m_model, false, false, RootMaskShowDataType);
    treeDlg.ShowModal();

    if (treeDlg.GetReturnCode() == 0)
        this->cboDataType->SetValue(treeDlg.SelectedSymbolicName);
}
