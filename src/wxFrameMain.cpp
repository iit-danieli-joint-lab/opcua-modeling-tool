#include "wxFrameMain.h"

#include "wxPanelInstance.h"
#include "wxPanelObjectType.h"
#include "wxPanelInstance.h"
#include "wxPanelType.h"
#include "wxPanelStructDataType.h"
#include "wxPanelEnumDataType.h"
#include "wxPanelVariableType.h"
#include "wxPanelVariable.h"
#include "wxPanelNode.h"
#include "wxPanelReferenceType.h"
#include "wxPanelReference.h"
#include "wxPanelMethod.h"
#include "wxProjectDialog.h"
#include "wxProjectGitDialog.h"
#include "wxAbout.h"
#include "wxCompileDialog.h"
#include "wxConfig.h"
#include "wxLogin.h"
#include "synthesis/opc.hxx"
#include "opcitemdata.hxx"
#include "opcelement.hxx"
#include "opcglobal.h"
#include "opcutils.h"
#include "opcimporter.h"
#include "modelTree.h"
#include "simpleJSON/JSON.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <time.h>
#include <string>
#include <sys/stat.h>

#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/log.h>
#include <wx/scrolwin.h>
#include <wx/generic/textdlgg.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/uri.h>
#include <wx/base64.h>
//#include <xercesc/dom/DOM.hpp>
//using namespace xercesc;

using namespace std;



//(*InternalHeaders(wxFrameMain)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(wxFrameMain)
const long wxFrameMain::ID_TREEOPC_ID = wxNewId();
const long wxFrameMain::ID_PANEL_HEADER_OBJ_TYPE = wxNewId();
const long wxFrameMain::ID_PANEL_HEADER_VAR_TYPE = wxNewId();
const long wxFrameMain::ID_PANEL_HEADER_EMPTY = wxNewId();
const long wxFrameMain::ID_CUSTOM1 = wxNewId();
const long wxFrameMain::ID_CUSTOM2 = wxNewId();
const long wxFrameMain::ID_CUSTOM3 = wxNewId();
const long wxFrameMain::ID_PNL_METHOD = wxNewId();
const long wxFrameMain::ID_CUSTOM4 = wxNewId();
const long wxFrameMain::ID_CUSTOM5 = wxNewId();
const long wxFrameMain::ID_CUSTOM6 = wxNewId();
const long wxFrameMain::ID_CUSTOM7 = wxNewId();
const long wxFrameMain::ID_BUTTON_UPDATE = wxNewId();
const long wxFrameMain::ID_PANEL_DETAIL_FOOTER = wxNewId();
const long wxFrameMain::ID_PANEL_MAIN = wxNewId();
const long wxFrameMain::ID_MENUITEM_NEW = wxNewId();
const long wxFrameMain::ID_MENUITEM3 = wxNewId();
const long wxFrameMain::ID_MENUSAVE = wxNewId();
const long wxFrameMain::ID_MENUITEM2 = wxNewId();
const long wxFrameMain::ID_MENUITEM1 = wxNewId();
const long wxFrameMain::ID_MENUITEM8 = wxNewId();
const long wxFrameMain::ID_MENUITEM11 = wxNewId();
const long wxFrameMain::ID_MENUITEM10 = wxNewId();
const long wxFrameMain::ID_MENUITEM7 = wxNewId();
const long wxFrameMain::ID_MENUITEM4 = wxNewId();
const long wxFrameMain::ID_MENUITEM5 = wxNewId();
const long wxFrameMain::ID_MENUITEM6 = wxNewId();
const long wxFrameMain::ID_MENU_ABOUT = wxNewId();
const long wxFrameMain::ID_STATUSBAR_MAIN = wxNewId();
const long wxFrameMain::ID_TOOLBARITEM3 = wxNewId();
const long wxFrameMain::ID_TOOLBARITEM1 = wxNewId();
const long wxFrameMain::ID_TOOLBARITEM2 = wxNewId();
const long wxFrameMain::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxFrameMain,wxFrame)
	//(*EventTable(wxFrameMain)
	//*)
END_EVENT_TABLE()

