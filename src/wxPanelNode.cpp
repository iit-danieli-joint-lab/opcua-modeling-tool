#include <wxPanelNode.h>

#include <opcutils.h>

#include <wx/dataview.h>
#include <wx/wx.h>
#include <wx/hashset.h>

#include <iostream>
#include <sstream>
#include <map>

using namespace std;

//(*InternalHeaders(wxPanelNode)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelNode)
const long wxPanelNode::ID_STATICTEXT1 = wxNewId();
const long wxPanelNode::ID_TEXTCTRL1 = wxNewId();
const long wxPanelNode::ID_STATICTEXT2 = wxNewId();
const long wxPanelNode::ID_LISTVIEW1 = wxNewId();
const long wxPanelNode::ID_PANEL2 = wxNewId();
const long wxPanelNode::ID_STATICTEXT4 = wxNewId();
const long wxPanelNode::ID_LISTVIEW3 = wxNewId();
const long wxPanelNode::ID_PANEL1 = wxNewId();
const long wxPanelNode::ID_STATICTEXT3 = wxNewId();
const long wxPanelNode::ID_LISTVIEW2 = wxNewId();
const long wxPanelNode::ID_PANEL3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelNode,wxPanel)
	//(*EventTable(wxPanelNode)
	//*)
END_EVENT_TABLE()

