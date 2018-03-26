#include <wxPanelType.h>

#include <wxPanelNode.h>
#include <wxFrameMain.h>
#include <opcutils.h>
#include <wx/log.h>

#include <vector>

//(*InternalHeaders(wxPanelType)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxPanelType)
const long wxPanelType::ID_STATICTEXT3 = wxNewId();
const long wxPanelType::ID_CHECKBOX2 = wxNewId();
const long wxPanelType::ID_STATICTEXT2 = wxNewId();
const long wxPanelType::ID_CHECKBOX1 = wxNewId();
const long wxPanelType::ID_PANEL1 = wxNewId();
const long wxPanelType::ID_CUSTOM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPanelType,wxPanel)
	//(*EventTable(wxPanelType)
	//*)
END_EVENT_TABLE()

using namespace std;

wxPanelType::wxPanelType(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPanelType)
	wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer1->AddGrowableCol(0);
	GridBagSizer1->AddGrowableRow(0);
	panelType = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	GridBagSizer2->AddGrowableCol(0);
	GridBagSizer2->AddGrowableRow(0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(panelType, ID_STATICTEXT3, _("No Class Generation"), wxDefaultPosition, wxSize(150,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
	StaticText3->SetMaxSize(wxSize(150,-1));
	BoxSizer2->Add(StaticText3, 1, wxALL|wxEXPAND, 5);
	chkNoClassGen = new wxCheckBox(panelType, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkNoClassGen->SetValue(false);
	BoxSizer2->Add(chkNoClassGen, 1, wxALL|wxEXPAND, 5);
	GridBagSizer2->Add(BoxSizer2, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(panelType, ID_STATICTEXT2, _("Abstract"), wxDefaultPosition, wxSize(150,13), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	StaticText2->SetMaxSize(wxSize(150,-1));
	BoxSizer3->Add(StaticText2, 1, wxALL|wxEXPAND, 5);
	chkAbstract = new wxCheckBox(panelType, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkAbstract->SetValue(false);
	BoxSizer3->Add(chkAbstract, 1, wxALL|wxEXPAND, 5);
	GridBagSizer2->Add(BoxSizer3, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	panelType->SetSizer(GridBagSizer2);
	GridBagSizer2->Fit(panelType);
	GridBagSizer2->SetSizeHints(panelType);
	GridBagSizer1->Add(panelType, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	panelNode = new wxPanelNode(this,ID_CUSTOM1);
	BoxSizer1->Add(panelNode, 1, wxEXPAND, 5);
	GridBagSizer1->Add(BoxSizer1, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);
	//*)
}

wxPanelType::~wxPanelType()
{
	//(*Destroy(wxPanelType)
	//*)
}

bool wxPanelType::UpdateData(const char *nodePrefix)
{
    this->m_type->IsAbstract(this->chkAbstract->GetValue());
    this->m_type->NoClassGeneration(this->chkNoClassGen->GetValue());

    return this->panelNode->UpdateData(nodePrefix);
}

void wxPanelType::PopulateData(const enum NodeType nodeType)
{
    this->chkAbstract->SetValue(this->m_type->IsAbstract());
    this->chkNoClassGen->SetValue(this->m_type->NoClassGeneration());

    ListOfChildren childrenList;
    ListOfReferences referencesList;
    NodeDesign::Children_optional children(childrenList);
    NodeDesign::References_optional references(referencesList);

    //TODO: Populate own fields here.

    wxString baseType        = OPCUtils::GetName<TypeDesign::BaseType_optional>(this->m_type->BaseType());
    int indexFoundForTypeDef = -1;
    int nodeIndex            = 0;

    //TODO: Make this selection polymorphic
    //      If they have their own panel, let's move this code to their ownself.
    switch (nodeType)
    {
        case NodeTypeObjectType:
            {
               ITERATE_MODELLIST(ObjectType, i, m_model)
               {
                    wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

                    //Find the ObjectType that the Object has typedef'd from.
                    if (    -1 == indexFoundForTypeDef
                         &&  0 != this->m_type->BaseType()
                         &&  0 == symName.compare(baseType) )
                    {
                        indexFoundForTypeDef = nodeIndex;
                        this->CopyParent(&(*i), &children, &references);
                    }
                    ++nodeIndex;
                }
                this->panelNode->PopulateChildren(&children);
                break;
            }

        case NodeTypeVariableType:
            {
                ITERATE_MODELLIST(VariableType, i, m_model)
                {
                    wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());


                    //Find the VariableType that the Object has typedef'd from.
                    if (    -1 == indexFoundForTypeDef
                         &&  0 != this->m_type->BaseType()
                         &&  0 == symName.compare(baseType) )
                    {
                        indexFoundForTypeDef = nodeIndex;
                        this->CopyParent(&(*i), &children, &references);
                    }
                    ++nodeIndex;
                }
                this->panelNode->PopulateChildren(&children);
                break;
            }
        case NodeTypeDataType:
            {
                ITERATE_MODELLIST(DataType, i, m_model)
                {
                    wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

                    //Find the VariableType that the Object has typedef'd from.
                    if (    -1 == indexFoundForTypeDef
                         &&  0 != this->m_type->BaseType()
                         &&  0 == symName.compare(baseType))
                    {
                        indexFoundForTypeDef = nodeIndex;
                        this->CopyParent(&(*i), &children, &references);
                    }
                    ++nodeIndex;
                }
                this->panelNode->PopulateChildren(&children);
                break;
            }
        default:
            cerr << "Error: wxPanelType::PopulateData() case:" << nodeType << " not handled.\n";
    }
    //TODO: Other model element type

    this->panelNode->PopulateData();

    this->panelNode->PopulateReferences(&references);
}

void wxPanelType::Init(TypeDesign* type, ModelDesign *model, wxTreeItemId treeItemId, wxFrameMain *mainFrame,
                       bool userOwner, bool hideEnum, bool hideChildren)
{
    this->m_type            = type;
    this->m_model           = model;
    this->m_treeItemId      = treeItemId;
    this->m_mainFrame       = mainFrame;

    this->chkNoClassGen->Enable(userOwner);
    this->chkAbstract->Enable(userOwner);

    this->panelNode->Init(type, model, treeItemId, mainFrame, userOwner, hideEnum, hideChildren);
}

void wxPanelType::CopyParent(TypeDesign *type, NodeDesign::Children_optional *inheritedChildren, NodeDesign::References_optional *inheritedReferences)
{
    //TODO: Add a logic to check for cyclic BaseType where a parent inherits a Child.
    //      Store baseType in a map, if key is there already then we terminate recursion and show message

    this->panelNode->CopyParent(type, inheritedChildren, inheritedReferences);

    //Get the BaseType and search the actual object
    wxString baseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(type->BaseType(), "BaseObjectType");

    //Recursion will stop at the BaseObjectType
    if (baseType.Cmp("BaseObjectType") == 0)
        return;


    TypeDesign *parentType = 0;

    //Search from ObjectType
    for (ModelDesign::ObjectType_iterator i (this->m_model->ObjectType().begin());
         i != this->m_model->ObjectType().end ();
         ++i)
    {
        wxString symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //Find the ObjectType that the Object has typedef'd from.
        if (0 == symName.compare(baseType))
        {
            parentType = &(*i);
            break;
        }
    }

    //TODO: Continue searching with the rest of the model element type if parentType is not null.

    //Search from VariableType

    //Search from PropertyType

    //Search from DataType

    //Search from ReferenceType?


    if (parentType != 0)
        this->CopyParent(parentType, inheritedChildren, inheritedReferences);
}
