#include <wxEnumDialog.h>
#include <opcutils.h>

#include <vector>
#include <wx/msgdlg.h>
#include <wx/log.h>

//(*InternalHeaders(wxEnumDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(wxEnumDialog)
const long wxEnumDialog::ID_STATICBOX1 = wxNewId();
const long wxEnumDialog::ID_STATICTEXT1 = wxNewId();
const long wxEnumDialog::ID_TEXTCTRL1 = wxNewId();
const long wxEnumDialog::ID_STATICTEXT2 = wxNewId();
const long wxEnumDialog::ID_STATICBOX2 = wxNewId();
const long wxEnumDialog::ID_BUTTON1 = wxNewId();
const long wxEnumDialog::ID_BUTTON2 = wxNewId();
const long wxEnumDialog::ID_TEXTCTRL3 = wxNewId();
const long wxEnumDialog::ID_STATICTEXT3 = wxNewId();
const long wxEnumDialog::ID_TEXTCTRL2 = wxNewId();
const long wxEnumDialog::ID_SPINBUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxEnumDialog,wxDialog)
	//(*EventTable(wxEnumDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxEnumDialog::wxEnumDialog(ModelDesign* model, wxWindow* parent,
                           int value, int increment, Parameter* paramEdit,
                           wxWindowID id,const wxPoint& pos,const wxSize& size)
                           : m_model(model), m_value(value), m_increment(increment)
{
	//(*Initialize(wxEnumDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(391,232));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,8), wxSize(376,168), 0, _T("ID_STATICBOX1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name"), wxPoint(48,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	txtName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(88,32), wxSize(280,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Description"), wxPoint(24,64), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,176), wxSize(376,48), 0, _T("ID_STATICBOX2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(232,192), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(304,192), wxSize(70,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	txtDescription = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(88,64), wxSize(280,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Value"), wxPoint(24,96), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	txtValue = new wxTextCtrl(this, ID_TEXTCTRL2, _("0"), wxPoint(88,96), wxSize(80,21), wxTE_RIGHT, m_vldNum, _T("ID_TEXTCTRL2"));
	btnValue = new wxSpinButton(this, ID_SPINBUTTON1, wxPoint(168,96), wxSize(17,24), wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	btnValue->SetRange(0, 100);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxEnumDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxEnumDialog::OnbtnCancelClick);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&wxEnumDialog::OnbtnValueChangeUp);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&wxEnumDialog::OnbtnValueChangeDown);
	//*)
    this->SetTitle("Enum Element");
    this->txtValue->SetValue(wxString::Format("%d", m_value));

	//Tab ordering
	txtDescription->MoveAfterInTabOrder(txtName);
	txtValue->MoveAfterInTabOrder(txtDescription);
    txtName->SetFocus();

    //Populate for edit
	if (paramEdit != 0)
    {
        this->txtName->SetValue(OPCUtils::GetString(paramEdit->Name()));

        wxString desc = OPCUtils::GetString(paramEdit->Description());
        if (desc.compare(NO_VALUE) !=0)
            this->txtDescription->SetValue(desc);

        //wxString idNumValue = OPCUtils::GetName<Parameter::Identifier_optional>(paramEdit->Identifier());
        //if (idNumValue.compare(NO_VALUE) !=0)
        //    this->txtValue->SetValue(idNumValue);

        this->txtValue->SetValue(OPCUtils::GetString(paramEdit->Identifier()));

        m_param = paramEdit;
    }
    else
        m_param = &m_paramNew;
}

wxEnumDialog::~wxEnumDialog()
{
	//(*Destroy(wxEnumDialog)
	//*)
}

void wxEnumDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void wxEnumDialog::OnbtnOKClick(wxCommandEvent& event)
{
    if (!OPCUtils::IsStringValidQName(this->txtName, this->txtName->GetValue().ToStdString(), "Enum Name"))
        return;

    //TODO: Other fields.
    //IsArray and IsOptional, what are the attributes of these two in the Parameter class?
    //UaModeler has this two.

    Parameter::Name_optional name(this->txtName->GetValue().ToStdString());
    m_param->Name(name);

    Parameter::Description_optional desc(this->txtDescription->GetValue().ToStdString());
    m_param->Description(desc);

    Parameter::Identifier_optional identNumValue(atoi(this->txtValue->GetValue().ToAscii()));
    m_param->Identifier(identNumValue);

    this->EndModal(0);
}

Parameter wxEnumDialog::GetParameter()
{
    return *this->m_param;
}

void wxEnumDialog::OnbtnValueChangeUp(wxSpinEvent& event)
{
    m_value += m_increment;
    this->txtValue->SetValue(wxString::Format("%d", m_value));
}

void wxEnumDialog::OnbtnValueChangeDown(wxSpinEvent& event)
{
    m_value -= m_increment;
    this->txtValue->SetValue(wxString::Format("%d", m_value));
}
