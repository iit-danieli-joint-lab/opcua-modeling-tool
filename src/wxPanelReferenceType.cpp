#include <wxPanelReferenceType.h>
#include <wxPanelType.h>
#include <synthesis/opc.hxx>
#include <opcutils.h>

//(*InternalHeaders(wxPanelReferenceType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelReferenceType)
const long wxPanelReferenceType::ID_CUSTOM1 = wxNewId();
const long wxPanelReferenceType::ID_STATICTEXT1 = wxNewId();
const long wxPanelReferenceType::ID_CHECKBOX1 = wxNewId();
const long wxPanelReferenceType::ID_StaticText1 = wxNewId();
const long wxPanelReferenceType::ID_txtInverseName = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelReferenceType,wxPanel)
	//(*EventTable(wxPanelReferenceType)
	//*)
END_EVENT_TABLE()
using namespace std;

wxPanelReferenceType::wxPanelReferenceType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelReferenceType)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	panelType = new wxPanelType(this,ID_CUSTOM1);
	BoxSizer2->Add(panelType, 1, wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT1, _("Symmetric"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText2->SetMinSize(wxSize(150,-1));
	StaticText2->SetMaxSize(wxSize(150,-1));
	BoxSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSymmetric = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkSymmetric->SetValue(false);
	BoxSizer3->Add(chkSymmetric, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_StaticText1, _("Inverse Name"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_StaticText1"));
	StaticText1->SetMinSize(wxSize(150,-1));
	StaticText1->SetMaxSize(wxSize(150,-1));
	BoxSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtInverseName = new wxTextCtrl(this, ID_txtInverseName, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_txtInverseName"));
	BoxSizer4->Add(txtInverseName, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

wxPanelReferenceType::~wxPanelReferenceType()
{
	//(*Destroy(wxPanelReferenceType)
	//*)
}
bool wxPanelReferenceType::UpdateData()
{
    bool retVal = false;
    this->m_refType->Symmetric(this->chkSymmetric->GetValue());
    this->m_refType->InverseName(this->txtInverseName->GetValue().ToStdString());
    retVal = this->panelType->UpdateData("ReferenceType");
    return retVal;
}

void wxPanelReferenceType::PopulateData()
{
    wxString inverseName = OPCUtils::GetString(this->m_refType->InverseName());
    if (inverseName.compare(NO_VALUE) !=0)
        this->txtInverseName->SetValue(inverseName);
    this->chkSymmetric->SetValue(this->m_refType->Symmetric());

    this->panelType->PopulateData(NodeTypeReferenceType);

}

void wxPanelReferenceType::Init(ReferenceTypeDesign* refType, ModelDesign* model, wxTreeItemId treeItemId,
                                wxFrameMain* mainFrame, bool userOwner)
{
    this->m_refType      = refType;
    this->m_model        = model;
    this->m_treeItemId   = treeItemId;
    this->m_mainFrame    = mainFrame;

    this->chkSymmetric->Enable(userOwner);
    this->txtInverseName->Enable(userOwner);

    this->panelType->Init(refType, model, treeItemId, mainFrame, userOwner);

    this->txtInverseName->SetValue("");
}


