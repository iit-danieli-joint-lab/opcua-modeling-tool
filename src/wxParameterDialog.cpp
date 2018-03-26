#include <wxParameterDialog.h>
#include <wxTreeDialog.h>
#include <opcglobal.h>
#include <opcutils.h>

#include <vector>
#include <wx/msgdlg.h>
#include <wx/log.h>

//(*InternalHeaders(wxParameterDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(wxParameterDialog)
const long wxParameterDialog::ID_STATICBOX1 = wxNewId();
const long wxParameterDialog::ID_STATICTEXT1 = wxNewId();
const long wxParameterDialog::ID_TEXTCTRL1 = wxNewId();
const long wxParameterDialog::ID_STATICTEXT2 = wxNewId();
const long wxParameterDialog::ID_STATICBOX2 = wxNewId();
const long wxParameterDialog::ID_BUTTON1 = wxNewId();
const long wxParameterDialog::ID_BUTTON2 = wxNewId();
const long wxParameterDialog::ID_TEXTCTRL3 = wxNewId();
const long wxParameterDialog::ID_STATICTEXT3 = wxNewId();
const long wxParameterDialog::ID_COMBOBOX1 = wxNewId();
const long wxParameterDialog::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxParameterDialog,wxDialog)
	//(*EventTable(wxParameterDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxParameterDialog::wxParameterDialog(ModelDesign *model, wxWindow* parent, Parameter* paramEdit,
                                     wxWindowID id,const wxPoint& pos,const wxSize& size):  m_model(model)
{
	//(*Initialize(wxParameterDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(392,197));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,8), wxSize(376,128), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name"), wxPoint(48,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	txtName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(88,32), wxSize(280,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Description"), wxPoint(24,64), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,136), wxSize(376,48), 0, _T("ID_STATICBOX2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(232,152), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(304,152), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	txtDescription = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(88,64), wxSize(280,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Data Type"), wxPoint(24,96), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	cboDataType = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(88,96), wxSize(240,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	btnLookup = new wxButton(this, ID_BUTTON3, _("..."), wxPoint(336,96), wxSize(32,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxParameterDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxParameterDialog::OnbtnCancelClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxParameterDialog::OnbtnLookupClick);
	//*)

    this->SetTitle("Parameter");

	//Tab ordering
	txtDescription->MoveAfterInTabOrder(txtName);
	cboDataType->MoveAfterInTabOrder(txtDescription);
	txtName->SetFocus();

    vector<wxString> cboList;
    cboList.push_back("Boolean");
    cboList.push_back("UInt32");
    cboList.push_back("Byte");
    //cboList.push_back("...");
	this->cboDataType->Set(cboList);

	//Populate for edit
	if (paramEdit != 0)
    {
        this->txtName->SetValue(OPCUtils::GetString(paramEdit->Name()));

        wxString desc = OPCUtils::GetString(paramEdit->Description());
        if (desc.compare(NO_VALUE) !=0)
            this->txtDescription->SetValue(desc);

        this->cboDataType->SetValue(OPCUtils::GetName<Parameter::DataType_optional>(paramEdit->DataType()));

        m_param = paramEdit;
    }
    else
        m_param = &m_paramNew;
}

wxParameterDialog::~wxParameterDialog()
{
	//(*Destroy(wxParameterDialog)
	//*)
}

void wxParameterDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void wxParameterDialog::OnbtnOKClick(wxCommandEvent& event)
{
    if (!OPCUtils::IsStringValidQName(this->txtName, this->txtName->GetValue().ToStdString(), "Parameter Name"))
        return;

    if (!OPCUtils::IsStringValidQName(this->cboDataType, this->cboDataType->GetValue().ToStdString(), "Data Type"))
        return;

    Parameter::Name_optional name(this->txtName->GetValue().ToStdString());
    m_param->Name(name);

    Parameter::Description_optional desc(this->txtDescription->GetValue().ToStdString());
    m_param->Description(desc);

    xml_schema::ncname nc(this->cboDataType->GetValue().ToStdString());
    //TODO: Do we need prefix for DataType. It seems like the compiler doesn't complaim.
    xml_schema::qname qn(nc);
    Parameter::DataType_optional dataType(qn);
    m_param->DataType(dataType);

    this->EndModal(0);
}

Parameter wxParameterDialog::GetParameter()
{
    return *this->m_param;
}

void wxParameterDialog::OnbtnLookupClick(wxCommandEvent& event)
{
    wxTreeDialog treeDlg(this, this->m_model, false, false, RootMaskShowDataType);
    treeDlg.ShowModal();

    if (treeDlg.GetReturnCode() == 0)
        this->cboDataType->SetValue(treeDlg.SelectedSymbolicName);
}