wxFrameMain::wxFrameMain(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
                        : m_model(0), m_modelTree(0), m_projectName(""), m_projectURI(""), m_projectFile("")
{
	//(*Initialize(wxFrameMain)
	wxBoxSizer* boxSizerHeaderInstance;
	wxBoxSizer* boxSizerHeaderType;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* boxSizerHeaderMethod;
	wxBoxSizer* boxSizerHeaderEnumDataType;
	wxBoxSizer* boxSizerHeaderObjectType;
	wxBoxSizer* boxSizerMain;
	wxBoxSizer* boxSizerHeaderVariable;
	wxBoxSizer* boxSizerHeaderReference;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* boxSizerDetail;
	wxBoxSizer* boxSizerHeaderReferenceType;
	wxBoxSizer* boxSizerTree;
	wxBoxSizer* boxSizerPanelMain;
	wxBoxSizer* boxSizerHeaderVariableType;
	wxBoxSizer* boxSizerFooter;
	wxBoxSizer* boxSizerHeaderEmpty;
	wxBoxSizer* boxSizerHeader;
	wxBoxSizer* boxSizerDetailFooter;
	wxBoxSizer* boxSizerHeaderStructDataType;

	Create(parent, wxID_ANY, _("UA Model eXcelerator"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(1000,600));
	boxSizerMain = new wxBoxSizer(wxHORIZONTAL);
	boxSizerTree = new wxBoxSizer(wxHORIZONTAL);
	panelMain = new wxScrolledWindow(this, ID_PANEL_MAIN, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL_MAIN"));
	boxSizerPanelMain = new wxBoxSizer(wxHORIZONTAL);
	treeOPCCtrl = new wxTreeCtrl(panelMain, ID_TREEOPC_ID, wxDefaultPosition, wxSize(376,400), wxTR_DEFAULT_STYLE|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, _T("ID_TREEOPC_ID"));
	treeOPCCtrl->SetMinSize(wxSize(400,300));
	boxSizerPanelMain->Add(treeOPCCtrl, 0, wxEXPAND, 0);
	boxSizerDetail = new wxBoxSizer(wxVERTICAL);
	boxSizerHeader = new wxBoxSizer(wxHORIZONTAL);
	boxSizerHeaderObjectType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderObjectType = new wxPanelObjectType(panelMain,ID_PANEL_HEADER_OBJ_TYPE);
	boxSizerHeaderObjectType->Add(pnlHeaderObjectType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderObjectType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderVariableType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderVariableType = new wxPanelVariableType(panelMain,ID_PANEL_HEADER_VAR_TYPE);
	boxSizerHeaderVariableType->Add(pnlHeaderVariableType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderVariableType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderEmpty = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderEmpty = new wxPanel(panelMain, ID_PANEL_HEADER_EMPTY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL_HEADER_EMPTY"));
	pnlHeaderEmpty->Hide();
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlHeaderEmpty->SetSizer(BoxSizer1);
	BoxSizer1->Fit(pnlHeaderEmpty);
	BoxSizer1->SetSizeHints(pnlHeaderEmpty);
	boxSizerHeaderEmpty->Add(pnlHeaderEmpty, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderEmpty, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderReferenceType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderReferenceType = new wxPanelReferenceType(panelMain,ID_CUSTOM1);
	boxSizerHeaderReferenceType->Add(pnlHeaderReferenceType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderReferenceType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderInstance = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderInstance = new wxPanelInstance(panelMain,ID_CUSTOM2);
	boxSizerHeaderInstance->Add(pnlHeaderInstance, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderInstance, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderReference = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderReference = new wxPanelReference(panelMain,ID_CUSTOM3);
	boxSizerHeaderReference->Add(pnlHeaderReference, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderReference, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderMethod = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderMethod = new wxPanelMethod(panelMain,ID_PNL_METHOD);
	boxSizerHeaderMethod->Add(pnlHeaderMethod, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderMethod, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderType = new wxPanelType(panelMain,ID_CUSTOM4);
	boxSizerHeaderType->Add(pnlHeaderType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderEnumDataType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderEnumDataType = new wxPanelEnumDataType(panelMain,ID_CUSTOM5);
	boxSizerHeaderEnumDataType->Add(pnlHeaderEnumDataType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderEnumDataType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderStructDataType = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderStructDataType = new wxPanelStructDataType(panelMain,ID_CUSTOM6);
	boxSizerHeaderStructDataType->Add(pnlHeaderStructDataType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderStructDataType, 1, wxALL|wxEXPAND, 5);
	boxSizerHeaderVariable = new wxBoxSizer(wxHORIZONTAL);
	pnlHeaderVariable = new wxPanelVariable(panelMain,ID_CUSTOM7);
	boxSizerHeaderVariable->Add(pnlHeaderVariable, 1, wxALL|wxEXPAND, 5);
	boxSizerHeader->Add(boxSizerHeaderVariable, 1, wxALL|wxEXPAND, 5);
	boxSizerDetail->Add(boxSizerHeader, 1, wxALL|wxEXPAND, 5);
	boxSizerDetailFooter = new wxBoxSizer(wxHORIZONTAL);
	pnlDetailFooter = new wxPanel(panelMain, ID_PANEL_DETAIL_FOOTER, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_DETAIL_FOOTER"));
	pnlDetailFooter->Hide();
	boxSizerFooter = new wxBoxSizer(wxHORIZONTAL);
	btnUpdate = new wxButton(pnlDetailFooter, ID_BUTTON_UPDATE, _("Update"), wxDefaultPosition, wxSize(-1,23), 0, wxDefaultValidator, _T("ID_BUTTON_UPDATE"));
	btnUpdate->SetMinSize(wxSize(-1,23));
	btnUpdate->SetMaxSize(wxSize(-1,23));
	boxSizerFooter->Add(btnUpdate, 1, wxALL|wxEXPAND, 5);
	pnlDetailFooter->SetSizer(boxSizerFooter);
	boxSizerFooter->Fit(pnlDetailFooter);
	boxSizerFooter->SetSizeHints(pnlDetailFooter);
	boxSizerDetailFooter->Add(pnlDetailFooter, 1, wxALL|wxEXPAND, 5);
	boxSizerDetail->Add(boxSizerDetailFooter, 0, wxALL|wxEXPAND, 5);
	boxSizerPanelMain->Add(boxSizerDetail, 1, wxALL|wxEXPAND, 5);
	panelMain->SetSizer(boxSizerPanelMain);
	boxSizerPanelMain->Fit(panelMain);
	boxSizerPanelMain->SetSizeHints(panelMain);
	boxSizerTree->Add(panelMain, 1, wxALL|wxEXPAND, 5);
	boxSizerMain->Add(boxSizerTree, 1, wxALL|wxEXPAND, 5);
	SetSizer(boxSizerMain);
	menuBarMain = new wxMenuBar();
	menuFile = new wxMenu();
	menuNew = new wxMenuItem(menuFile, ID_MENUITEM_NEW, _("&New\tCtrl-N"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuNew);
	menuOpen = new wxMenuItem(menuFile, ID_MENUITEM3, _("&Open\tCtrl-O"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuOpen);
	menuSave = new wxMenuItem(menuFile, ID_MENUSAVE, _("&Save\tCtrl-S"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuSave);
	menuSaveAs = new wxMenuItem(menuFile, ID_MENUITEM2, _("Save &As\tCtrl-A"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuSaveAs);
	menuFile->AppendSeparator();
	menuImport = new wxMenuItem(menuFile, ID_MENUITEM1, _("&Import\tCtrl-I"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuImport);
	menuFile->AppendSeparator();
	Menu2 = new wxMenu();
	mnuNewGithub = new wxMenuItem(Menu2, ID_MENUITEM8, _("New\tCtrl-W"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(mnuNewGithub);
	mnuOpenGithub = new wxMenuItem(Menu2, ID_MENUITEM11, _("Open\tCtrl-P"), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(mnuOpenGithub);
	menuFile->Append(ID_MENUITEM10, _("Github"), Menu2, wxEmptyString);
	menuFile->AppendSeparator();
	mnuConfig = new wxMenuItem(menuFile, ID_MENUITEM7, _("Config"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(mnuConfig);
	menuFile->AppendSeparator();
	menuExit = new wxMenuItem(menuFile, ID_MENUITEM4, _("E&xit\tCtrl-X"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuExit);
	menuBarMain->Append(menuFile, _("File"));
	Menu1 = new wxMenu();
	menuSettings = new wxMenuItem(Menu1, ID_MENUITEM5, _("Project Settings\tCtrl-P"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(menuSettings);
	mnuCompile = new wxMenuItem(Menu1, ID_MENUITEM6, _("Compile\tCtrl-C"), wxEmptyString, wxITEM_NORMAL);
	Menu1->Append(mnuCompile);
	menuBarMain->Append(Menu1, _("Project"));
	menuHelp = new wxMenu();
	mnuAbout = new wxMenuItem(menuHelp, ID_MENU_ABOUT, _("A&bout\tCtrl-B"), wxEmptyString, wxITEM_NORMAL);
	menuHelp->Append(mnuAbout);
	menuBarMain->Append(menuHelp, _("&Help"));
	SetMenuBar(menuBarMain);
	statusBarMain = new wxStatusBar(this, ID_STATUSBAR_MAIN, 0, _T("ID_STATUSBAR_MAIN"));
	int __wxStatusBarWidths_1[1] = { -10 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	statusBarMain->SetFieldsCount(1,__wxStatusBarWidths_1);
	statusBarMain->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(statusBarMain);
	toolbar = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	toolbar->AddSeparator();
	tbOpen = toolbar->AddTool(ID_TOOLBARITEM3, _("Open"), wxBitmap(wxImage(_T("icons/open.png"))), wxBitmap(wxImage(_T("icons/open.png"))), wxITEM_NORMAL, _("Open UMX Model"), wxEmptyString);
	tbSave = toolbar->AddTool(ID_TOOLBARITEM1, _("Save"), wxBitmap(wxImage(_T("icons/Save-icon.png"))), wxNullBitmap, wxITEM_NORMAL, _("Save UMX Model"), wxEmptyString);
	toolbar->AddSeparator();
	tbCompile = toolbar->AddTool(ID_TOOLBARITEM2, _("Compile"), wxBitmap(wxImage(_T("icons/gear-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Compile Model"), wxEmptyString);
	toolbar->Realize();
	SetToolBar(toolbar);
	SetSizer(boxSizerMain);
	Layout();

	Connect(ID_TREEOPC_ID,wxEVT_COMMAND_TREE_ITEM_ACTIVATED,(wxObjectEventFunction)&wxFrameMain::OntreeOPCCtrlItemActivated);
	Connect(ID_TREEOPC_ID,wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&wxFrameMain::OntreeOPCCtrlItemRightClick);
	Connect(ID_TREEOPC_ID,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&wxFrameMain::OntreeOPCCtrlSelectionChanged);
	Connect(ID_BUTTON_UPDATE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxFrameMain::OnbtnUpdateClick);
	Connect(ID_MENUITEM_NEW,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuNewSelected);
	Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuOpenSelected);
	Connect(ID_MENUSAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuSaveSelected);
	Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuSaveAsSelected);
	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuImportSelected);
	Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmnuNewGithubSelected);
	Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmnuOpenGithubSelected);
	Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmnuConfigSelected);
	Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuExitSelected);
	Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmenuSettingsSelected);
	Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmnuCompileSelected);
	Connect(ID_MENU_ABOUT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxFrameMain::OnmnuAboutSelected);
	Connect(ID_TOOLBARITEM3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxFrameMain::OntbOpenClicked);
	Connect(ID_TOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxFrameMain::OntbSaveClicked);
	Connect(ID_TOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxFrameMain::OntbCompileClicked);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wxFrameMain::OnClose);
	//*)

    //We need to reference with a member variable to make these accessible, declaring from the
    //outside of the generated code of wxSmith so that it will not be overwritten.
    m_boxSizerHeaderObjectType      = boxSizerHeaderObjectType;
    m_boxSizerHeaderVariableType    = boxSizerHeaderVariableType;
    m_boxSizerHeaderVariable        = boxSizerHeaderVariable;
    m_boxSizerHeaderEmpty           = boxSizerHeaderEmpty;
    m_boxSizerHeaderReferenceType   = boxSizerHeaderReferenceType;
    m_boxSizerHeaderReference       = boxSizerHeaderReference;
    m_boxSizerHeaderInstance        = boxSizerHeaderInstance;
    m_boxSizerHeaderMethod          = boxSizerHeaderMethod;
    m_boxSizerHeaderType            = boxSizerHeaderType;
    m_boxSizerHeaderStructDataType  = boxSizerHeaderStructDataType;
    m_boxSizerHeaderEnumDataType    = boxSizerHeaderEnumDataType;
    m_boxSizerDetailFooter          = boxSizerDetailFooter;

    m_boxSizerHeader                = boxSizerHeader;
    m_boxSizerMain                  = boxSizerMain;
    m_boxSizerDetail                = boxSizerDetail;
    m_boxSizerPanelMain             = boxSizerPanelMain;

    #ifndef __linux__
        this->treeOPCCtrl->SetWindowStyle(wxTR_HIDE_ROOT); //Hides the real root node to have many virtual roots
    #else
        //TODO:Make sure this is an else if of windows
    #endif // __linux__


    /* Initialize logger */
    #ifdef LOG_FILE
        wxDateTime date = wxDateTime::Today();
        wxString logFileName = wxString::Format("log_%d_%02d.txt", date.GetYear(), date.GetMonth()+1);
        wxFileName fLog(wxStandardPaths::Get().GetTempDir(), logFileName);
        FILE *file = fopen(fLog.GetFullPath().ToAscii(), "a+" ); //TODO: File is being delete every time this opens.
        if (file != 0)
        {
            m_logFile.reset(file);
            delete wxLog::SetActiveTarget(new wxLogStderr(m_logFile.get()));
        }
    #else
        //This will write logs to std err if console is enabled and to dev null if console is disabled. Otherwise it will show in a dialog box.
        delete wxLog::SetActiveTarget(new wxLogStderr(0));
    #endif // LOG_FILE

    wxLog::SetTimestamp("%d/%b/%Y %H:%M:%S");
    wxLogMessage("************************");
    wxLogMessage("eXcelerator Start");
    wxLogMessage("************************");


    /* Initialize schema.
     * Copy xsd file to the temp dir so that we will be sure that there are no spaces in the temp directory.
     * xsi:schemaLocation does not allow spaces for xsd path
     */
    wxFileName fSrc(wxStandardPaths::Get().GetExecutablePath());
    wxFileName fDest(wxStandardPaths::Get().GetTempDir(), "opc_with_namespace.xsd");
    if (!wxCopyFile(wxString::Format("%sopc_with_namespace.xsd", fSrc.GetPathWithSep()),
                    fDest.GetFullPath().ToStdString(),
                    true))
    {
        ::wxMessageBox("Initializing UMX failed.\n"
                       "Could not create opc_with_namespace.xsd in the temp directory.",
                       wxStandardPaths::Get().GetTempDir());
        this->Close();
    }

    this->SetIcon(wxIcon(wxIconLocation("icons/umx.ico")));
    this->treeOPCCtrl->AssignImageList(OPCUtils::GetCommonImageList());
    panelMain->SetScrollRate(5, 5);
    this->Maximize();
    wxBusyCursor cursorSpinning;
    InitUI();
    OpenModel(MODEL_TEMPLATE_FILENAME, false);
    m_xmlNewlyCreated = true;
    m_projectName     = "";
    m_projectURI      = "";
    m_projectFile     = "";
    m_gitProjectType  = false;
    m_dirty           = false;
}

wxFrameMain::~wxFrameMain()
{
	//(*Destroy(wxFrameMain)
	//*)
}

void wxFrameMain::OntreeOPCCtrlItemActivated(wxTreeEvent& event)
{
    OntreeOPCCtrlSelectionChanged(event);
}

void wxFrameMain::OntreeOPCCtrlSelectionChanged(wxTreeEvent& event)
{
    NodeSelected(event.GetItem());
}

void wxFrameMain::NodeSelected(wxTreeItemId selectedItemId)
{
    wxColour nodeColor          = this->treeOPCCtrl->GetItemTextColour(selectedItemId);
    wxTreeItemData *data        = treeOPCCtrl->GetItemData(selectedItemId);
    OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(data);

    InitUI();
    bool userOwner = (OPCUtils::DARK_GRAY != nodeColor);
    this->pnlDetailFooter->Enable(userOwner);

    //Just some specific flags to be able to refactor related types.
    bool childMethod        = false;
    bool childProperty      = false;

    switch(pvData->NodeType)
    {
        case NodeTypeObjectRoot:
        case NodeTypeObjectTypeRoot:
        case NodeTypeVariableTypeRoot:
        {
            //Do nothing.
            break;
        }
        case NodeTypeDataType:
        {
            OPCItemData<DataTypeDesign> *pvElement = dynamic_cast<OPCItemData<DataTypeDesign> *>(data);

            string symName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pvElement->Element->SymbolicName());

            if (OPCUtils::IsSameTypeDefinition(this->m_model.get(), *pvElement->Element, "Enumeration", NodeTypeDataType))
            {
                this->m_boxSizerHeaderEnumDataType->Show(this->pnlHeaderEnumDataType, true);
                this->pnlHeaderEnumDataType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner);
                this->pnlHeaderEnumDataType->PopulateData();
            }
            else if (OPCUtils::IsSameTypeDefinition(this->m_model.get(), *pvElement->Element, "Structure", NodeTypeDataType))
            {
                this->m_boxSizerHeaderStructDataType->Show(this->pnlHeaderStructDataType, true);
                this->pnlHeaderStructDataType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner) ;
                this->pnlHeaderStructDataType->PopulateData();
            }
            else
            {
                this->m_boxSizerHeaderType->Show(this->pnlHeaderType, true);
                this->pnlHeaderType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner);
                this->pnlHeaderType->PopulateData(pvData->NodeType);
            }

            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeObjectType:
        {
            this->m_boxSizerHeaderObjectType->Show(this->pnlHeaderObjectType, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<ObjectTypeDesign> *pvElement = dynamic_cast<OPCItemData<ObjectTypeDesign> *>(data);

            this->pnlHeaderObjectType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner) ;
            this->pnlHeaderObjectType->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeVariableType:
        {
            this->m_boxSizerHeaderVariableType->Show(this->pnlHeaderVariableType, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<VariableTypeDesign> *pvElement = dynamic_cast<OPCItemData<VariableTypeDesign> *>(data);

            VariableTypeDesign * topMostValidParentVariableType = 0;
            this->pnlHeaderVariableType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner, topMostValidParentVariableType);
            this->pnlHeaderVariableType->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeReferenceType:
        {
            this->m_boxSizerHeaderReferenceType->Show(this->pnlHeaderReferenceType, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<ReferenceTypeDesign> *pvElement = dynamic_cast<OPCItemData<ReferenceTypeDesign> *>(data);

            this->pnlHeaderReferenceType->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner);
            this->pnlHeaderReferenceType->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeReference:
        {
            this->m_boxSizerHeaderReference->Show(this->pnlHeaderReference, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<Reference> *pvElement = dynamic_cast<OPCItemData<Reference> *>(data);

            this->pnlHeaderReference->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner);
            this->pnlHeaderReference->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeChildMethod:
            childMethod = true;
        case NodeTypeMethod:
        {
            this->m_boxSizerHeaderMethod->Show(this->pnlHeaderMethod, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<MethodDesign> *pvElement = dynamic_cast<OPCItemData<MethodDesign> *>(data);

            this->pnlHeaderMethod->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner, childMethod);
            this->pnlHeaderMethod->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeChildObject:
        case NodeTypeObject:
        {
            this->m_boxSizerHeaderInstance->Show(this->pnlHeaderInstance, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            OPCItemData<ObjectDesign> *pvElement = dynamic_cast<OPCItemData<ObjectDesign> *>(data);

            this->pnlHeaderInstance->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner, pvData->NodeType);
            this->pnlHeaderInstance->PopulateData(pvData->NodeType);
            //nodeTextUpdateable = true;
            break;
        }
        case NodeTypeChildProperty:    //Property is directly a sublcass of NodeTypeVariable. Both their classes structure have no difference, except for
            childProperty = true;      //their type definition. Property uses DataType while Variable uses VariableType. Same with Object uses ObjectType.
        case NodeTypeChildVariable:
        {
            this->m_boxSizerHeaderVariable->Show(this->pnlHeaderVariable, true);
            this->m_boxSizerDetailFooter->Show(this->pnlDetailFooter, true);

            if (childProperty)
            {
                OPCItemData<PropertyDesign> *pvElement = dynamic_cast<OPCItemData<PropertyDesign> *>(data);
                this->pnlHeaderVariable->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner, pvData->NodeType);
            }
            else
            {
                OPCItemData<VariableDesign> *pvElement = dynamic_cast<OPCItemData<VariableDesign> *>(data);
                this->pnlHeaderVariable->Init(*pvElement->Element, &(*this->m_model), selectedItemId, this, userOwner, pvData->NodeType);
            }

            this->pnlHeaderVariable->PopulateData();
            //nodeTextUpdateable = true;
            break;
        }
        default:
            InitUI();
            cerr << "switch default - This is a bug! case: " << pvData->NodeType << " not handled.\n";
            break;
    }

    /* We don't need to update the node since we make sure that node add/delete/update must all re-create the tree.
    //Refresh node text just in case something occur prior to this like node deleted or update.
    if (nodeTextUpdateable)
    {
        if (pvData->NodeType == NodeTypeReference)
        {
            OPCItemData<Reference> *pvElement = dynamic_cast<OPCItemData<Reference> *>(data);
            string sTargetId = OPCUtils::GetStringFromQName(pvElement->Element->TargetId());
            this->treeOPCCtrl->SetItemText(selectedItemId, sTargetId);
        }
        else
        {
            OPCItemData<NodeDesign> *pvElement = reinterpret_cast<OPCItemData<NodeDesign> *>(data);
            string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pvElement->Element->SymbolicName());
            this->treeOPCCtrl->SetItemText(selectedItemId, symName);
        }
    }
    */

    this->m_boxSizerHeader->Layout();
    this->m_boxSizerDetail->Layout();
    this->m_boxSizerMain->Layout();
}

void wxFrameMain::OnPopupMenuNode(wxCommandEvent &evt)
{
    switch(evt.GetId())
    {
        case MenuPopup_ID_ADD:
        {
            OnPopupMenuAddNode(evt);
            break;
        }
        case MenuPopup_ID_DEL:
        {
            OnPopupMenuDeleteNode(evt);
            break;
        }
        case MenuPopup_ID_GOTO_NODE:
        {
            OnPopupMenuGotoNode(evt);
            break;
        }
    }
}

bool wxFrameMain::SearchName(NodeDesign *node, std::string refTargetId, std::queue<std::string> symNames)
{
    bool treeNodeFound = false;

    string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(node->SymbolicName());
    if (refTargetId.compare(symName) == 0)
    {
        if (symNames.size() == 0)
            treeNodeFound = SearchNodeInTree(this->treeOPCCtrl->GetRootItem(), node);
        else
        {
            NodeDesign *nodeChildFound = FindChildren(node, symNames);
            if (nodeChildFound != 0)
                treeNodeFound = SearchNodeInTree(this->treeOPCCtrl->GetRootItem(), nodeChildFound);
        }
    }

    return treeNodeFound;
}

void wxFrameMain::OnPopupMenuGotoNode(wxCommandEvent &evt)
{
    void *selectedData = (static_cast<wxMenu *>(evt.GetEventObject()))->GetClientData();
    OPCItemData<Reference> *pvSelectedData = reinterpret_cast<OPCItemData<Reference> *>(selectedData);


    //ReferenceType which is the symbolic name of a Reference Type. But what is the relevance of this? For something else
    //but not for navigation


    //Find the node of the reference target Id
    string ssRefFullName = OPCUtils::GetStringFromQName(pvSelectedData->Element->TargetId());

    //This should not happen
    if (ssRefFullName.compare(NO_VALUE) == 0)
        return;

    //Tokenize underscore
    queue <string> symNames;
    char *p = strtok(strdup(ssRefFullName.c_str()), "_");
    while (p) {
        symNames.push(p);
        p = strtok(NULL, "_");
    }
    if (symNames.size() == 0)
        symNames.push(ssRefFullName);

    //Search the actual object of the targetId, and use it to search the tree node.
    bool treeNodeFound   = false;

    string refTargetId = symNames.front();
    symNames.pop();

    ITERATE_MODELLIST(Object, i, m_model)
    {
        treeNodeFound = SearchName(&(*i), refTargetId, symNames);
        if (treeNodeFound)
            break;
    }

    //Try again without tokenizing. Name may have underscore
    queue <string> emptySymNames;
    if (!treeNodeFound)
        ITERATE_MODELLIST(Object, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
        ITERATE_MODELLIST(ObjectType, i, m_model)
        {
            queue <string> dupSymNames = symNames;
            treeNodeFound = SearchName(&(*i), refTargetId, symNames);
            if (treeNodeFound)
                break;
        }

    //Try again without tokenizing. Name may have underscore
    if (!treeNodeFound)
        ITERATE_MODELLIST(ObjectType, i, m_model)
        {
            queue <string> dupSymNames = symNames;
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
        ITERATE_MODELLIST(Variable, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), refTargetId, symNames);
            if (treeNodeFound)
                break;
        }

    //Try again without tokenizing. Name may have underscore
    if (!treeNodeFound)
        ITERATE_MODELLIST(Variable, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
        ITERATE_MODELLIST(VariableType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), refTargetId, symNames);
            if (treeNodeFound)
                break;
        }

    //Try again without tokenizing. Name may have underscore
    if (!treeNodeFound)
        ITERATE_MODELLIST(VariableType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
        ITERATE_MODELLIST(DataType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), refTargetId, symNames);
            if (treeNodeFound)
                break;
        }

    //Try again without tokenizing. Name may have underscore
    if (!treeNodeFound)
        ITERATE_MODELLIST(DataType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
        ITERATE_MODELLIST(ReferenceType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), refTargetId, symNames);
            if (treeNodeFound)
                break;
        }

    //Try again without tokenizing. Name may have underscore
    if (!treeNodeFound)
        ITERATE_MODELLIST(ReferenceType, i, m_model)
        {
            treeNodeFound = SearchName(&(*i), ssRefFullName, emptySymNames);
            if (treeNodeFound)
                break;
        }

    if (!treeNodeFound)
    {
        ::wxMessageBox("Node Referenced Not Found", "Go to Target Node");
        treeOPCCtrl->SelectItem(pvSelectedData->ItemId); //Return focus back to the node where we right clicked since Go To Reference failed.
        treeOPCCtrl->ScrollTo(pvSelectedData->ItemId);
    }
}

NodeDesign * wxFrameMain::FindChildren(NodeDesign *node, queue<std::string> symNames)
{
    if(node->Children() == 0)
        return 0;

    NodeDesign *nodeFound = 0;

    string refId = symNames.front();
    symNames.pop();

    //Object
    ITERATE_CHILDREN(Object, node, i)
    {
        string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
        if (symName.compare(refId) == 0)
        {
            if (symNames.size() == 0)
                return &(*i);
            else
            {
                nodeFound = FindChildren(&(*i), symNames);
                if (nodeFound != 0)
                    return nodeFound;
            }
        }
    }

    //Variable
    ITERATE_CHILDREN(Variable, node, i)
    {
        string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
        if (symName.compare(refId) == 0)
        {
            if (symNames.size() == 0)
                return &(*i);
            else
            {
                nodeFound = FindChildren(&(*i), symNames);
                if (nodeFound != 0)
                    return nodeFound;
            }
        }
    }

    //Property
    ITERATE_CHILDREN(Property, node, i)
    {
        string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
        if (symName.compare(refId) == 0)
        {
            if (symNames.size() == 0)
                return &(*i);
            else
            {
                nodeFound = FindChildren(&(*i), symNames);
                if (nodeFound != 0)
                    return nodeFound;
            }
        }
    }

    //Method
    ITERATE_CHILDREN(Method, node, i)
    {
        string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
        if (symName.compare(refId) == 0)
        {
            if (symNames.size() == 0)
                return &(*i);
            else
            {
                nodeFound = FindChildren(&(*i), symNames);
                if (nodeFound != 0)
                    return nodeFound;
            }
        }
    }

    return 0;
}

bool wxFrameMain::SearchNodeInTree(const wxTreeItemId &itemId, NodeDesign *nodeToSearch)
{
    if (this->treeOPCCtrl->HasChildren(itemId))
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId childId = this->treeOPCCtrl->GetFirstChild(itemId, cookie);

        while (childId.IsOk())
        {
            wxTreeItemData *data        = treeOPCCtrl->GetItemData(childId);
            OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(data);

            /* N.B:  We need to check if a node has no item data set because in
                     Issue 73: https://beeonddev.visualstudio.com/UMX/_workitems?id=73&_a=edit
                     , it crashed when right clicking "Go To Reference Node" of a reference node.
                     This happened because Microsoft BoilerDesign.xml's virtual roots(DataType,
                     EventType, ReferenceType) does not exist in the xml.
                     So any traversal of the tree should check for null item data on each node.
            */
            if (    pvData !=0
                && *pvData->Element != 0)
            {
                if (nodeToSearch == *pvData->Element)
                {
                    treeOPCCtrl->SelectItem(childId);
                    treeOPCCtrl->ScrollTo(childId);
                    return true;  //Stop searching, found it.
                }
            }

            //Recursively search the children
            if (this->treeOPCCtrl->HasChildren(childId))
                if (SearchNodeInTree(childId, nodeToSearch))
                    return true; //Stop searching, found from the subtree.

            childId = this->treeOPCCtrl->GetNextChild(itemId, cookie);
        }
    }

    return false;
}

void wxFrameMain::OnPopupMenuDeleteNode(wxCommandEvent &evt)
{
    void *data                  = (static_cast<wxMenu *>(evt.GetEventObject()))->GetClientData();
    OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(data);

    //If we re-create the tree, we have to retrieve the nearest(previous sibling, next sibling, parent node)
    //node to focus after deletion is done
    wxTreeItemId nearestNode    = this->treeOPCCtrl->GetPrevSibling(pvData->ItemId);
    if (!nearestNode.IsOk())
        nearestNode = this->treeOPCCtrl->GetNextSibling(pvData->ItemId);
    if (!nearestNode.IsOk())
        nearestNode = this->treeOPCCtrl->GetItemParent(pvData->ItemId);
    wxTreeItemData *nearestNodeData  = treeOPCCtrl->GetItemData(nearestNode);
    OPCItemData<void> *pvNearestData = reinterpret_cast<OPCItemData<void> *>(nearestNodeData);

    //We pass a list to store all the wxTreeItemId that needs to be deleted
    //so that we don't have to recreate the whole tree which clears the current tree state.
    //TODO: We will have to remove this vector that we pass to the DeleteNode if we will finalize
    //      that everytime a node is added/deleted/updated, we make it consistent to re-create the tree.
    vector<wxTreeItemId> nodeItemIdList;

    if (DeleteNode(pvData, true, nodeItemIdList))
    {
        /* Strategy 1: Delete the node one by one but make sure to update the node text on click
         //No need to re-create tree since we are deleting node one by one.
        for (vector<wxTreeItemId>::iterator it = nodeItemIdList.begin() ; it != nodeItemIdList.end(); ++it)
        {
            //cout << "List node to delete :" << this->treeOPCCtrl->GetItemText(*it) << "\n";
            this->treeOPCCtrl->Delete(*it);
        }
        */

        //Strategy 2: Recreate the tree
        m_modelTree->CreateTree(this->m_model.get(), true, true, *pvNearestData->Element);
        treeOPCCtrl->SelectItem(m_modelTree->GetLastSelectedItem());
        treeOPCCtrl->ScrollTo(m_modelTree->GetLastSelectedItem());
        this->m_dirty = true;
    }
}


bool wxFrameMain::DeleteNode(OPCItemData<void> *pvData, bool showConfirmation, vector<wxTreeItemId> &nodeItemIdList)
{
    wxTreeItemId selectedItemId   = pvData->ItemId;
    enum NodeType nodeTypeDeleted = pvData->NodeType;

    //TODO: This should be polymorphic. The only problem is that, we will have to duplicate the code synthesis generated classes
    //      to avoid making changes on it.

    if (showConfirmation)
    {
        wxMessageDialog yesNoDiag(this, "Are you sure you want to delete this node?", "Confirm Delete", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
            return false;
    }

    wxString deleteMsg;
    bool deleted = false;

    string bufferTargetId;
    string prevTargetId  = OPCUtils::GetTargetId(selectedItemId, bufferTargetId, this->treeOPCCtrl);
    string prevSymName   = this->treeOPCCtrl->GetItemText(selectedItemId).ToStdString();

    wxLogMessage("Delete Start - Node Text:%s", prevSymName);
    wxLogMessage("Delete Node Type:%s", OPCUtils::NodeTypeToString(pvData->NodeType));

    switch(pvData->NodeType)
    {
        case NodeTypeObjectType:
            {
                OPCItemData<ObjectTypeDesign> *pNode = reinterpret_cast<OPCItemData<ObjectTypeDesign> *>(pvData);
                deleteMsg = wxString::Format("ObjectType %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(ObjectType, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->ObjectType().erase(i);
                        deleted = true;
                        break;
                    }
                }

                break;
            }
        case NodeTypeVariableType:
            {
                OPCItemData<VariableTypeDesign> *pNode = reinterpret_cast<OPCItemData<VariableTypeDesign> *>(pvData);
                deleteMsg = wxString::Format("VariableType %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(VariableType, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->VariableType().erase(i);
                        deleted = true;
                        break;
                    }
                }

                break;
            }
        case NodeTypeDataType:
            {
                OPCItemData<DataTypeDesign> *pNode = reinterpret_cast<OPCItemData<DataTypeDesign> *>(pvData);
                deleteMsg = wxString::Format("DataType %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(DataType, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->DataType().erase(i);
                        deleted = true;
                        break;
                    }
                }

                break;
            }
        case NodeTypeReferenceType:
            {
                OPCItemData<ReferenceTypeDesign> *pNode = reinterpret_cast<OPCItemData<ReferenceTypeDesign> *>(pvData);
                deleteMsg = wxString::Format("ReferenceType %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(ReferenceType, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->ReferenceType().erase(i);
                        deleted = true;
                        break;
                    }
                }

                break;
            }
        case NodeTypeObject:
            {
                OPCItemData<ObjectDesign> *pNode = reinterpret_cast<OPCItemData<ObjectDesign> *>(pvData);
                deleteMsg = wxString::Format("Object %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(Object, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->Object().erase(i);
                        deleted = true;
                        break;
                    }
                }
                break;
            }
        case NodeTypeMethod:
            {
                OPCItemData<MethodDesign> *pNode = reinterpret_cast<OPCItemData<MethodDesign> *>(pvData);
                deleteMsg = wxString::Format("Method %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                ITERATE_MODELLIST(Method, i, m_model)
                {
                    //We can only delete using the iterator. So we have to iterate and find the item to delete.
                    if (*pNode->Element == &(*i))
                    {
                        m_model->Method().erase(i);
                        deleted = true;
                        break;
                    }
                }
                break;
            }
        case NodeTypeChildObject:
            {
                OPCItemData<ObjectDesign> *pNode = reinterpret_cast<OPCItemData<ObjectDesign> *>(pvData);
                deleteMsg = wxString::Format("Object %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                if (pNode->Data != 0)
                {
                    NodeDesign* parentNode = reinterpret_cast<NodeDesign*>(pNode->Data);
                    ITERATE_CHILDREN(Object, parentNode, i)
                    {
                        //We can only delete using the iterator. So we have to iterate and find the item to delete.
                        if (*pNode->Element == &(*i))
                        {
                            parentNode->Children()->Object().erase(i);
                            deleted = true;
                            break;
                        }
                    }
                }
                break;
            }
        case NodeTypeChildVariable:
            {
                OPCItemData<VariableDesign> *pNode = reinterpret_cast<OPCItemData<VariableDesign> *>(pvData);
                deleteMsg = wxString::Format("Variable %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                if (pNode->Data != 0)
                {
                    NodeDesign* parentNode = reinterpret_cast<NodeDesign*>(pNode->Data);
                    ITERATE_CHILDREN(Variable, parentNode, i)
                    {
                        //We can only delete using the iterator. So we have to iterate and find the item to delete.
                        if (*pNode->Element == &(*i))
                        {
                            parentNode->Children()->Variable().erase(i);
                            deleted = true;
                            break;
                        }
                    }
                }
                break;
            }
        case NodeTypeChildProperty:
            {
                OPCItemData<PropertyDesign> *pNode = reinterpret_cast<OPCItemData<PropertyDesign> *>(pvData);
                deleteMsg = wxString::Format("Property %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                if (pNode->Data != 0)
                {
                    NodeDesign* parentNode = reinterpret_cast<NodeDesign*>(pNode->Data);
                    ITERATE_CHILDREN(Property, parentNode, i)
                    {
                        //We can only delete using the iterator. So we have to iterate and find the item to delete.
                        if (*pNode->Element == &(*i))
                        {
                            parentNode->Children()->Property().erase(i);
                            deleted = true;
                            break;
                        }
                    }
                }
                break;
            }
        case NodeTypeChildMethod:
            {
                OPCItemData<MethodDesign> *pNode = reinterpret_cast<OPCItemData<MethodDesign> *>(pvData);
                deleteMsg = wxString::Format("Property %s deleted.", OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName()));

                if (pNode->Data != 0)
                {
                    NodeDesign* parentNode = reinterpret_cast<NodeDesign*>(pNode->Data);
                    ITERATE_CHILDREN(Method, parentNode, i)
                    {
                        //We can only delete using the iterator. So we have to iterate and find the item to delete.
                        if (*pNode->Element == &(*i))
                        {
                            parentNode->Children()->Method().erase(i);
                            deleted = true;
                            break;
                        }
                    }
                }
                break;
            }
        case NodeTypeReference:
            {
                OPCItemData<Reference> *pNode = reinterpret_cast<OPCItemData<Reference> *>(pvData);
                deleteMsg = wxString::Format("Reference %s deleted.", OPCUtils::GetStringFromQName(pNode->Element->TargetId()));

                if (pNode->Data != 0)
                {
                    NodeDesign* parentNode = reinterpret_cast<NodeDesign*>(pNode->Data);
                    ITERATE_REFERENCES(parentNode, i)
                    {
                        //We can only delete using the iterator. So we have to iterate and find the item to delete.
                        if (*pNode->Element == &(*i))
                        {
                            parentNode->References()->Reference().erase(i);
                            deleted = true;
                            break;
                        }
                    }
                }
                break;
            }
        default:
            cerr << "switch default - This is a bug! case: " << pvData->NodeType << " not handled.\n";
            break;
    }

    if (deleted)
    {
        cerr << "deleted prevSymName: " << prevSymName << "\n";
        m_modelTree->PropagateUpdate(prevSymName, "",
                                     prevTargetId, "",
                                     false/*Dummy value*/, nodeTypeDeleted);

        nodeItemIdList.push_back(selectedItemId);

        //Loop all children and delete recursively.
        wxTreeItemIdValue dummyCookie;
        wxTreeItemId child = this->treeOPCCtrl->GetFirstChild(selectedItemId, dummyCookie);
        while (child.IsOk())
        {
            wxTreeItemData *childData      = treeOPCCtrl->GetItemData(child);
            OPCItemData<void> *pvChildData = reinterpret_cast<OPCItemData<void> *>(childData);
            wxLogMessage(" - Delete Child Start");
            DeleteNode(pvChildData, false, nodeItemIdList);
            wxLogMessage(" - Delete Child End");
            child = this->treeOPCCtrl->GetNextChild(child, dummyCookie);
        }

        //this->treeOPCCtrl->Delete(selectedItemId);
        ::wxMessageBox(deleteMsg, _("Delete"));
    }
    wxLogMessage("Delete End - %s", deleteMsg);
    return deleted;
}

void wxFrameMain::OnPopupMenuAddNode(wxCommandEvent &evt)
{
    string newSymbolicName = OPCUtils::GenerateStringId("NewSymbolicName");
    xml_schema::ncname ncSym(newSymbolicName);
    xml_schema::qname qnSym(ncSym);
    NodeDesign::SymbolicName_optional symObj(qnSym);

    void *data                  = (static_cast<wxMenu *>(evt.GetEventObject()))->GetClientData();
    OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(data);

    wxLogMessage("");
    wxLogMessage("Add Start - Node:%s", newSymbolicName);
    wxLogMessage("Add Node Type:%s", OPCUtils::NodeTypeToString(pvData->NodeType));

    //TODO: This should be polymorphic. The only problem is that, we will have to duplicate the code synthesis generated classes
    //      to avoid making changes on it.
    switch(pvData->NodeType)
    {
        case NodeTypeObjectType:
            {
                OPCItemData<ObjectTypeDesign> *parentObjType = reinterpret_cast<OPCItemData<ObjectTypeDesign> *>(pvData);

                ObjectTypeDesign objType;
                objType.SymbolicName(symObj);
                OPCUtils::SetBaseType(objType,
                                      OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentObjType->Element->SymbolicName()),
                                      OPCUtils::IsUserNodeOwner(*parentObjType->Element));
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->ObjectType().insert(m_model->ObjectType().end(), objType) /*End*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeDataType:
            {
                OPCItemData<DataTypeDesign> *parentObjType = reinterpret_cast<OPCItemData<DataTypeDesign> *>(pvData);

                DataTypeDesign dataType;
                dataType.SymbolicName(symObj);
                //dataType.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                OPCUtils::SetBaseType(dataType,
                                      OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentObjType->Element->SymbolicName()),
                                      OPCUtils::IsUserNodeOwner(*parentObjType->Element));
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->DataType().insert(m_model->DataType().end(), dataType) /*End*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeVariableType:
            {
                OPCItemData<VariableTypeDesign> *parentObjType = reinterpret_cast<OPCItemData<VariableTypeDesign> *>(pvData);

                VariableTypeDesign varType;
                varType.SymbolicName(symObj);
                //varType.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                OPCUtils::SetBaseType(varType,
                                      OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentObjType->Element->SymbolicName()),
                                      OPCUtils::IsUserNodeOwner(*parentObjType->Element));

                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->VariableType().insert(m_model->VariableType().end(), varType) /*End*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeReferenceType:
            {
                OPCItemData<ReferenceTypeDesign> *parentObjType = reinterpret_cast<OPCItemData<ReferenceTypeDesign> *>(pvData);

                ReferenceTypeDesign refType;
                refType.SymbolicName(symObj);
                //refType.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                OPCUtils::SetBaseType(refType,
                                      OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentObjType->Element->SymbolicName()),
                                      OPCUtils::IsUserNodeOwner(*parentObjType->Element));
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->ReferenceType().insert(m_model->ReferenceType().end(), refType) /*End*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeObjectRoot:
            {
                ObjectDesign obj;
                obj.SymbolicName(symObj);
                //obj.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->Object().insert(m_model->Object().begin(), obj) /*Front*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeMethodRoot:
            {
                MethodDesign method;
                method.SymbolicName(symObj);
                //method.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(m_model->Method().insert(m_model->Method().begin(), method) /*Front*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeChildrenMethodRoot:
            {
                OPCItemData<NodeDesign> *dataNode = reinterpret_cast<OPCItemData<NodeDesign> *>(pvData);

                if(dataNode->Element->Children() == 0)
                {
                    ListOfChildren childrenList;
                    NodeDesign::Children_optional children(childrenList);
                    dataNode->Element->Children(children);
                }

                MethodDesign method;
                method.SymbolicName(symObj);
                //method.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        &(*(dataNode->Element->Children()->Method().insert(dataNode->Element->Children()->Method().begin(), method) /*Front*/)));
                this->m_dirty = true;
                break;
            }
        case NodeTypeChildrenObjectRoot:
            {
                OPCItemData<NodeDesign> *dataNode = reinterpret_cast<OPCItemData<NodeDesign> *>(pvData);

                if(dataNode->Element->Children() == 0)
                {
                    ListOfChildren childrenList;
                    NodeDesign::Children_optional children(childrenList);
                    dataNode->Element->Children(children);
                }

                ObjectDesign obj;
                obj.SymbolicName(symObj);
                //obj.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.
                OPCUtils::SetTypeDef(obj, "BaseObjectType", false);

                dataNode->Element->Children()->Object().insert(dataNode->Element->Children()->Object().begin(), obj);/*Front*/
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        static_cast<ObjectDesign *>(&dataNode->Element->Children()->Object().front()));
                this->m_dirty = true;
                break;
            }
        case NodeTypeChildrenVariableRoot:
            {
                OPCItemData<NodeDesign> *dataNode = reinterpret_cast<OPCItemData<NodeDesign> *>(pvData);

                if(dataNode->Element->Children() == 0)
                {
                    ListOfChildren childrenList;
                    NodeDesign::Children_optional children(childrenList);
                    dataNode->Element->Children(children);
                }

                VariableDesign var;
                var.SymbolicName(symObj);
                //var.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.
                OPCUtils::SetTypeDef(var, "BaseVariableType", false);

                dataNode->Element->Children()->Variable().insert(dataNode->Element->Children()->Variable().begin(), var);/*Front*/
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        static_cast<VariableDesign *>(&dataNode->Element->Children()->Variable().front()));
                this->m_dirty = true;
                break;
            }
        case NodeTypeChildrenPropertyRoot:
            {
                OPCItemData<NodeDesign> *dataNode = reinterpret_cast<OPCItemData<NodeDesign> *>(pvData);

                if(dataNode->Element->Children() == 0)
                {
                    ListOfChildren childrenList;
                    NodeDesign::Children_optional children(childrenList);
                    dataNode->Element->Children(children);
                }

                PropertyDesign prop;
                prop.SymbolicName(symObj);
                //prop.StringId("node_owner=user"); //N.B: StringId is scalable as we can add more properties separated with a separator character.

                dataNode->Element->Children()->Property().insert(dataNode->Element->Children()->Property().begin(), prop);/*Front*/
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        static_cast<VariableDesign *>(&dataNode->Element->Children()->Property().front()));
                this->m_dirty = true;
                break;
            }
        case NodeTypeReferencesRoot:
            {
                //Get the selected node where we need to add the new reference
                OPCItemData<NodeDesign> *dataNode = reinterpret_cast<OPCItemData<NodeDesign> *>(pvData);

                if(dataNode->Element->References() == 0)
                {
                    ListOfReferences referencesList;
                    NodeDesign::References_optional references(referencesList);
                    dataNode->Element->References(references);
                }

                xml_schema::ncname nc("References");
                xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                Reference::ReferenceType_type refType(qn);
                Reference::TargetId_type targetId("null");
                Reference ref(refType, targetId);

                dataNode->Element->References()->Reference().insert(dataNode->Element->References()->Reference().begin(), ref);
                m_modelTree->CreateTree(this->m_model.get(), true, true,
                                        static_cast<Reference *>(&dataNode->Element->References()->Reference().front()));
                this->m_dirty = true;
                break;
            }

        default:
            cerr << "switch default - This is a bug! case: " << pvData->NodeType << " not handled.\n";
            break;
    }

    //Since we recreate the tree, we can't use the selectedItemId as it does not exist anymore,
    //so we have to use the property from modelTree where it store the last selected item.
    treeOPCCtrl->SelectItem(m_modelTree->GetLastSelectedItem());
    treeOPCCtrl->ScrollTo(m_modelTree->GetLastSelectedItem());
    wxLogMessage("Add End - Node:%s", newSymbolicName);
}


void wxFrameMain::OntreeOPCCtrlItemRightClick(wxTreeEvent& event)
{
    wxTreeItemId selectedItemId = event.GetItem();
    if (!selectedItemId.IsOk())
        return;

    //Retrieve the node data selected.
    wxTreeItemData *selectedData      = treeOPCCtrl->GetItemData(selectedItemId);
    OPCItemData<void> *pvSelectedData = reinterpret_cast<OPCItemData<void> *>(selectedData);

    //Store the selected item so that we can delete/access directly from the tree control
    //without the need of reconstructing the whole tree.
    pvSelectedData->ItemId = selectedItemId;

    //Set the node data to the Popup menu.
    wxMenu treeItemMenu;
    treeItemMenu.SetClientData(selectedData);

    wxColour nodeColor =  this->treeOPCCtrl->GetItemTextColour(selectedItemId);

    switch(pvSelectedData->NodeType)
    {
        case NodeTypeMethodRoot:
        case NodeTypeObjectRoot:
            {
            treeItemMenu.Append(MenuPopup_ID_ADD, "Add");
            treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuAddNode), NULL, this);

            PopupMenu(&treeItemMenu);
            break;
            }

        case NodeTypeReferencesRoot:
        case NodeTypeChildrenObjectRoot:
        case NodeTypeChildrenMethodRoot:
        case NodeTypeChildrenVariableRoot:
        case NodeTypeChildrenPropertyRoot:
            {
            OPCItemData<NodeDesign> *parentNode = dynamic_cast<OPCItemData<NodeDesign> *>(selectedData);
            treeItemMenu.Append(MenuPopup_ID_DEL, "Add")->Enable(OPCUtils::IsUserNodeOwner(*parentNode->Element));
            treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuAddNode), NULL, this);

            PopupMenu(&treeItemMenu);
            break;
            }
        case NodeTypeDataType:
            {
                //We don't allow Adding from indirect descendants of the Enumeration. Direct subtyping only is allowed.
                OPCItemData<DataTypeDesign> *parentNode = dynamic_cast<OPCItemData<DataTypeDesign> *>(selectedData);
                string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentNode->Element->SymbolicName());
                if (   symName.compare("Enumeration") == 0
                    || OPCUtils::IsSameTypeDefinition(this->m_model.get(), *parentNode->Element, "Structure", NodeTypeDataType)
                    || !OPCUtils::IsSameTypeDefinition(this->m_model.get(), *parentNode->Element, "Enumeration", NodeTypeDataType))
                    treeItemMenu.Append(MenuPopup_ID_ADD, "Add");

                treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((OPCUtils::DARK_GRAY != nodeColor));

                treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuNode), NULL, this);

                PopupMenu(&treeItemMenu);
                break;
            }
        case NodeTypeVariableType:
        case NodeTypeObjectType:
            {
                treeItemMenu.Append(MenuPopup_ID_ADD, "Add");
                treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((OPCUtils::DARK_GRAY != nodeColor));

                treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuNode), NULL, this);

                PopupMenu(&treeItemMenu);

                break;
            }
        case NodeTypeReferenceType:
           {
            OPCItemData<ReferenceTypeDesign> *parentNode = dynamic_cast<OPCItemData<ReferenceTypeDesign> *>(selectedData);
            string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(parentNode->Element->SymbolicName());
            if (symName.compare("References") != 0)
            {
                treeItemMenu.Append(MenuPopup_ID_ADD, "Add");
                treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((OPCUtils::DARK_GRAY != nodeColor));

                treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuNode), NULL, this);

                PopupMenu(&treeItemMenu);
            }
            break;
           }
        case NodeTypeObject:
        case NodeTypeMethod:
        case NodeTypeChildObject:
        case NodeTypeChildVariable:
        case NodeTypeChildProperty:
        case NodeTypeChildMethod:
           {
            treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((OPCUtils::DARK_GRAY != nodeColor));
            treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuNode), NULL, this);

            PopupMenu(&treeItemMenu);
            break;
           }
        case NodeTypeReference:
            {
            treeItemMenu.Append(MenuPopup_ID_DEL, "Delete")->Enable((OPCUtils::DARK_GRAY != nodeColor));
            treeItemMenu.Append(MenuPopup_ID_GOTO_NODE, "Go to Target Node");
            treeItemMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxFrameMain::OnPopupMenuNode), NULL, this);

            PopupMenu(&treeItemMenu);
            break;
            }
        default:
            cerr << "switch default - This is a bug! case: " << pvSelectedData->NodeType << " not handled.\n";
            break;
    }
}

