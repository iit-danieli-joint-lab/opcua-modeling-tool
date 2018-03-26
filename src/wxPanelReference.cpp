#include <wxPanelReference.h>
#include <opcutils.h>
#include <synthesis/opc.hxx>
#include <wxTreeDialog.h>

#include <wx/wx.h>


using namespace std;

//(*InternalHeaders(wxPanelReference)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelReference)
const long wxPanelReference::ID_STATICTEXT1 = wxNewId();
const long wxPanelReference::ID_TEXTCTRL2 = wxNewId();
const long wxPanelReference::ID_BUTTON2 = wxNewId();
const long wxPanelReference::ID_STATICTEXT2 = wxNewId();
const long wxPanelReference::ID_TEXTCTRL1 = wxNewId();
const long wxPanelReference::ID_BUTTON1 = wxNewId();
const long wxPanelReference::ID_STATICTEXT4 = wxNewId();
const long wxPanelReference::ID_CHECKBOX1 = wxNewId();
const long wxPanelReference::ID_STATICTEXT3 = wxNewId();
const long wxPanelReference::ID_CHECKBOX2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelReference,wxPanel)
	//(*EventTable(wxPanelReference)
	//*)
END_EVENT_TABLE()

wxPanelReference::wxPanelReference(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelReference)
	wxBoxSizer* BoxSizer4;
	wxGridBagSizer* GridBagSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("wxID_ANY"));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer1->AddGrowableCol(0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Reference Type"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText1->SetMaxSize(wxSize(150,-1));
	BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtReferenceType = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer1->Add(txtReferenceType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnLookupRefType = new wxButton(this, ID_BUTTON2, _("..."), wxDefaultPosition, wxSize(30,0), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnLookupRefType->SetMinSize(wxSize(30,21));
	btnLookupRefType->SetMaxSize(wxSize(30,21));
	BoxSizer1->Add(btnLookupRefType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(BoxSizer1, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Target Id"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	StaticText2->SetMaxSize(wxSize(150,-1));
	BoxSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtTargetId = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(txtTargetId, 1, wxALL|wxEXPAND, 5);
	btnShowTree = new wxButton(this, ID_BUTTON1, _("..."), wxDefaultPosition, wxSize(30,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnShowTree->SetMinSize(wxSize(30,21));
	btnShowTree->SetMaxSize(wxSize(30,0));
	BoxSizer2->Add(btnShowTree, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(BoxSizer2, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Inverse"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT4"));
	StaticText4->SetMaxSize(wxSize(150,-1));
	BoxSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInverse = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkInverse->SetValue(false);
	BoxSizer3->Add(chkInverse, 1, wxALL|wxEXPAND, 5);
	GridBagSizer1->Add(BoxSizer3, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("One Way"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	StaticText3->SetMaxSize(wxSize(150,-1));
	BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkOneWay = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkOneWay->SetValue(false);
	BoxSizer4->Add(chkOneWay, 1, wxALL|wxEXPAND, 5);
	GridBagSizer1->Add(BoxSizer4, wxGBPosition(3, 0), wxDefaultSpan, wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPanelReference::OnbtnLookupRefTypeClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPanelReference::OnbtnShowTreeClick1);
	//*)

    //Tab ordering
	txtTargetId->MoveAfterInTabOrder(txtReferenceType);
	txtReferenceType->SetFocus();


}

wxPanelReference::~wxPanelReference()
{
	//(*Destroy(wxPanelReference)
	//*)
}

void wxPanelReference::Clear()
{
    this->txtTargetId->SetValue("");
    this->txtReferenceType->SetValue("");
}

void wxPanelReference::Init(Reference* reference, ModelDesign* model, wxTreeItemId treeItemId,
                            wxFrameMain* mainFrame, bool userOwner)
{
    this->m_reference       = reference;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;

    this->chkInverse->Enable(userOwner);
    this->chkOneWay->Enable(userOwner);
    this->txtReferenceType->Enable(userOwner);
    this->txtTargetId->Enable(userOwner);
    this->btnLookupRefType->Enable(userOwner);
    this->btnShowTree->Enable(userOwner);

    this->Clear();
}

bool wxPanelReference::UpdateData()
{
    string referenceType = this->txtReferenceType->GetValue().ToStdString();
    if (referenceType.length() == 0)
    {
        ::wxMessageBox("ReferenceType is mandatory.", "Update Error");
        return false;
    }

    wxString targetIdStr  = this->txtTargetId->GetValue();
    if(   targetIdStr.Len() == 0
       || targetIdStr.Find(' ') != -1)
    {
        wxMessageBox("TargetId is empty or has spaces.", "Error");
        this->txtTargetId->SetFocus();
        return false;
    }

    xml_schema::ncname ncTarget(targetIdStr.ToStdString());
    xml_schema::qname qnTarget(m_refTargetIdNS, ncTarget);
    Reference::TargetId_type targetId(qnTarget);
    this->m_reference->TargetId(targetId);

    xml_schema::ncname nc(referenceType);
    xml_schema::qname qn(m_refTargetRefTypeNS, nc);
    Reference::ReferenceType_type refType(qn);
    this->m_reference->ReferenceType(refType);

    this->m_reference->IsInverse(this->chkInverse->GetValue());
    this->m_reference->IsOneWay(this->chkOneWay->GetValue());

    return true;
}

void wxPanelReference::PopulateData()
{
    this->Clear();

    this->txtTargetId->SetValue(OPCUtils::GetStringFromQName(this->m_reference->TargetId()));
    this->m_refTargetIdNS =  this->m_reference->TargetId().namespace_();

    this->txtReferenceType->SetValue(OPCUtils::GetStringFromQName(this->m_reference->ReferenceType()));
    this->m_refTargetRefTypeNS =  this->m_reference->ReferenceType().namespace_();

    this->chkInverse->SetValue(this->m_reference->IsInverse());
    this->chkOneWay->SetValue(this->m_reference->IsOneWay());
}

void wxPanelReference::OnbtnShowTreeClick1(wxCommandEvent& event)
{
    wxTreeDialog treeDlg(this, m_model, true, false);
    treeDlg.ShowModal();

    if (treeDlg.SelectedStringId.length() > 0)
    {
        this->m_refTargetIdNS = treeDlg.SelectedNamespace;
        this->txtTargetId->SetValue(treeDlg.SelectedStringId);
    }
}

void wxPanelReference::OnbtnLookupRefTypeClick(wxCommandEvent& event)
{
    wxTreeDialog treeDlg(this, this->m_model, false, false, RootMaskShowReferenceType);
    treeDlg.ShowModal();

    if (treeDlg.GetReturnCode() == 0)
    {
        this->m_refTargetRefTypeNS = treeDlg.SelectedNamespace;
        this->txtReferenceType->SetValue(treeDlg.SelectedSymbolicName);
    }
}

