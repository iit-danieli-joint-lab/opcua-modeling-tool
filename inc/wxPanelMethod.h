#ifndef WXPANELMETHOD_H
#define WXPANELMETHOD_H

//(*Headers(wxPanelMethod)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/combobox.h>
//*)

#include "synthesis/opc.hxx"

#include <wx/treebase.h>

class wxPanelInstance;
class wxFrameMain;

class wxPanelMethod: public wxPanel
{
	public:

		wxPanelMethod(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~wxPanelMethod();

		//(*Declarations(wxPanelMethod)
		wxStaticText* StaticText2;
		wxComboBox* cboTypeDefinition;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* StaticText5;
		wxCheckBox* chkNonExecutable;
		wxTextCtrl* txtSymbolicName;
		wxListView* listOutput;
		wxListView* listInput;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(wxPanelMethod)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_LISTVIEW_INPUT;
		static const long ID_STATICTEXT3;
		static const long ID_LISTVIEW_OUTPUT;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX1;
		//*)

	private:

		//(*Handlers(wxPanelMethod)
		void OnlistInputBeginDrag(wxListEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void OnButton1Click2(wxCommandEvent& event);
		void OnlistInputBeginDrag1(wxListEvent& event);
		void OnlistInputBeginDrag2(wxListEvent& event);
		void OnlistInputBeginDrag3(wxListEvent& event);
		void OnlistInputItemRClick1(wxListEvent& event);
		void OntxtSymbolicNameText(wxCommandEvent& event);
		void OnlistInputBeginDrag4(wxListEvent& event);
		void OnlistInputBeginDrag5(wxListEvent& event);
		void OnlistInputBeginDrag6(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

    private:
        void OnPopupList(wxCommandEvent &evt);
        void SetListItemParameter(Parameter *param, wxListView *listView, int nodeId, bool disabled);

        //Custom Event Handlers
        void OnlistInputItemRClick(wxCommandEvent& event);
		void OnlistOutputItemRClick(wxCommandEvent& event);

		void AddParameter(Parameter &param, bool isInput);
		void DeleteParameter(bool isInput);

        void PopulateInputArgs();
        void PopulateOutputArgs();

    public:
        //This method has to be called every time a node is clicked to associate
        //this panel with the new node value.
        //@param showTypeDef: Type Definition attribute is only available for Child Method because
        //                    it uses the Method instances defined, as the type. This is another opc quirk
        //                    where Method are InstanceDesign instead of a TypeDesign.
        void Init(MethodDesign *method, ModelDesign *model, wxTreeItemId treeItemId,
                  wxFrameMain *mainFrame, bool userOwner, bool showTypeDef);

        void PopulateData();
        void Clear();
        bool UpdateData();

    private:
        MethodDesign *m_method;
        ModelDesign* m_model;
        wxTreeItemId m_treeItemId;
        wxFrameMain *m_mainFrame;
        bool m_showTypeDef;
        bool m_userOwner;
        //This will store temporarily the input/output parameters to allow the user to manually Update the changes.
        std::auto_ptr<MethodDesign> m_tempMethod;
};

#endif