bool wxFrameMain::OpenModel(std::string fileName, bool setProjectName/*This is for open/import only*/)
{
    bool successOpen = false;

    try
    {
        //Since the xml can be opened from any directory, xsi:schemaLocation may not be able to point
        //the exact location of the xsd file relative to the executable directory.
        //By forcing to set the property and ignore the value from the xml file, we
        //are assured that the xsd file will be located.
        ::xml_schema::properties p;
        wxFileName filename(wxStandardPaths::Get().GetTempDir(), "opc_with_namespace.xsd");
        p.schema_location("http://opcfoundation.org/UA/ModelDesign.xsd",
                          filename.GetFullPath().ToStdString());


        //Before we reset and overwrite the existing model, we use a temp variable for loading the file
        //to ensure that no exception is thrown.
        auto_ptr<ModelDesign> tempModel = ModelDesign_(fileName, 0, p);
        m_model.reset();
        m_model = tempModel;

        if (   setProjectName
            && this->m_model->Namespaces() != 0)
        {
            m_projectName = "";
            m_projectURI  = "";
            m_projectFile = "";

            for (NamespaceTable::Namespace_iterator i(this->m_model->Namespaces()->Namespace().begin());
                                                      i != this->m_model->Namespaces()->Namespace().end();
                                                      ++i)
            {
                stringstream ssName;
                ssName << i->Name();

                //Read only the project main namespace
                if (   ssName.str() != "OpcUa"
                    && i->FilePath() == 0)
                {
                    stringstream ssXmlPrefixName;
                    if (i->XmlPrefix() != 0)
                    {
                        ssXmlPrefixName << i->XmlPrefix();
                        m_projectName = ssXmlPrefixName.str();
                    }
                    else
                        m_projectName = ssName.str();

                    this->m_projectURI  = *i;

                    this->SetTitle(wxString::Format("UA Model eXcelerator (Project:%s)", m_projectName));
                }
            }
        }

        successOpen = true;

        InitUI();
        treeOPCCtrl->DeleteAllItems();

        this->m_modelTree.reset(new ModelTree(this->treeOPCCtrl));
        this->m_modelTree->CreateTree(m_model.get()); //TODO: we should replace it with shared_ptr to remove get.

        //This will make the scrollbars show up.
        panelMain->FitInside(); //Ask the sizer about the needed sized
    }
    catch(::xsd::cxx::tree::parsing<char> parseException)
    {
        stringstream ss;
        ss << parseException;
        wxString parseMsg = wxString::Format("Parsing xml error: %s.", ss.str());
        ::wxMessageBox(_(parseMsg), _("XML Error"));
        wxLogMessage("Open - Error: %s", parseMsg);
    }

    return successOpen;
}

