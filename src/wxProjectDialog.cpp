#include "opcutils.h"
#include "wxProjectDialog.h"


#include <sstream>

//(*InternalHeaders(wxProjectDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxProjectDialog)
const long wxProjectDialog::ID_STATICBOX1 = wxNewId();
const long wxProjectDialog::ID_TEXTCTRL1 = wxNewId();
const long wxProjectDialog::ID_STATICTEXT1 = wxNewId();
const long wxProjectDialog::ID_STATICTEXT3 = wxNewId();
const long wxProjectDialog::ID_TEXTCTRL3 = wxNewId();
const long wxProjectDialog::ID_STATICBOX2 = wxNewId();
const long wxProjectDialog::ID_BUTTON1 = wxNewId();
const long wxProjectDialog::ID_BUTTON2 = wxNewId();
const long wxProjectDialog::ID_STATICTEXT4 = wxNewId();
const long wxProjectDialog::ID_TEXTCTRL4 = wxNewId();
const long wxProjectDialog::ID_STATICBOX3 = wxNewId();
const long wxProjectDialog::ID_STATICBOX4 = wxNewId();
const long wxProjectDialog::ID_LISTVIEW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxProjectDialog,wxDialog)
	//(*EventTable(wxProjectDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxProjectDialog::wxProjectDialog(ModelDesign* model,wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) : m_model(model)
{
	//(*Initialize(wxProjectDialog)
	Create(parent, wxID_ANY, _("Project Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(663,381));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(8,0), wxSize(648,136), 0, _T("ID_STATICBOX1"));
	txtName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(118,32), wxSize(200,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name(XmlPrefix)"), wxPoint(16,33), wxSize(90,13), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Model URI"), wxPoint(16,66), wxSize(90,13), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	txtFullURI = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(118,64), wxSize(530,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,328), wxSize(648,45), 0, _T("ID_STATICBOX2"));
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(476,344), wxSize(75,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(568,344), wxSize(72,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Project File"), wxPoint(16,98), wxSize(90,13), wxALIGN_RIGHT, _T("ID_STATICTEXT4"));
	txtFilename = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxPoint(118,96), wxSize(530,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Label"), wxPoint(72,480), wxDefaultSize, 0, _T("ID_STATICBOX3"));
	StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Namespaces"), wxPoint(8,137), wxSize(648,190), 0, _T("ID_STATICBOX4"));
	lstNamespaces = new wxListView(this, ID_LISTVIEW1, wxPoint(24,160), wxSize(624,152), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW1"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxProjectDialog::OnbtnCancelClick);
	//*)

    //N.B:
    //The main reason why we separate the main project configuration so we can
    //derive the Targetnamespace and xmlns ModelDesign attributes from the project values.

    wxListItem col0;
    col0.SetWidth(100);
    col0.SetText( _("Name"));
    this->lstNamespaces->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetWidth(100);
    col1.SetText( _("XmlPrefix"));
    this->lstNamespaces->InsertColumn(1, col1);

    wxListItem col2;
    col2.SetWidth(150);
    col2.SetText( _("FilePath"));
    this->lstNamespaces->InsertColumn(2, col2);

    wxListItem col3;
    col3.SetWidth(300);
    col3.SetText( _("URI"));
    this->lstNamespaces->InsertColumn(3, col3);

    wxListItem col4;
    col4.SetWidth(100);
    col4.SetText( _("Prefix"));
    this->lstNamespaces->InsertColumn(4, col4);

    wxListItem col5;
    col5.SetWidth(100);
    col5.SetText( _("InternalPrefix"));
    this->lstNamespaces->InsertColumn(5, col5);

    wxListItem col6;
    col6.SetWidth(300);
    col6.SetText( _("XmlNamespace"));
    this->lstNamespaces->InsertColumn(6, col6);


    //TODO: Allow add/edit/delete of other namespaces except for the default OpcUa server entry.
}

wxProjectDialog::~wxProjectDialog()
{
	//(*Destroy(wxProjectDialog)
	//*)
}

void wxProjectDialog::SetEditable(bool editable)
{
    this->txtName->SetEditable(editable);
	this->txtFullURI->SetEditable(editable);
}

void wxProjectDialog::OnbtnOKClick(wxCommandEvent& event)
{
    if (txtName->IsEditable())
    {
        if(!OPCUtils::IsStringValidQName(txtName, txtName->GetValue().ToStdString(), "Model Name"))
            return;

        if(!OPCUtils::IsStringValidQName(txtFullURI, txtFullURI->GetValue().ToStdString(), "URI"))
            return;
    }
    this->EndDialog(wxID_OK);
}

void wxProjectDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndDialog(wxID_CANCEL);
}

void wxProjectDialog::LoadOtherNamespaces()
{
    if (this->m_model->Namespaces() == 0)
        return;

    int nodeId = 0;
    for (NamespaceTable::Namespace_iterator i(this->m_model->Namespaces()->Namespace().begin());
                                                      i != this->m_model->Namespaces()->Namespace().end();
                                                      ++i)
    {
        stringstream ssName;
        if (i->Name() != 0)
            ssName << i->Name();

        /* I think it's better to just show all the namespaces including the main project.
        //Do not display the main project namespace entry.
        //We take first the XmlPrefix as the main project namespace entry.
        //If it doesn't exist check the name attribute.
        //This logic should match with wxFrameMain::OpenModel()
        stringstream ssXmlPrefix;
        if (i->XmlPrefix() != 0)
        {
            ssXmlPrefix << i->XmlPrefix();
            if (ssName.str() == txtName->GetValue().ToStdString())
                continue;
        }
        else
        {
            if (ssName.str() == txtName->GetValue().ToStdString())
                continue;
        }
        */

        stringstream ssfilePath;
        if (i->FilePath() != 0)
            ssfilePath << i->FilePath();

        stringstream ssXmlPrefixName;
        if (i->XmlPrefix() != 0)
            ssXmlPrefixName << i->XmlPrefix();

        stringstream ssPrefix;
        if (i->Prefix() != 0)
            ssPrefix << i->Prefix();

        stringstream ssInternalPrefix;
        if (i->InternalPrefix() != 0)
            ssInternalPrefix << i->InternalPrefix();

        stringstream ssXmlNamespace;
        if (i->XmlNamespace() != 0)
            ssXmlNamespace << i->XmlNamespace();

        wxListItem item;
        item.SetId(nodeId);
        item.SetText(ssName.str());                                         //column 0
        this->lstNamespaces->InsertItem(item);
        this->lstNamespaces->SetItem(nodeId, 1, ssXmlPrefixName.str());     //column 1
        this->lstNamespaces->SetItem(nodeId, 2, ssfilePath.str());          //column 2
        this->lstNamespaces->SetItem(nodeId, 3, *i);                        //column 3
        this->lstNamespaces->SetItem(nodeId, 4, ssPrefix.str());            //column 4
        this->lstNamespaces->SetItem(nodeId, 5, ssInternalPrefix.str());    //column 5
        this->lstNamespaces->SetItem(nodeId, 6, ssXmlNamespace.str());      //column 6
        nodeId++;
        }
}