wxPanelNode::wxPanelNode(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelNode)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* boxSizerReferences;
	wxBoxSizer* boxSizerSymName;
	wxBoxSizer* boxSizerField;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* boxSizerChildren;
	wxBoxSizer* mainSizer;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	mainSizer = new wxBoxSizer(wxVERTICAL);
	boxSizerSymName = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Symbolic Name"), wxDefaultPosition, wxSize(150,21), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	StaticText1->SetMinSize(wxSize(150,21));
	StaticText1->SetMaxSize(wxSize(150,21));
	boxSizerSymName->Add(StaticText1, 1, wxALL|wxALIGN_TOP, 5);
	txtSymbolicName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	boxSizerSymName->Add(txtSymbolicName, 1, wxALL|wxEXPAND, 5);
	mainSizer->Add(boxSizerSymName, 0, wxEXPAND, 5);
	boxSizerChildren = new wxBoxSizer(wxVERTICAL);
	panelChildren = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	StaticText2 = new wxStaticText(panelChildren, ID_STATICTEXT2, _("Children"), wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, _T("ID_STATICTEXT2"));
	BoxSizer4->Add(StaticText2, 0, wxEXPAND, 5);
	childrenListViewCtrl = new wxListView(panelChildren, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW1"));
	BoxSizer4->Add(childrenListViewCtrl, 1, wxEXPAND, 0);
	panelChildren->SetSizer(BoxSizer4);
	BoxSizer4->Fit(panelChildren);
	BoxSizer4->SetSizeHints(panelChildren);
	boxSizerChildren->Add(panelChildren, 1, wxALL|wxEXPAND, 5);
	mainSizer->Add(boxSizerChildren, 1, wxTOP|wxEXPAND, 5);
	boxSizerField = new wxBoxSizer(wxVERTICAL);
	panelField = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	StaticText4 = new wxStaticText(panelField, ID_STATICTEXT4, _("Field"), wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, _T("ID_STATICTEXT4"));
	BoxSizer3->Add(StaticText4, 0, wxTOP|wxEXPAND, 5);
	fieldListViewCtrl = new wxListView(panelField, ID_LISTVIEW3, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW3"));
	BoxSizer3->Add(fieldListViewCtrl, 1, wxEXPAND, 5);
	panelField->SetSizer(BoxSizer3);
	BoxSizer3->Fit(panelField);
	BoxSizer3->SetSizeHints(panelField);
	boxSizerField->Add(panelField, 1, wxALL|wxEXPAND, 5);
	mainSizer->Add(boxSizerField, 1, wxEXPAND, 0);
	boxSizerReferences = new wxBoxSizer(wxVERTICAL);
	panelReference = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText3 = new wxStaticText(panelReference, ID_STATICTEXT3, _("Reference"), wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, _T("ID_STATICTEXT3"));
	BoxSizer1->Add(StaticText3, 0, wxTOP|wxEXPAND, 5);
	referenceListViewCtrl = new wxListView(panelReference, ID_LISTVIEW2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTVIEW2"));
	referenceListViewCtrl->SetMaxSize(wxSize(-1,200));
	BoxSizer1->Add(referenceListViewCtrl, 1, wxEXPAND, 5);
	panelReference->SetSizer(BoxSizer1);
	BoxSizer1->Fit(panelReference);
	BoxSizer1->SetSizeHints(panelReference);
	boxSizerReferences->Add(panelReference, 1, wxALL|wxEXPAND, 5);
	mainSizer->Add(boxSizerReferences, 1, wxEXPAND, 5);
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);
	//*)

    m_mainSizer             = mainSizer;
    m_boxSizerChildren      = boxSizerChildren;
    m_boxSizerReferences    = boxSizerReferences;
    m_boxSizerField          = boxSizerField;

    //TODO: Temporarily hide code as we are not sure to use this control or not.
    //gridBagSizerPanelNode->Hide(childrenDataViewCtrl, true);

    {
    //Children Using ListView
    // Add 1st column
    wxListItem col0;
    col0.SetWidth(300);
    col0.SetText( _("Name") );
    childrenListViewCtrl->InsertColumn(0, col0);

    // Add 3rd column
    wxListItem col1;
    col1.SetWidth(200);
    col1.SetText( _("Type Definition") );
    childrenListViewCtrl->InsertColumn(1, col1);

    // Add 4th column
    wxListItem col2;
    col2.SetWidth(300);
    col2.SetText( _("Data Type") );
    childrenListViewCtrl->InsertColumn(2, col2);
    }

    {
    //References
    // Add first column
    wxListItem refCol0;
    refCol0.SetWidth(300);
    refCol0.SetText( _("Reference Type") );
    referenceListViewCtrl->InsertColumn(0, refCol0);

    // Add second column
    wxListItem refCol1;
    refCol1.SetWidth(300);
    refCol1.SetText( _("Target") );
    referenceListViewCtrl->InsertColumn(1, refCol1);
    }
}

wxPanelNode::~wxPanelNode()
{
	//(*Destroy(wxPanelNode)
	//*)
}
void wxPanelNode::Init(NodeDesign* node, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                       bool userOwner, bool hideField, bool hideChildren, bool hideRefereces)
{
    this->Clear();
    this->m_node            = node;
    this->m_model           = model;
    this->m_mainFrame       = mainFrame;
    this->m_treeItemId      = treeItemId;

    this->txtSymbolicName->Enable(userOwner);

    this->HideField(hideField);
    this->HideChildren(hideChildren);
    this->HideReferences(hideRefereces);
}

void wxPanelNode::Clear()
{
    this->txtSymbolicName->SetValue("");
    this->fieldListViewCtrl->DeleteAllItems();
    this->childrenListViewCtrl->DeleteAllItems();
    this->referenceListViewCtrl->DeleteAllItems();
}

void wxPanelNode::PopulateData()
{
    this->txtSymbolicName->SetValue(OPCUtils::GetName(this->m_node->SymbolicName()));
}

void wxPanelNode::PopulateReferencesListCtrl(NodeDesign::References_optional *references, int &nodeId, bool disabled)
{
    for (ListOfReferences::Reference_const_iterator i((*references)->Reference().begin());
         i != (*references)->Reference().end();
         ++i)
    {
        SetReferenceItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }
}

void wxPanelNode::PopulateChildrenListCtrl(NodeDesign::Children_optional *children, int &nodeId, bool disabled)
{
    //Object
    ITERATE_FROM_CHILDREN(Object, (*children), i)
    {
        SetChildrenItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }

    //Variable
    ITERATE_FROM_CHILDREN(Variable, (*children), i)
    {
        SetChildrenItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }

    //Property
    ITERATE_FROM_CHILDREN(Property, (*children), i)
    {
        SetChildrenItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }

    //Method
    ITERATE_FROM_CHILDREN(Method, (*children), i)
    {
        SetChildrenItemNodeValues(&(*i), nodeId, disabled);
        ++nodeId;
    }
}

void wxPanelNode::PopulateChildren(NodeDesign::Children_optional *children)
{
    this->childrenListViewCtrl->DeleteAllItems();

    int nodeId = 0;

    //Add own children to the list control
    if(this->m_node->Children() != 0)
        PopulateChildrenListCtrl(&this->m_node->Children(), nodeId, false);

    PopulateChildrenListCtrl(children, nodeId, true);
}

void wxPanelNode::PopulateReferences(NodeDesign::References_optional *references)
{
    this->referenceListViewCtrl->DeleteAllItems();

    int nodeId = 0;

    //Add own references to the list control
    if(this->m_node->References() != 0)
        PopulateReferencesListCtrl(&this->m_node->References(), nodeId, false);

    //Add inherited references to the list control
    PopulateReferencesListCtrl(references, nodeId, true);
}

void wxPanelNode::SetChildrenItemNodeValues(const NodeDesign *node, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    //column 0
    item.SetText(OPCUtils::GetString((node->SymbolicName() != 0 ) ? node->SymbolicName()->name() : NO_VALUE));
    childrenListViewCtrl->InsertItem(item);

    //N.B: We can move this code specific to instances but that would make the Children list view
    //dynamic with its column and content which would add more customization.
    //TODO: Consider making these implementation specific to class type.
    const PropertyDesign* property = dynamic_cast<const PropertyDesign*>(node);
    if (property != 0)
    {
        string dataType = OPCUtils::GetName<VariableTypeDesign::DataType_optional>(property->DataType(), string(""));
        childrenListViewCtrl->SetItem(nodeId, 2, dataType);     //column 2
    }
    else
    {
        const InstanceDesign* instance = dynamic_cast<const InstanceDesign*>(node);
        if (instance !=0)
        {
            string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(instance->TypeDefinition(), "");
            childrenListViewCtrl->SetItem(nodeId, 1, typeDef);  //column 1
        }
    }
}

void wxPanelNode::SetReferenceItemNodeValues(const Reference* ref, int nodeId, bool disabled)
{
    wxListItem item;
    item.SetId(nodeId); //TODO: Do we need an id? When clicked?
    if (disabled)
        item.SetBackgroundColour(*wxLIGHT_GREY);

    item.SetText(OPCUtils::GetString(ref->ReferenceType().name()));                             //column 0
    referenceListViewCtrl->InsertItem(item);

    referenceListViewCtrl->SetItem(nodeId, 1, OPCUtils::GetString( ref->TargetId().name()));    //column 1
}

bool wxPanelNode::UpdateData(const char *nodePrefix)
{
    string symName = this->txtSymbolicName->GetValue().ToStdString();
    if (!OPCUtils::SetSymName(this->m_node, symName))
    {
        this->txtSymbolicName->SetFocus();
        return false;
    }

    return true;
}

void wxPanelNode::DeleteChildren()
{
    this->childrenListViewCtrl->DeleteAllItems();

    if (this->m_node->Children() == 0)
        return;

    this->m_node->Children()->Object().erase(this->m_node->Children()->Object().begin(), this->m_node->Children()->Object().end());
    this->m_node->Children()->Variable().erase(this->m_node->Children()->Variable().begin(), this->m_node->Children()->Variable().end());
    this->m_node->Children()->Property().erase(this->m_node->Children()->Property().begin(), this->m_node->Children()->Property().end());
    this->m_node->Children()->Method().erase(this->m_node->Children()->Method().begin(), this->m_node->Children()->Method().end());
}

void wxPanelNode::DeleteReferences()
{
    this->referenceListViewCtrl->DeleteAllItems();

    if (this->m_node->References() == 0)
        return;

    this->m_node->References()->Reference().erase(this->m_node->References()->Reference().begin(), this->m_node->References()->Reference().end());
}

void wxPanelNode::CopyParent(NodeDesign* sourceNode, NodeDesign::Children_optional *inheritedChildren,
                             NodeDesign::References_optional *inheritedReferences)
{
    if (sourceNode->Children() != 0)
    {
        //Copy Object source to the children
        ITERATE_CHILDREN(Object, sourceNode, i)
        {
            (*inheritedChildren)->Object().push_back(*i);
        }

        //Copy Property source to the children
        ITERATE_CHILDREN(Property, sourceNode, i)
        {
            (*inheritedChildren)->Property().push_back(*i);
        }

        //Copy Method source to the children
        ITERATE_CHILDREN(Method, sourceNode, i)
        {
            (*inheritedChildren)->Method().push_back(*i);
        }

        //Copy Variable source to the children
        ITERATE_CHILDREN(Variable, sourceNode, i)
        {
            (*inheritedChildren)->Variable().push_back(*i);
        }
    }

    if (sourceNode->References() != 0)
    {
        //Copy source References to the references
        for (ListOfReferences::Reference_const_iterator i(sourceNode->References()->Reference().begin());
             i != sourceNode->References()->Reference().end();
             ++i)
        {
           (*inheritedReferences)->Reference().push_back(*i);
        }
    }

    //TODO: What happens to the existing custom children and references added? Ask confirmation to delete all?
    //TODO: Recreate the tree node as it will have a new structure

    //TODO: Get BaseType
    //TODO: Call this recursively to add more children and references from the Base Type
}

void wxPanelNode::HideField(bool hide)
{
    if (hide)
        this->m_boxSizerField->Hide(this->panelField, true);
    else
        this->m_boxSizerField->Show(this->panelField, true);

    this->m_boxSizerField->Layout();
    this->m_mainSizer->Layout();
}

void wxPanelNode::HideChildren(bool hide)
{
    if (hide)
        this->m_boxSizerChildren->Hide(this->panelChildren, true);
    else
        this->m_boxSizerChildren->Show(this->panelChildren, true);

    this->m_boxSizerChildren->Layout();
    this->m_mainSizer->Layout();
}


void wxPanelNode::HideReferences(bool hide)
{
    if (hide)
        this->m_boxSizerReferences->Hide(this->panelReference, true);
    else
        this->m_boxSizerReferences->Show(this->panelReference, true);

    this->m_boxSizerReferences->Layout();
    this->m_mainSizer->Layout();
}

wxListView* wxPanelNode::GetFieldListView()
{
    return this->fieldListViewCtrl;
}

void wxPanelNode::OnPaint(wxPaintEvent& event)
{
}
