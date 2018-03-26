#ifndef WXFRAMEMAIN_H
#define WXFRAMEMAIN_H

//(*Headers(wxFrameMain)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <opcglobal.h>
#include <opcitemdata.hxx>

#include <vector>
#include <memory>
#include <map>
#include <queue>

//#include <map> --requires -std=c++11 and our code synthesis has to be generated in c++11

class ObjectTypeDesign;
class ModelDesign;
class ModelTree;
class NodeDesign;
class wxFile;
class wxPanelType;
class wxPanelStructDataType;
class wxPanelEnumDataType;
class wxPanelReferenceType;
class wxPanelInstance;
class wxPanelReference;
class wxPanelMethod;
class wxPanelObjectType;
class wxPanelVariableType;
class wxPanelVariable;
class wxScrolledWindow;

class wxFrameMain: public wxFrame
{
	public:

		wxFrameMain(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxFrameMain();

		//(*Declarations(wxFrameMain)
		wxMenuItem* menuSettings;
		wxMenu* menuFile;
		wxToolBarToolBase* tbCompile;
		wxMenuItem* mnuOpenGithub;
		wxMenuItem* menuImport;
		wxToolBarToolBase* tbSave;
		wxToolBar* toolbar;
		wxPanelReferenceType* pnlHeaderReferenceType;
		wxPanelInstance* pnlHeaderInstance;
		wxButton* btnUpdate;
		wxPanelMethod* pnlHeaderMethod;
		wxTreeCtrl* treeOPCCtrl;
		wxPanelVariableType* pnlHeaderVariableType;
		wxMenu* Menu1;
		wxMenuItem* mnuCompile;
		wxMenuItem* menuNew;
		wxMenuItem* menuSave;
		wxMenuItem* menuSaveAs;
		wxMenuBar* menuBarMain;
		wxPanelType* pnlHeaderType;
		wxMenu* menuHelp;
		wxPanelEnumDataType* pnlHeaderEnumDataType;
		wxMenuItem* menuExit;
		wxMenuItem* mnuAbout;
		wxMenuItem* menuOpen;
		wxToolBarToolBase* tbOpen;
		wxPanel* pnlDetailFooter;
		wxMenuItem* mnuNewGithub;
		wxPanelObjectType* pnlHeaderObjectType;
		wxScrolledWindow* panelMain;
		wxStatusBar* statusBarMain;
		wxPanelStructDataType* pnlHeaderStructDataType;
		wxMenu* Menu2;
		wxMenuItem* mnuConfig;
		wxPanelVariable* pnlHeaderVariable;
		wxPanel* pnlHeaderEmpty;
		wxPanelReference* pnlHeaderReference;
		//*)

	protected:

		//(*Identifiers(wxFrameMain)
		static const long ID_TREEOPC_ID;
		static const long ID_PANEL_HEADER_OBJ_TYPE;
		static const long ID_PANEL_HEADER_VAR_TYPE;
		static const long ID_PANEL_HEADER_EMPTY;
		static const long ID_CUSTOM1;
		static const long ID_CUSTOM2;
		static const long ID_CUSTOM3;
		static const long ID_PNL_METHOD;
		static const long ID_CUSTOM4;
		static const long ID_CUSTOM5;
		static const long ID_CUSTOM6;
		static const long ID_CUSTOM7;
		static const long ID_BUTTON_UPDATE;
		static const long ID_PANEL_DETAIL_FOOTER;
		static const long ID_PANEL_MAIN;
		static const long ID_MENUITEM_NEW;
		static const long ID_MENUITEM3;
		static const long ID_MENUSAVE;
		static const long ID_MENUITEM2;
		static const long ID_MENUITEM1;
		static const long ID_MENUITEM8;
		static const long ID_MENUITEM11;
		static const long ID_MENUITEM10;
		static const long ID_MENUITEM7;
		static const long ID_MENUITEM4;
		static const long ID_MENUITEM5;
		static const long ID_MENUITEM6;
		static const long ID_MENU_ABOUT;
		static const long ID_STATUSBAR_MAIN;
		static const long ID_TOOLBARITEM3;
		static const long ID_TOOLBARITEM1;
		static const long ID_TOOLBARITEM2;
		static const long ID_TOOLBAR1;
		//*)

	private:

		//(*Handlers(wxFrameMain)
		void OnBtnDeleteAllClick(wxCommandEvent& event);
		void OnBtnSaveClick(wxCommandEvent& event);
		void OntreeOPCCtrlItemActivated(wxTreeEvent& event);
		void OntreeOPCCtrlSelectionChanged(wxTreeEvent& event);
		void OntreeOPCCtrlItemRightClick(wxTreeEvent& event);
		void OnmenuNewSelected(wxCommandEvent& event);
		void OnmenuOpenSelected(wxCommandEvent& event);
		void OnmenuExitSelected(wxCommandEvent& event);
		void OnbtnUpdateClick(wxCommandEvent& event);
		void OnmenuSaveSelected(wxCommandEvent& event);
		void OnmenuSaveAsSelected(wxCommandEvent& event);
		void OnmenuClearSelected(wxCommandEvent& event);
		void OnpnlHeaderEmptyPaint(wxPaintEvent& event);
		void OnmenuImportSelected(wxCommandEvent& event);
		void OnmenuSettingsSelected(wxCommandEvent& event);
		void OnmnuAboutSelected(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnmnuCompileSelected(wxCommandEvent& event);
		void OntbSaveClicked(wxCommandEvent& event);
		void OntbCompileClicked(wxCommandEvent& event);
		void OntbOpenClicked(wxCommandEvent& event);
		void OnmnuConfigSelected(wxCommandEvent& event);
		void OnmnuNewGithubSelected(wxCommandEvent& event);
		void OnmnuOpenGithubSelected(wxCommandEvent& event);
		void OnmnuSaveSelected(wxCommandEvent& event);
		void OnmnuSaveGithubSelected(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void InitUI();
        void OnPopupMenuNode(wxCommandEvent &evt);
        void OnPopupMenuAddNode(wxCommandEvent &evt);
        void OnPopupMenuDeleteNode(wxCommandEvent &evt);
        bool DeleteNode(OPCItemData<void> *pvData, bool showConfirmation, std::vector<wxTreeItemId> &nodeItemIdList);
        bool OpenModel(std::string fileName, bool setProjectName);
        //void OpenXML(const char* filename, const char* title, const char* msgAction, const char* msgActionPastTense);
        void OnPopupMenuGotoNode(wxCommandEvent &evt);
        bool SetProjectSettings();

        //@param temp - This will be used to save the model to a temp file for the model compiler to process.
        //TODO: Need to add the logic when temp is true.
        void Save(bool showSaveDialog, bool temp = false);

        void NodeSelected(wxTreeItemId selectedItemId);

        //@symNames should be pass by value so that popping of elements would not
        //affect the original copy for the next type iteration.
        bool SearchName(NodeDesign *node, std::string refTargetId, std::queue<std::string> symNames);
        NodeDesign *FindChildren(NodeDesign *currentNode, std::queue<std::string> symNames);

        //Recursively search the node in the tree. Each tree node has an OPCItemData attached to it.
        //By walking through all the tree nodes, we are able to compare the address of the OPCItemData and the nodeToSearch.
        bool SearchNodeInTree(const wxTreeItemId &itemId, NodeDesign *nodeToSearch);

        void OpenGithubSetting(bool openGitProject);
        void SaveModel(std::ostream &outStream);

    public:
        void ReCreateNodeTree(const wxTreeItemId &treeItemId, NodeDesign *nodeToSearch, bool userOwner);

    private:
        wxBoxSizer* m_boxSizerHeaderObjectType;
        wxBoxSizer* m_boxSizerHeaderVariableType;
        wxBoxSizer* m_boxSizerHeaderEmpty;
        wxBoxSizer* m_boxSizerHeaderReferenceType;
        wxBoxSizer* m_boxSizerHeaderReference;
        wxBoxSizer* m_boxSizerHeaderInstance;
        wxBoxSizer* m_boxSizerHeaderVariable;
        wxBoxSizer* m_boxSizerHeaderType;
        wxBoxSizer* m_boxSizerHeaderStructDataType;
        wxBoxSizer* m_boxSizerHeaderEnumDataType;
        wxBoxSizer* m_boxSizerDetailFooter;

        wxBoxSizer* m_boxSizerHeader;
        wxBoxSizer* m_boxSizerMain;
        wxBoxSizer* m_boxSizerDetail;
        wxBoxSizer* m_boxSizerPanelMain;
        wxBoxSizer* m_boxSizerHeaderMethod;

        std::auto_ptr<ModelDesign> m_model;
        std::auto_ptr<ModelTree> m_modelTree;
        std::map<std::string, std::string> m_modelNSInfoMap; //Loaded/Opened model, will have its namespaces info map stored here.

        std::string m_projectName;
        std::string m_projectURI;
        std::string m_projectFile;

        bool m_dirty;

        bool m_xmlNewlyCreated;   //We don't allow changes for project setting on files that are opened or imported.
                                  //Default/Target Namespace has already been set to all the elements without prefixes
                                  //during opening of the xml. Changing after it's opened, will create
                                  //prefixes for new elements like p1, p2, p3, etc..
        std::auto_ptr<FILE> m_logFile;

        bool m_gitProjectType;

        wxString m_gitUsername;
        wxString m_gitPassword;
        wxString m_gitRepoOwner;
        wxString m_gitRepo;
        wxString m_gitFilePath;
        wxString m_gitBranch;
        wxString m_gitSHA;
};
#endif