void wxFrameMain::OnmenuNewSelected(wxCommandEvent& event)
{
    if (this->m_dirty)
    {
        wxMessageDialog yesNoDiag(this, "Changes have not been saved. Proceed?", "Lose Changes", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
            return;
    }

    bool   oldXmlNewlyCreated = m_xmlNewlyCreated;
    string oldProjectName     = m_projectName;
    string oldProjectURI      = m_projectURI;
    string oldProjectFile     = m_projectFile;
    bool   oldGitProjectType  = m_gitProjectType;

    m_xmlNewlyCreated = true;
    m_gitProjectType  = false;
    m_projectName     = "";
    m_projectURI      = "";
    m_projectFile     = "";
    m_dirty           = false;
    m_gitProjectType  = false;
    OpenModel(MODEL_TEMPLATE_FILENAME, false);


    if (!SetProjectSettings())
    {
        m_xmlNewlyCreated = oldXmlNewlyCreated;
        m_projectName     = oldProjectName;
        m_projectURI      = oldProjectURI;
        m_projectFile     = oldProjectFile;
        m_gitProjectType  = oldGitProjectType;
        return;
    }
}

void wxFrameMain::OnmenuOpenSelected(wxCommandEvent& event)
{
    if (this->m_dirty)
    {
        wxMessageDialog yesNoDiag(this, "Changes have not been saved. Proceed?", "Lose Changes", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
            return;
    }

    wxFileDialog openFileDialog(this,
                                _("Open UA XML file"), "", "",
                                _("UA XML files (*.xml)|*.xml"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    this->SetCursor(wxCursor(wxCURSOR_WAIT));

    OPCImporter importer;
    wxString importError;
    if (!importer.MergeUMXToBuiltInTypes(openFileDialog.GetPath().ToStdString().c_str(), importError, m_modelNSInfoMap))
    {
        this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
        ::wxMessageBox(importError);
    }else
    {
        wxLogMessage("");
        wxLogMessage("Open Start - File:%s", openFileDialog.GetPath().ToStdString());
        if (OpenModel(importer.GetMergedFile(), true))
        {
            m_xmlNewlyCreated = false;
            m_projectFile     = openFileDialog.GetPath().ToStdString();
            m_gitProjectType  = false;
            this->m_dirty     = false;
            this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
            ::wxMessageBox(wxString::Format("Successfully opened %s", openFileDialog.GetPath().ToStdString()), "Open");
        }else
        {
            this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
            ::wxMessageBox(wxString::Format("Failed to open %s.", openFileDialog.GetPath().ToStdString()), "Open");
        }
        wxLogMessage("Open - End");
    }
}

void wxFrameMain::OnmenuExitSelected(wxCommandEvent& event)
{
    if (this->m_dirty)
    {
        wxMessageDialog yesNoDiag(this, "Changes have not been saved. Proceed?", "Lose Changes", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
        {
            return;
        }
    }
    this->Close(true);
}

void wxFrameMain::InitUI()
{
    //Hide Initially. Different panels are shown later depending on the type of tree node selected.
    this->m_boxSizerHeaderEmpty->Hide(this->pnlHeaderEmpty, true);
    this->m_boxSizerHeaderObjectType->Hide(this->pnlHeaderObjectType, true);
    this->m_boxSizerHeaderVariableType->Hide(this->pnlHeaderVariableType, true);
    this->m_boxSizerHeaderVariable->Hide(this->pnlHeaderVariable, true);
    this->m_boxSizerHeaderReferenceType->Hide(this->pnlHeaderReferenceType, true);
    this->m_boxSizerHeaderReference->Hide(this->pnlHeaderReference, true);
    this->m_boxSizerHeaderMethod->Hide(this->pnlHeaderMethod, true);
    this->m_boxSizerHeaderInstance->Hide(this->pnlHeaderInstance, true);
    this->m_boxSizerHeaderType->Hide(this->pnlHeaderType, true);
    this->m_boxSizerHeaderStructDataType->Hide(this->pnlHeaderStructDataType, true);
    this->m_boxSizerHeaderEnumDataType->Hide(this->pnlHeaderEnumDataType, true);
    this->m_boxSizerDetailFooter->Hide(this->pnlDetailFooter, true);
    Layout();
}

void wxFrameMain::OnbtnUpdateClick(wxCommandEvent& event)
{
    //Update
    wxTreeItemId selectedItemId = treeOPCCtrl->GetSelection();
    if(   selectedItemId.IsOk()
       && treeOPCCtrl->GetRootItem() != selectedItemId)
    {
        string bufferTargetId;
        string prevTargetId             = OPCUtils::GetTargetId(selectedItemId, bufferTargetId, this->treeOPCCtrl);
        string prevNodeText             = this->treeOPCCtrl->GetItemText(selectedItemId).ToStdString();
        wxTreeItemData *data            = treeOPCCtrl->GetItemData(selectedItemId);
        OPCItemData<void> *pvData       = reinterpret_cast<OPCItemData<void> *>(data);
        bool updated                    = false;

        wxLogMessage("");
        wxLogMessage("Update Start - Node:%s", prevNodeText);
        wxLogMessage("Update Node Type:%s", OPCUtils::NodeTypeToString(pvData->NodeType));

        switch(pvData->NodeType)
        {
            case NodeTypeDataType:
            {
                OPCItemData<DataTypeDesign> *parentNode = dynamic_cast<OPCItemData<DataTypeDesign> *>(data);
                if (OPCUtils::IsSameTypeDefinition(this->m_model.get(), *parentNode->Element, "Enumeration", NodeTypeDataType))
                    updated = this->pnlHeaderEnumDataType->UpdateData();
                else if (OPCUtils::IsSameTypeDefinition(this->m_model.get(), *parentNode->Element, "Structure", NodeTypeDataType))
                    updated = this->pnlHeaderStructDataType->UpdateData();
                else
                    updated = this->pnlHeaderType->UpdateData("DataType");

                break;
            }
            case NodeTypeObjectType:
            {
                updated = this->pnlHeaderObjectType->UpdateData();
                break;
            }
            case NodeTypeObject:
            case NodeTypeChildObject:
            {
                updated = this->pnlHeaderInstance->UpdateData("Object");
                break;
            }
            case NodeTypeChildVariable:
            {
                updated = this->pnlHeaderVariable->UpdateData("Variable");
                break;
            }
            case NodeTypeChildProperty:
            {
                updated = this->pnlHeaderVariable->UpdateData("Property");
                break;
            }
            case NodeTypeVariableType:
            {
                updated = this->pnlHeaderVariableType->UpdateData();
                break;
            }
            case NodeTypeReference:
            {
                updated = this->pnlHeaderReference->UpdateData();
                break;
            }
            case NodeTypeReferenceType:
            {
                updated = this->pnlHeaderReferenceType->UpdateData();
                break;
            }
            case NodeTypeChildMethod:
            case NodeTypeMethod:
            {
                updated = this->pnlHeaderMethod->UpdateData();
                break;
            }
        default:
            cerr << "switch default - This is a bug! case: " << pvData->NodeType << " not handled.\n";
            break;
        }

        if (updated)
        {
            bool treeRebuilt = false;
            if (pvData->NodeType == NodeTypeReference)
            {
                OPCItemData<Reference> *ref  = reinterpret_cast<OPCItemData<Reference> *>(data);
                string newRefTargetid = OPCUtils::GetStringFromQName(ref->Element->TargetId());

                //Rebuild tree, only if the TargetId has been changed.
                if (prevNodeText != newRefTargetid)
                {
                    m_modelTree->CreateTree(this->m_model.get(), true, true, *ref->Element);
                    treeRebuilt = true;
                }
                wxLogMessage("Update End - Node:(Before:%s, After:%s)", prevNodeText, newRefTargetid);
            }
            else
            {
                OPCItemData<NodeDesign> *pNode  = reinterpret_cast<OPCItemData<NodeDesign> *>(data);
                bufferTargetId = "";
                string newTargetId  = OPCUtils::GetTargetId(selectedItemId, bufferTargetId, this->treeOPCCtrl);
                string newSymName   = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pNode->Element->SymbolicName());

                //Rebuild tree and propagate, only if made changes to the Symbolic Name
                if (prevNodeText != newSymName)
                {
                    m_modelTree->PropagateUpdate(prevNodeText, newSymName, prevTargetId, newTargetId, OPCUtils::IsUserNodeOwner(*pNode->Element), pvData->NodeType);
                    m_modelTree->CreateTree(this->m_model.get(), true, true, *pNode->Element);
                    treeRebuilt = true;
                }
                wxLogMessage("Update End - Node:(Before:%s, After:%s)", prevNodeText, newSymName);
            }

            if (treeRebuilt)
            {
                //Since we recreate the tree, we can't use the selectedItemId as it does not exist anymore,
                //so we have to use the property from modelTree where it store the last selected item.
                treeOPCCtrl->SelectItem(m_modelTree->GetLastSelectedItem());
                treeOPCCtrl->ScrollTo(m_modelTree->GetLastSelectedItem());
            }
            else
                //Refresh the panel.
                NodeSelected(selectedItemId);

            this->m_dirty = true;
            ::wxMessageBox(_("Successfully updated."), _("Update"));
        }
        else
            wxLogMessage("Update End (No changes) - Node:", prevNodeText);
    }
}

void wxFrameMain::OnmenuSaveSelected(wxCommandEvent& event)
{
    if (this->m_gitProjectType)
        OnmnuSaveGithubSelected(event);
    else
    {
        wxBusyCursor cursorSpinning;
        Save((m_projectFile == "")); //Show save dialog is file is not set
    }
}

void wxFrameMain::OnmenuSaveAsSelected(wxCommandEvent& event)
{
    wxBusyCursor cursorSpinning;

    Save(true);
}

void wxFrameMain::Save(bool showSaveDialog, bool temp /*= false*/)
{
    wxLogMessage("");
    wxLogMessage("Save() Start");

    if(m_model.get() == 0) /* This should not happen. */
    {
        ::wxMessageBox(_("Model is empty, nothing to saved."), _("Save"));
        return;
    }

    //We don't check m_xmlNewlyCreated because even after saving, the
    //Project setting name and URI are still editable.
    if (  (  m_projectName == ""
           || m_projectURI == "")
        && this->m_projectFile == "")
    {
        if (!SetProjectSettings())
            return;
    }

    if (   m_projectFile == ""
        || showSaveDialog)
    {
        //Filename to save.
        wxFileDialog openFileDialog(this,
                                    _("Save As"), "", "",
                                    _("UA XML files (*.xml)|*.xml"), wxFD_SAVE);

        if (openFileDialog.ShowModal() == wxID_CANCEL)
            return;

        struct stat buffer;
        if (   stat(openFileDialog.GetPath().ToAscii(), &buffer) == 0
            && wxYES != wxMessageBox("File already exists. Do you want to overwrite it?", "Confirm Overwrite",
                                     wxYES_NO|wxNO_DEFAULT, this))
            return;

        m_projectFile = openFileDialog.GetPath();
    }
    std::ofstream ofs(m_projectFile.c_str());
    SaveModel(ofs);
    ::wxMessageBox(wxString::Format("Successfully saved %s", m_projectFile), _("Save"));
    this->m_dirty           = false;
    this->m_gitProjectType  = false;

    wxLogMessage("Save() End");
}

//TODO: Move this logic to UMXModelManager class.
void wxFrameMain::SaveModel(std::ostream &outStream)
{
    wxLogMessage("");
    wxLogMessage("SaveModel Start");



    //N.B: We don't save it yet, instead we weed out the built-in types.
    //     By cloning the actual to a temporary model, we can now delete non-user elements

    //     then save the temporary model.
    //ModelDesign_(cout, *m_model, m);  //to stdout
    //ModelDesign_(ofs, *m_model, m);   //to file

    auto_ptr<ModelDesign> tempModel(new ModelDesign(*this->m_model.get()));

    ITERATE_MODELLIST(DataType, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->DataType().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(VariableType, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->VariableType().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(ReferenceType, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->ReferenceType().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(ObjectType, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->ObjectType().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(Method, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->Method().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(Object, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->Object().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(Variable, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->Variable().erase(i);
            --i;
        }
    }

    ITERATE_MODELLIST(Property, i, tempModel)
    {
        if (!OPCUtils::IsUserNodeOwner(&(*i)))
        {
            tempModel->Property().erase(i);
            --i;
        }
    }

    //Note that we can add schema for each name that we define, just like the empty name .
    //Refer to http://www.codesynthesis.com/projects/xsd/documentation/cxx/tree/guide/ 6.1 Namespace and Schema Information
    xml_schema::namespace_infomap m;
    m["opc"].name   = "http://opcfoundation.org/UA/ModelDesign.xsd";
    m["opc"].schema = "opc_with_namespace.xsd"; //TODO: This should be a resource file

    m["xsi"].name   = "http://www.w3.org/2001/XMLSchema-instance";
    m["xsd"].name   = "http://www.w3.org/2001/XMLSchema";
    m["ua"].name    = "http://opcfoundation.org/UA/";
    m["uax"].name   = "http://opcfoundation.org/UA/2008/02/Types.xsd";

    //TODO: Verify if we don't really need this.
    //      Looks like we don't need this. We can just put an empty string and it should work.
    //      If so, we can treat all namespaces in the same way in the list view,
    //      remove the fields for the main project settings!!!
    m[""].name      = this->m_model->TargetNamespace();  //xmlns (Default namespace)

    if (m_xmlNewlyCreated)
        cout << "Saved with a new namespace_infomap.\n";
    else
    {
        std::map<std::string, std::string>::iterator iter, iterEnd;
        iterEnd = m_modelNSInfoMap.end();
        for (iter = m_modelNSInfoMap.begin(); iter != iterEnd; ++iter)
        {
            cout << "key: \"" << iter->first << "\" "
                 << "value: " << iter->second << endl;
             m[iter->first].name = iter->second;
        }

        cout << "Saved with additional namespace_infomap from the opened xml.\n";
    }

    ModelDesign_(outStream, *tempModel, m);
    wxLogMessage("SaveModel End");
}

//This is deprecated. We don't allow the model to be deleted.
//Let the user create a new model.
void wxFrameMain::OnmenuClearSelected(wxCommandEvent& event)
{
    wxBusyCursor cursorSpinning;

    if(m_model.get() == 0)
        return;

    //Delete each Element group
    m_model->ObjectType().erase(m_model->ObjectType().begin(), m_model->ObjectType().end());
    m_model->VariableType().erase(m_model->VariableType().begin(), m_model->VariableType().end());
    m_model->ReferenceType().erase(m_model->ReferenceType().begin(), m_model->ReferenceType().end());
    m_model->DataType().erase(m_model->DataType().begin(), m_model->DataType().end());
    m_model->Method().erase(m_model->Method().begin(), m_model->Method().end());
    m_model->Object().erase(m_model->Object().begin(), m_model->Object().end());
    m_model->Variable().erase(m_model->Variable().begin(), m_model->Variable().end());
    m_model->Property().erase(m_model->Property().begin(), m_model->Property().end());
    m_model->Dictionary().erase(m_model->Dictionary().begin(), m_model->Dictionary().end());
    m_model->View().erase(m_model->View().begin(), m_model->View().end());

    m_modelTree->CreateTree(this->m_model.get());
    wxLogMessage("Save End");
}

void wxFrameMain::ReCreateNodeTree(const wxTreeItemId& treeItemId, NodeDesign* node, bool userOwner)
{
    treeOPCCtrl->DeleteChildren(treeItemId);

    this->m_modelTree->PopulateChildrenTree(treeItemId, node,
                                            TREE_SHOW_CHILD_OBJECT | TREE_SHOW_CHILD_VARIABLE | TREE_SHOW_CHILD_PROPERTY | TREE_SHOW_CHILD_METHOD,
                                            0, userOwner);
    this->m_modelTree->PopulateReferencesTree(treeItemId, node, 0, userOwner);
}

void wxFrameMain::OnmenuImportSelected(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this,
                                _("Import OPC UA XML file"), "", "",
                                _("XML files (*.xml)|*.xml"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    auto_ptr<wxBusyCursor> cursorSpinning(new wxBusyCursor());

    OPCImporter importer;
    if (!importer.Import(openFileDialog.GetPath().ToStdString().c_str()))
    {
        cursorSpinning.reset();
        ::wxMessageBox(wxString::Format("Failed to import %s.", openFileDialog.GetPath().ToStdString()), "Import");
    }
    else
    {
        wxLogMessage("");
        wxLogMessage("Open Start - File:%s", openFileDialog.GetPath().ToStdString());
        if (OpenModel(importer.GetMergedFile(), true))
        {
            cursorSpinning.reset();
            m_xmlNewlyCreated = false;
            ::wxMessageBox(wxString::Format("Successfully imported %s", openFileDialog.GetPath().ToStdString()), "Import");
        }else
        {
            cursorSpinning.reset();
            ::wxMessageBox(wxString::Format("Failed to import %s.", openFileDialog.GetPath().ToStdString()), "Import");
        }
        wxLogMessage("Open End");
    }
}

void wxFrameMain::OnmenuSettingsSelected(wxCommandEvent& event)
{
    if (!SetProjectSettings())
        return;
}

//This is for newly created only. Even if it is saved, as long as it was not opened.
bool wxFrameMain::SetProjectSettings()
{
    wxProjectDialog projectDiag(this->m_model.get(), this);
    projectDiag.SetEditable(this->m_xmlNewlyCreated);

    projectDiag.txtName->SetValue(m_projectName);
    if (!this->m_xmlNewlyCreated)
        projectDiag.txtFullURI->SetValue(m_projectURI);
    else
        projectDiag.txtFullURI->SetValue(m_projectName == "" ? "http://opcfoundation.org/UA/xxxxxxxxxx/" : m_projectURI );

    if (!m_gitProjectType)
        projectDiag.txtFilename->SetValue(m_projectFile);
    else
    {
        wxURI url(wxString::Format("https://github.com/%s/%s/blob/%s/%s",
                                 m_gitRepoOwner,
                                 m_gitRepo,
                                 m_gitBranch,
                                 m_gitFilePath
                                 ));
        projectDiag.txtFilename->SetValue(url.BuildURI());
    }

    projectDiag.LoadOtherNamespaces();
    if (projectDiag.ShowModal() != wxID_OK)
        return false;

    /* Set new project setting values. */
    m_projectName = projectDiag.txtName->GetValue().ToStdString();
    m_projectURI  = projectDiag.txtFullURI->GetValue().ToStdString();
    this->SetTitle(wxString::Format("UA Model eXcelerator (Project: %s)", m_projectName));


    /* Set model namespace based on project setting values. */
    if (this->m_model->Namespaces() == 0)
    {
        NamespaceTable nsTable;
        this->m_model->Namespaces(nsTable);
    }

    this->m_model->Namespaces()->Namespace().erase( this->m_model->Namespaces()->Namespace().begin(),
                                                    this->m_model->Namespaces()->Namespace().end());

    //TODO: Verify if we don't really need this.
    //      Looks like we don't need this. We can just put an empty string and it should work.
    //      If so, we can treat all namespaces in the same way in the list view,
    //      remove the fields for the main project settings!!!
    this->m_model->TargetNamespace(m_projectURI);

    //Create the project namespace entry.
    Namespace modelNamespace(m_projectURI);
    modelNamespace.Prefix(m_projectName);
    modelNamespace.XmlPrefix(m_projectName);
    modelNamespace.Name(m_projectName);
    //TODO: Not sure if it is necessary to include other attributes(InternalPrefix, XmlNamespace, etc...)
    this->m_model->Namespaces()->Namespace().insert(this->m_model->Namespaces()->Namespace().begin(),
                                                    modelNamespace);

    /* Create the server namespace entry. */
    //To avoid duplicate error for the server when importing, we have removed the Namespaces from the model template xml
    //and dynamically generate it here.
    Namespace serverNamespace("http://opcfoundation.org/UA/");
    serverNamespace.Prefix("Opc.Ua");
    serverNamespace.Name("OpcUa");
    serverNamespace.InternalPrefix("Opc.Ua.Server");
    serverNamespace.XmlNamespace("http://opcfoundation.org/UA/2008/02/Types.xsd");
    this->m_model->Namespaces()->Namespace().insert(this->m_model->Namespaces()->Namespace().begin(),
                                                    serverNamespace);

    return true;
}

void wxFrameMain::OnmnuAboutSelected(wxCommandEvent& event)
{
    wxAbout about(this);
    about.ShowModal();
}

void wxFrameMain::OnClose(wxCloseEvent& event)
{
    if (   event.CanVeto()
        && this->m_dirty)
    {
        wxMessageDialog yesNoDiag(this, "Changes have not been saved. Proceed?", "Lose Changes", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
        {
            event.Veto();
            return;
        }
    }
    wxLogMessage("************************");
    wxLogMessage("eXcelerator End");
    wxLogMessage("************************\n\n");
    delete wxLog::SetActiveTarget(0);
    if (m_logFile.get() != 0)
        fclose(m_logFile.get());
    Destroy();
}

void wxFrameMain::OnmnuCompileSelected(wxCommandEvent& event)
{
    if (m_projectFile == "")
    {
        ::wxMessageBox("This project has not been saved yet.", "UA Model Compiler");
        return;
    }
    else
    {
        wxFileName fInput(m_projectFile);
        if (!fInput.Exists())
        {
            ::wxMessageBox("Project file does not exist. Save the model first.", "UA Model Compiler");
            return;
        }
    }

    if (this->m_dirty)
    {
        /*
        wxMessageDialog yesNoDiag(this,
                                  "Changes have not been saved.\n"
                                  "It will not be included in the compilation. Proceed?",
                                  "UA Model Compiler", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
            return;
        */

        //We will not allow to proceed when it is still dirty because we need to validate the model first if we
        //can proceed. An empty model will cause the Compiler to crash.
        ::wxMessageBox("Changes in the model have not been saved yet.", "UA Model Compiler");
        return;
    }

    /* Check if the model is empty, it will crash the compiler. */
    bool hasUserElement = false;
    ITERATE_MODELLIST(DataType, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(VariableType, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(ReferenceType, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(ObjectType, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(Method, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(Object, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(Variable, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    ITERATE_MODELLIST(Property, i, m_model)
    {
        if (OPCUtils::IsUserNodeOwner(&(*i)))
        {
            hasUserElement = true;
            break;
        }
    }

    if (!hasUserElement)
    {
        ::wxMessageBox("Empty model, nothing to compile.", "UA Model Compiler");
        return;
    }


    /*TODO: Other option is to compile the model instead of using the project file. */



    wxCompileDialog compileDlg(m_projectFile, this);
    compileDlg.ShowModal();
}

void wxFrameMain::OntbSaveClicked(wxCommandEvent& event)
{
    this->OnmenuSaveSelected(event);
}

void wxFrameMain::OntbCompileClicked(wxCommandEvent& event)
{
    this->OnmnuCompileSelected(event);
}

void wxFrameMain::OntbOpenClicked(wxCommandEvent& event)
{
    this->OnmenuOpenSelected(event);
}

void wxFrameMain::OnmnuConfigSelected(wxCommandEvent& event)
{
    wxConfig config(this);
    config.ShowModal();
}

void  wxFrameMain::OpenGithubSetting(bool openGitProject)
{
    if (this->m_dirty)
    {
        wxMessageDialog yesNoDiag(this, "Changes have not been saved. Proceed?", "Lose Changes", wxYES_NO|wxNO_DEFAULT);
        if (yesNoDiag.ShowModal() != wxID_YES)
            return;
    }

    wxProjectGitDialog projectGitDiag(m_gitUsername, m_gitPassword, this);

    if (openGitProject)
    {
        wxFileDialog openFileDialog(this,
                                    _("Open UA XML file"), "", "",
                                    _("Github UMX files (*.github.umx)|*.github.umx"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

        if (openFileDialog.ShowModal() == wxID_CANCEL)
            return;
        projectGitDiag.OpenGitProjectFile(openFileDialog.GetPath().ToStdString());
    }

    projectGitDiag.ShowModal();
    if (projectGitDiag.GitFileToOpen != "")
    {
        this->SetCursor(wxCursor(wxCURSOR_WAIT));
        wxString importError;
        OPCImporter importer;
        if (!importer.MergeUMXToBuiltInTypes(projectGitDiag.GitFileToOpen.ToStdString().c_str(), importError, m_modelNSInfoMap))
        {
            this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
            ::wxMessageBox(importError, "Open");
        }else
        {
            wxLogMessage("");
            wxLogMessage("Open Start - File:%s", projectGitDiag.GitFileToOpen.ToStdString());
            if (OpenModel(importer.GetMergedFile(), true))
            {
                m_xmlNewlyCreated = false;
                m_gitProjectType  = true;
                m_gitUsername     = projectGitDiag.GitUsername;
                m_gitPassword     = projectGitDiag.GitPassword;
                m_gitRepoOwner    = projectGitDiag.txtRepoOwner->GetValue();
                m_gitRepo         = projectGitDiag.txtRepo->GetValue();
                m_gitFilePath     = projectGitDiag.txtGithubFile->GetValue();;
                m_gitBranch       = projectGitDiag.txtBranch->GetValue();;
                m_projectFile     = projectGitDiag.GitFileToOpen.ToStdString();
                m_gitSHA          = projectGitDiag.GitSHA;
                this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
                ::wxMessageBox("Successfully opened github file.", "Github");
            }
            else
            {
                this->SetCursor(wxCursor(wxCURSOR_DEFAULT));
               ::wxMessageBox(wxString::Format("Failed to open %s.", projectGitDiag.GitFileToOpen.ToStdString()), "Open");
            }
            wxLogMessage("Open - End");
        }
    }
}

void wxFrameMain::OnmnuNewGithubSelected(wxCommandEvent& event)
{
    OpenGithubSetting(false);
}

void wxFrameMain::OnmnuOpenGithubSelected(wxCommandEvent& event)
{
    OpenGithubSetting(true);
}

void wxFrameMain::OnmnuSaveGithubSelected(wxCommandEvent& event)
{
    if (   m_gitProjectType
        && m_projectFile != ""
        && m_gitRepoOwner != ""
        && m_gitRepo != ""
        && m_gitFilePath != ""
        && m_gitBranch != "")
    {
        JSONValue *jsonValue = 0;
        wxURI url(wxString::Format("https://api.github.com/repos/%s/%s/contents/%s",
                                    m_gitRepoOwner,
                                    m_gitRepo,
                                    m_gitFilePath
                                 ));

        //Encode model xml to Base64
        ostringstream strStream;
        SaveModel(strStream);
        wxString uaXMLBase64 = wxBase64Encode(strStream.str().c_str(), strStream.str().size());

        if (OPCUtils::GithubConnect(m_gitUsername, m_gitPassword,
                                    wxString::Format("-X PUT -d \"{\\\"branch\\\": \\\"%s\\\", \\\"message\\\": \\\"Commit from UMX\\\", "
                                                     "\\\"content\\\": \\\"%s\\\", \\\"sha\\\": \\\"%s\\\"}\" \"%s\"",
                                                     m_gitBranch,
                                                     uaXMLBase64,
                                                     m_gitSHA,
                                                     url.BuildURI()),
                                    &jsonValue))
        {
            JSONObject root = jsonValue->AsObject();
            if (root.find(L"commit") != root.end())
            {
                m_dirty = false;
                ::wxMessageBox("Successfully saved to github.", "Github");
            }
            else if (   root.find(L"message") != root.end()
                     && root[L"message"]->IsString())
                ::wxMessageBox(wxString::Format("Error: %s.", (root[L"message"]->AsString().c_str())), "Github");
            else
                ::wxMessageBox("Error: Unknown.", "Github");
        }

        if (jsonValue != 0)
            delete jsonValue;
    }
}
