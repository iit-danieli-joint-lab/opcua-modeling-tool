#include <wxFieldDialog.h>
#include <wxTreeDialog.h>
#include <opcglobal.h>
#include <opcutils.h>

#include <vector>
#include <wx/msgdlg.h>
#include <wx/log.h>

//(*InternalHeaders(wxFieldDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(wxFieldDialog)
const long wxFieldDialog::ID_STATICBOX1 = wxNewId();
const long wxFieldDialog::ID_STATICTEXT1 = wxNewId();
const long wxFieldDialog::ID_TEXTCTRL1 = wxNewId();
const long wxFieldDialog::ID_STATICTEXT2 = wxNewId();
const long wxFieldDialog::ID_STATICBOX2 = wxNewId();
const long wxFieldDialog::ID_BUTTON1 = wxNewId();
const long wxFieldDialog::ID_BUTTON2 = wxNewId();
const long wxFieldDialog::ID_TEXTCTRL3 = wxNewId();
const long wxFieldDialog::ID_STATICTEXT3 = wxNewId();
const long wxFieldDialog::ID_COMBOBOX1 = wxNewId();
const long wxFieldDialog::ID_BUTTON3 = wxNewId();
const long wxFieldDialog::ID_STATICTEXT4 = wxNewId();
const long wxFieldDialog::ID_STATICTEXT5 = wxNewId();
const long wxFieldDialog::ID_TEXTCTRL2 = wxNewId();
const long wxFieldDialog::ID_COMBOBOX2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxFieldDialog,wxDialog)
	//(*EventTable(wxFieldDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxFieldDialog::wxFieldDialog(ModelDesign *model, wxWindow* parent, std::string title, Parameter* paramEdit,
                             wxWindowID id,const wxPoint& pos,const wxSize& size): m_model(model)
{
	//(*Initialize(wxFieldDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(401,242));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,8), wxSize(384,176), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name"), wxPoint(12,40), wxSize(90,21), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	txtName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(108,36), wxSize(274,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Description"), wxPoint(12,66), wxSize(90,21), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,184), wxSize(384,48), 0, _T("ID_STATICBOX2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(224,200), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(312,200), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	txtDescription = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(108,64), wxSize(274,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Data Type"), wxPoint(12,95), wxSize(90,21), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	cboDataType = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(108,92), wxSize(228,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	btnLookup = new wxButton(this, ID_BUTTON3, _("..."), wxPoint(348,92), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Value Rank"), wxPoint(12,123), wxSize(90,21), wxALIGN_RIGHT, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Array Dimension"), wxPoint(12,150), wxSize(90,21), wxALIGN_RIGHT, _T("ID_STATICTEXT5"));
	txtArraySize = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(108,148), wxSize(40,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	cboValueRank = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(108,120), wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxFieldDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxFieldDialog::OnbtnCancelClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxFieldDialog::OnbtnLookupClick);
	//*)

    this->SetTitle(title);

	//Tab ordering
	txtDescription->MoveAfterInTabOrder(txtName);
	cboDataType->MoveAfterInTabOrder(txtDescription);
	txtName->SetFocus();

    vector<wxString> cboList;
    cboList.push_back("Boolean");
    cboList.push_back("UInt32");
    cboList.push_back("Byte");

	this->cboDataType->Set(cboList);


	vector<wxString> cboValueRankList;
    cboValueRankList.push_back("Scalar");
    cboValueRankList.push_back("Array");
    cboValueRankList.push_back("ScalarOrArray");
    cboValueRankList.push_back("OneOrMoreDimensions");
	this->cboValueRank->Set(cboValueRankList);

	//Populate for edit
	if (paramEdit != 0)
    {
        this->txtName->SetValue(OPCUtils::GetString(paramEdit->Name()));

        wxString desc = OPCUtils::GetString(paramEdit->Description());
        if (desc.compare(NO_VALUE) !=0)
            this->txtDescription->SetValue(desc);

        this->cboDataType->SetValue(OPCUtils::GetName<Parameter::DataType_optional>(paramEdit->DataType()));

        wxString valueRank  = OPCUtils::GetString(paramEdit->ValueRank());
        if (valueRank.compare(NO_VALUE) !=0)
            this->cboValueRank->SetValue(valueRank);

        wxString arrayDimension = OPCUtils::GetString(paramEdit->ArrayDimensions());
        if (arrayDimension.compare(NO_VALUE) !=0)
            this->txtArraySize->SetValue(arrayDimension);

        m_param = paramEdit;
    }
    else
        m_param = &m_paramNew;
}

wxFieldDialog::~wxFieldDialog()
{
	//(*Destroy(wxFieldDialog)
	//*)
}

void wxFieldDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void wxFieldDialog::OnbtnOKClick(wxCommandEvent& event)
{
    if (!OPCUtils::IsStringValidQName(this->txtName, this->txtName->GetValue().ToStdString(), "Field Name"))
        return;

    if (!OPCUtils::IsStringValidQName(this->cboDataType, this->cboDataType->GetValue().ToStdString(), "Data Type"))
        return;

    Parameter::Name_optional name(this->txtName->GetValue().ToStdString());
    m_param->Name(name);

    Parameter::Description_optional desc(this->txtDescription->GetValue().ToStdString());
    m_param->Description(desc);

    //Find the actual element so we can get the prefix
    bool userOwner = true; //By default we make it a user owner just in case we could not find it.
    xml_schema::ncname nc(this->cboDataType->GetValue().ToStdString());
    ITERATE_MODELLIST(DataType, i, m_model)
    {
        string dataTypeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
        if (this->cboDataType->GetValue().ToStdString() ==dataTypeSymName)
        {
           userOwner = OPCUtils::IsUserNodeOwner(&(*i));
           break;
        }
    }

    xml_schema::qname qn((userOwner ? "" : "http://opcfoundation.org/UA/"), nc);
    Parameter::DataType_optional dataType(qn);
    m_param->DataType(dataType);

    string valueRank = this->cboValueRank->GetValue().ToStdString();
    if (valueRank.compare("") != 0)
        m_param->ValueRank(valueRank);

    m_param->ArrayDimensions(this->txtArraySize->GetValue().ToStdString());


    this->EndModal(0);
}

Parameter wxFieldDialog::GetParameter()
{
    return *this->m_param;
}

void wxFieldDialog::OnbtnLookupClick(wxCommandEvent& event)
{
    wxTreeDialog treeDlg(this, this->m_model, false, false, RootMaskShowDataType);
    treeDlg.ShowModal();

    if (treeDlg.GetReturnCode() == 0)
    {
        this->cboDataType->SetValue(treeDlg.SelectedSymbolicName);
    }
}

void wxFieldDialog::OntxtNameText(wxCommandEvent& event)
{
}
