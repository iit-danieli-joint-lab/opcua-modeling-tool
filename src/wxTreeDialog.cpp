#include "opcutils.h"
#include "wxTreeDialog.h"
#include "modelTree.h"

#include <wx/log.h>

//(*InternalHeaders(wxTreeDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxTreeDialog)
const long wxTreeDialog::ID_TREECTRL1 = wxNewId();
const long wxTreeDialog::ID_BUTTON1 = wxNewId();
const long wxTreeDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxTreeDialog,wxDialog)
	//(*EventTable(wxTreeDialog)
	//*)
END_EVENT_TABLE()

using namespace std;

wxTreeDialog::wxTreeDialog(wxWindow* parent, ModelDesign* model,
                           bool showChildren, bool showReferences,
                           int showRootMask, wxWindowID id,const wxPoint& pos,const wxSize& size)
                           : m_model(model), m_selectedNode(0)
{
	//(*Initialize(wxTreeDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Lookup"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	treeOPCCtrl = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxSize(229,421), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	BoxSizer1->Add(treeOPCCtrl, 1, wxALL|wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	btnOK = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxTreeDialog::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxTreeDialog::OnbtnCancelClick);
	//*)

    treeOPCCtrl->SetWindowStyle(wxTR_HIDE_ROOT); //Hides the real root node to have many virtual roots
    treeOPCCtrl->AssignImageList(OPCUtils::GetCommonImageList());

    ModelTree modelTree(treeOPCCtrl);
    modelTree.CreateTree(m_model, showChildren, showReferences, 0, showRootMask);
}

wxTreeDialog::~wxTreeDialog()
{
	//(*Destroy(wxTreeDialog)
	//*)
}

void wxTreeDialog::OnbtnCancelClick(wxCommandEvent& event)
{
    this->EndModal(-1);
}

void wxTreeDialog::OnbtnOKClick(wxCommandEvent& event)
{
    wxTreeItemId nodeSelected = this->treeOPCCtrl->GetSelection();
    if (nodeSelected.IsOk())
    {
        wxTreeItemData *data       = treeOPCCtrl->GetItemData(nodeSelected);
        OPCItemData<void> *pvData  = reinterpret_cast<OPCItemData<void> *>(data);

        std::string nodeType = "";
        switch(pvData->NodeType)
        {
            case NodeTypeDataType:
                nodeType = "DataType";
                break;
            case NodeTypeObject:
            case NodeTypeChildObject:
                nodeType = "Object";
                break;
            case NodeTypeObjectType:
                nodeType = "ObjectType";
                break;
            case NodeTypeChildProperty:
                nodeType = "Property";
                break;
            case NodeTypeChildVariable:
                nodeType = "Variable";
                break;
            case NodeTypeVariableType:
                nodeType = "VariableType";
                break;
            case NodeTypeMethod:
            case NodeTypeChildMethod:
                nodeType = "Method";
                break;
            case NodeTypeReference:
                nodeType = "Reference";
                break;
            case NodeTypeReferenceType:
                nodeType = "ReferenceType";
                break;
            default:
                //TODO: Add all case types.
                cerr << "switch default - This is a bug! case: " << pvData->NodeType << " not handled.\n";
                break;
        }

        if (nodeType.compare("") != 0)
        {
            OPCItemData<NodeDesign> *pvElement  = reinterpret_cast<OPCItemData<NodeDesign> *>(data);
            this->SelectedSymbolicName          = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pvElement->Element->SymbolicName());
            this->SelectedNamespace             = pvElement->Element->SymbolicName()->namespace_();
            this->m_selectedNode                = *pvElement->Element;

            string bufferTargetId;
            this->SelectedStringId              = OPCUtils::GetTargetId(nodeSelected, bufferTargetId, treeOPCCtrl);
            this->EndModal(0);
            return;
        }
    }

    this->EndModal(-1);
}



NodeDesign* wxTreeDialog::GetSelectedNode()
{
    return this->m_selectedNode;
}
