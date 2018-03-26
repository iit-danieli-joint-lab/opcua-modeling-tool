#include <modelTree.h>
#include <opcutils.h>
#include <opcglobal.h>
#include <opcitemdata.hxx>
#include <opcelement.hxx>
#include <synthesis/opc.hxx>

#include "wx/log.h"
#include <sstream>

using namespace std;

ModelTree::ModelTree(wxTreeCtrl *treeOPCCtrl)
                    : m_treeOPCCtrl(treeOPCCtrl)
{
    //ctor
}

ModelTree::~ModelTree()
{
    //dtor
}

void ModelTree::CreateTree(ModelDesign *modelDesign, bool showChildren,
                           bool showReferences, void *nodeAdded, int showRootMask)
{
    m_model = modelDesign;

    m_treeOPCCtrl->DeleteAllItems();

    //TODO: ModelDesign should not be empty. It should be initialized(opened) with an empty xml.
    if(m_model == 0)
        return;

    wxTreeItemId rootId = m_treeOPCCtrl->AddRoot(_T("Hidden Root"));

    wxTreeItemData *itemDataRoot = OPCUtils::CreateItemData(NodeTypeRoot, rootId);
    m_treeOPCCtrl->SetItemData(rootId, itemDataRoot);

    if (showRootMask & RootMaskShowDataType)
    {
        //DataType
        wxTreeItemId dataTypeRootId = m_treeOPCCtrl->AppendItem(rootId, _T("DataType"));
        wxTreeItemData *itemDataDataTypeRoot = OPCUtils::CreateItemData(NodeTypeDataTypeRoot, dataTypeRootId);
        m_treeOPCCtrl->SetItemData(dataTypeRootId, itemDataDataTypeRoot);
        m_treeOPCCtrl->SetItemImage(dataTypeRootId, IconFolderWithHammer, wxTreeItemIcon_Normal);

        wxTreeItemId dataTypeBaseRootId = m_treeOPCCtrl->AppendItem(dataTypeRootId, _T("BaseDataType"));
        m_treeOPCCtrl->SetItemImage(dataTypeBaseRootId, IconDocumentType, wxTreeItemIcon_Normal);
        m_treeOPCCtrl->SetItemTextColour(dataTypeBaseRootId, OPCUtils::DARK_GRAY);
        PopulateDataSubTypesTree(dataTypeBaseRootId, "BaseDataType", true, nodeAdded);
        //TODO: Should we include those that has no BaseType=""? PopulateDataSubTypesTree(dataTypeRootId, "");
    }

    if (showRootMask & RootMaskShowEventType)
    {
        //EventType -   Although this is part of the ObjectType, opc trend to treat this a type
        //              of its own. So we put this under the virtual root.
        wxTreeItemId eventTypeRootId = m_treeOPCCtrl->AppendItem(rootId, _T("EventType"));
        wxTreeItemData *itemDataEventTypeRoot = OPCUtils::CreateItemData(NodeTypeObjectTypeRoot, eventTypeRootId);
        m_treeOPCCtrl->SetItemData(eventTypeRootId, itemDataEventTypeRoot);
        m_treeOPCCtrl->SetItemImage(eventTypeRootId, IconFolderWithHammer, wxTreeItemIcon_Normal);

        wxTreeItemId baseEventTypeRootId = m_treeOPCCtrl->AppendItem(eventTypeRootId, _T("BaseEventType"));
        m_treeOPCCtrl->SetItemImage(baseEventTypeRootId, IconDocumentType, wxTreeItemIcon_Normal);
        m_treeOPCCtrl->SetItemTextColour(baseEventTypeRootId, OPCUtils::DARK_GRAY);
        map<string, string> emptyExcludeTypeList;
        PopulateObjectSubTypesTree(baseEventTypeRootId, "BaseEventType", true, emptyExcludeTypeList,
                                   TREE_SHOW_CHILD_PROPERTY | TREE_SHOW_CHILD_VARIABLE, showChildren, showReferences,
                                   nodeAdded);
    }

    if (showRootMask & RootMaskShowObjectType)
    {
        //ObjectType
        wxTreeItemId objectTypeRootId = m_treeOPCCtrl->AppendItem(rootId, _T("ObjectType"));
        wxTreeItemData *itemDataObjectTypeRoot = OPCUtils::CreateItemData(NodeTypeObjectTypeRoot, objectTypeRootId);
        m_treeOPCCtrl->SetItemData(objectTypeRootId, itemDataObjectTypeRoot);
        m_treeOPCCtrl->SetItemImage(objectTypeRootId, IconFolderWithHammer, wxTreeItemIcon_Normal);

        wxTreeItemId baseObjectTypeRootId = m_treeOPCCtrl->AppendItem(objectTypeRootId, _T("BaseObjectType"));
        m_treeOPCCtrl->SetItemImage(baseObjectTypeRootId, IconDocumentType, wxTreeItemIcon_Normal);
        m_treeOPCCtrl->SetItemTextColour(baseObjectTypeRootId, OPCUtils::DARK_GRAY);
        map<string, string> excludeTypeList;
        excludeTypeList["BaseEventType"] = "BaseEventType"; //Exclude this type since it will be promoted as a root itself.
        PopulateObjectSubTypesTree(baseObjectTypeRootId, "BaseObjectType", true, excludeTypeList,
                                   TREE_SHOW_CHILD_OBJECT | TREE_SHOW_CHILD_VARIABLE | TREE_SHOW_CHILD_PROPERTY | TREE_SHOW_CHILD_METHOD,
                                   showChildren, showReferences, nodeAdded);
    }

    if (showRootMask & RootMaskShowReferenceType)
    {
        //ReferenceType
        wxTreeItemId referenceTypeRootId = m_treeOPCCtrl->AppendItem(rootId, _T("ReferenceType"));
        wxTreeItemData *itemDataReferenceTypeRoot = OPCUtils::CreateItemData(NodeTypeDataTypeRoot, referenceTypeRootId);
        m_treeOPCCtrl->SetItemData(referenceTypeRootId, itemDataReferenceTypeRoot);
        m_treeOPCCtrl->SetItemImage(referenceTypeRootId, IconFolderWithHammer, wxTreeItemIcon_Normal);

        wxTreeItemId referenceTypeBaseRootId = m_treeOPCCtrl->AppendItem(referenceTypeRootId, _T("References"));
        m_treeOPCCtrl->SetItemImage(referenceTypeBaseRootId, IconDocumentType, wxTreeItemIcon_Normal);
        m_treeOPCCtrl->SetItemTextColour(referenceTypeBaseRootId, OPCUtils::DARK_GRAY);
        PopulateReferenceSubTypesTree(referenceTypeBaseRootId, "References", true, nodeAdded);
        //TODO: Should we include those that has no BaseType=""? PopulateReferenceSubTypesTree(referenceTypeRootId, "");
    }

    if (showRootMask & RootMaskShowVariableType)
    {
        //VariableType
        wxTreeItemId variableTypeRootId = m_treeOPCCtrl->AppendItem(rootId, _T("VariableType"));
        wxTreeItemData *itemDataVariableTypeRoot = OPCUtils::CreateItemData(NodeTypeVariableTypeRoot, variableTypeRootId);
        m_treeOPCCtrl->SetItemData(variableTypeRootId, itemDataVariableTypeRoot);
        m_treeOPCCtrl->SetItemImage(variableTypeRootId, IconFolderWithHammer, wxTreeItemIcon_Normal);

        wxTreeItemId baseVariableTypeRootId = m_treeOPCCtrl->AppendItem(variableTypeRootId, _T("BaseVariableType"));
        m_treeOPCCtrl->SetItemImage(baseVariableTypeRootId, IconDocumentType, wxTreeItemIcon_Normal);
        m_treeOPCCtrl->SetItemTextColour(baseVariableTypeRootId, OPCUtils::DARK_GRAY);
        PopulateVariableSubTypesTree(baseVariableTypeRootId, "BaseVariableType", true, showChildren, showReferences, nodeAdded);
    }

    if (showRootMask & RootMaskShowMethod)
    {
        //Method
        wxTreeItemId methodRootId = m_treeOPCCtrl->AppendItem(rootId, _T("Method"));
        wxTreeItemData *itemDataMethodRoot = OPCUtils::CreateItemData(NodeTypeMethodRoot, methodRootId);
        m_treeOPCCtrl->SetItemData(methodRootId, itemDataMethodRoot);
        m_treeOPCCtrl->SetItemImage(methodRootId, IconBallGreen, wxTreeItemIcon_Normal);

        ITERATE_MODELLIST(Method, i, m_model)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(methodRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
            wxTreeItemData *itemData = OPCUtils::CreateItemData<MethodDesign>(NodeTypeMethod, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);

            //Find the new item added to focus.
            if (   nodeAdded != 0
                && nodeAdded == &(*i))
            {
                m_selectedItemId = nodeItemId;
            }

            if (!OPCUtils::IsUserNodeOwner(&(*i)))
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
        }
    }

    if (showRootMask & RootMaskShowObject)
    {
        //Object
        wxTreeItemId objectRootId = m_treeOPCCtrl->AppendItem(rootId, _T("Object"));
        wxTreeItemData *itemDataObjectRoot = OPCUtils::CreateItemData(NodeTypeObjectRoot, objectRootId);
        m_treeOPCCtrl->SetItemData(objectRootId, itemDataObjectRoot);
        m_treeOPCCtrl->SetItemImage(objectRootId, IconBallGreen, wxTreeItemIcon_Normal);

        ITERATE_MODELLIST(Object, i, m_model)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(objectRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
            wxTreeItemData *itemData = OPCUtils::CreateItemData<ObjectDesign>(NodeTypeObject, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
            bool userOwner = OPCUtils::IsUserNodeOwner(&(*i));

            if (showChildren)
                PopulateChildrenTree(nodeItemId, &(*i),
                                     TREE_SHOW_CHILD_OBJECT | TREE_SHOW_CHILD_VARIABLE | TREE_SHOW_CHILD_PROPERTY | TREE_SHOW_CHILD_METHOD,
                                     nodeAdded, userOwner);

            if (showReferences)
                PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

            //Find the new item added to focus.
            if (   nodeAdded != 0
                && nodeAdded == &(*i))
            {
                m_selectedItemId = nodeItemId;
            }

            if (!userOwner)
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            TypeDesign *objType = OPCUtils::GetObjectTypeDesign(this->m_model, &(*i));

            if (   objType != 0
                && OPCUtils::IsSameTypeDefinition(this->m_model, objType, "FolderType", NodeTypeObjectType))
                this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconFolderYellow, wxTreeItemIcon_Normal);
            else
                 this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
        }
    }
}

void ModelTree::PopulateObjectSubTypesTree(const wxTreeItemId &parentId, string baseType, bool setParentItemData,
                                           std::map<string, string> &excludeTypeList, short int showChildrenMask,
                                           bool showChildren, bool showReferences, void *nodeAdded)
{
    ITERATE_MODELLIST(ObjectType, i, m_model)
    {
        string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(i->BaseType());
        string elementSymName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        if (excludeTypeList.count(elementSymName) > 0)
            continue;

        //N.B:  Setting the parent item data here is a workaround
        //      so that we don't have to search the parent separately.
        if (   setParentItemData
            && baseType.compare(elementSymName) == 0)
        {
            wxTreeItemData *parentItemData = OPCUtils::CreateItemData<ObjectTypeDesign>(NodeTypeObjectType, &(*i), parentId);
            m_treeOPCCtrl->SetItemData(parentId, parentItemData);
        }

        if (elementBaseType.compare(baseType) == 0)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(parentId, elementSymName);
            wxTreeItemData *itemData = OPCUtils::CreateItemData<ObjectTypeDesign>(NodeTypeObjectType, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
            bool userOwner = OPCUtils::IsUserNodeOwner(&(*i));

            if (showChildren)
                PopulateChildrenTree(nodeItemId, &(*i), showChildrenMask, nodeAdded, userOwner);

            if (showReferences)
                PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

			if (OPCUtils::IsSameTypeDefinition(this->m_model, &(*i), "FolderType", NodeTypeObjectType))
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconFolderYellow, wxTreeItemIcon_Normal);
			else
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconDocumentType, wxTreeItemIcon_Normal);

			//Find the new item added to focus.
			if (   nodeAdded != 0
				&& nodeAdded == &(*i))
			{
				m_selectedItemId = nodeItemId;
			}

            if (!userOwner)
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            //Use their Symbolic Name to get the subtypes
            PopulateObjectSubTypesTree(nodeItemId, elementSymName, false, excludeTypeList,
                                       showChildrenMask, showChildren, showReferences, nodeAdded);
        }
    }
}

void ModelTree::PopulateVariableSubTypesTree(const wxTreeItemId &parentId, string baseType, bool setParentItemData,
                                             bool showChildren, bool showReferences, void *nodeAdded)
{
    ITERATE_MODELLIST(VariableType, i, m_model)
    {
        string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(i->BaseType());
        string elementSymName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //N.B:  Setting the parent item data here is a workaround
        //      so that we don't have to search the parent separately.
        if (   setParentItemData
            && baseType.compare(elementSymName) == 0)
        {
            wxTreeItemData *parentItemData = OPCUtils::CreateItemData<VariableTypeDesign>(NodeTypeVariableType, &(*i), parentId);
            m_treeOPCCtrl->SetItemData(parentId, parentItemData);
        }

        if (elementBaseType.compare(baseType) == 0)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(parentId,elementSymName);
            wxTreeItemData *itemData = OPCUtils::CreateItemData<VariableTypeDesign>(NodeTypeVariableType, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
            bool userOwner = OPCUtils::IsUserNodeOwner(&(*i));

            if (OPCUtils::IsSameTypeDefinition(this->m_model, &(*i), "Structure", NodeTypeVariableType))
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconStructType, wxTreeItemIcon_Normal);
            else if (OPCUtils::IsSameTypeDefinition(this->m_model, &(*i), "Enumeration", NodeTypeVariableType))
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconEnumType, wxTreeItemIcon_Normal);
			else
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconDocumentType, wxTreeItemIcon_Normal);

            if (showChildren)
                PopulateChildrenTree(nodeItemId, &(*i), TREE_SHOW_CHILD_VARIABLE, nodeAdded, userOwner);

            if (showReferences)
                PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

            //Find the new item added to focus.
            if (   nodeAdded != 0
                && nodeAdded == &(*i))
            {
                m_selectedItemId = nodeItemId;
            }

            if (!userOwner)
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            //Use their Symbolic Name to get the subtypes
            PopulateVariableSubTypesTree(nodeItemId, elementSymName, false, showChildren, showReferences, nodeAdded);
        }
    }
}

void ModelTree::PopulateDataSubTypesTree(const wxTreeItemId &parentId, string baseType, bool setParentItemData,
                                         void *nodeAdded)
{
    ITERATE_MODELLIST(DataType, i, m_model)
    {
        string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(i->BaseType());
        string elementSymName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //N.B:  Setting the parent item data here is a workaround
        //      so that we don't have to search the parent separately.
        if (   setParentItemData
            && baseType.compare(elementSymName) == 0)
        {
            wxTreeItemData *parentItemData = OPCUtils::CreateItemData<DataTypeDesign>(NodeTypeDataType, &(*i), parentId);
            m_treeOPCCtrl->SetItemData(parentId, parentItemData);
        }

        if (elementBaseType.compare(baseType) == 0)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(parentId, elementSymName);
            wxTreeItemData *itemData = OPCUtils::CreateItemData<DataTypeDesign>(NodeTypeDataType, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);

			if (OPCUtils::IsSameTypeDefinition(this->m_model, &(*i), "Structure", NodeTypeDataType))
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconStructType, wxTreeItemIcon_Normal);
            else if (OPCUtils::IsSameTypeDefinition(this->m_model, &(*i), "Enumeration", NodeTypeDataType))
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconEnumType, wxTreeItemIcon_Normal);
			else
				this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconDocumentType, wxTreeItemIcon_Normal);

            //Find the new item added to focus.
			if (   nodeAdded != 0
				&& nodeAdded == &(*i))
			{
				m_selectedItemId = nodeItemId;
			}

            if (!OPCUtils::IsUserNodeOwner(&(*i)))
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            //Use their Symbolic Name to get the subtypes
            PopulateDataSubTypesTree(nodeItemId, elementSymName, false, nodeAdded);
        }
    }
}

void ModelTree::PopulateReferenceSubTypesTree(const wxTreeItemId &parentId, string baseType, bool setParentItemData,
                                              void *nodeAdded)
{
    ITERATE_MODELLIST(ReferenceType, i, m_model)
    {
        string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(i->BaseType());
        string elementSymName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());

        //N.B:  Setting the parent item data here is a workaround
        //      so that we don't have to search the parent separately.
        if (   setParentItemData
            && baseType.compare(elementSymName) == 0)
        {
            wxTreeItemData *parentItemData = OPCUtils::CreateItemData<ReferenceTypeDesign>(NodeTypeReferenceType, &(*i), parentId);
            m_treeOPCCtrl->SetItemData(parentId, parentItemData);
        }

        if (elementBaseType.compare(baseType) == 0)
        {
            wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(parentId, elementSymName);
            wxTreeItemData *itemData = OPCUtils::CreateItemData<ReferenceTypeDesign>(NodeTypeReferenceType, &(*i), nodeItemId);
            m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
            m_treeOPCCtrl->SetItemImage(nodeItemId, IconDocumentType, wxTreeItemIcon_Normal);

			//Find the new item added to focus.
			if (   nodeAdded != 0
				&& nodeAdded == &(*i))
			{
				m_selectedItemId = nodeItemId;
			}

            if (!OPCUtils::IsUserNodeOwner(&(*i)))
                m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

            //Use their Symbolic Name to get the subtypes
            PopulateReferenceSubTypesTree(nodeItemId, elementSymName, false, nodeAdded);
        }
    }
}

void ModelTree::PopulateChildrenTree(const wxTreeItemId &parentId, NodeDesign *node,
                                     short int showChildrenMask, void *nodeAdded, bool userOwner)
{
    //Check if Node is a Method. Method is not allowed to have Children, so we should exit.
    if (OPCUtils::IsNodeMethod(parentId, this->m_treeOPCCtrl))
        return;

    wxTreeItemId childrenId = this->m_treeOPCCtrl->AppendItem(parentId, "Children");

    //Store the node so we can access it if we add children
    wxTreeItemData *itemDataChildrenRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeChildrenRoot, node, childrenId);
    m_treeOPCCtrl->SetItemData(childrenId, itemDataChildrenRoot);
    m_treeOPCCtrl->SetItemImage(childrenId, IconChildren, wxTreeItemIcon_Normal);
    if (!userOwner)
        m_treeOPCCtrl->SetItemTextColour(childrenId, OPCUtils::DARK_GRAY);

    wxTreeItemId objectRootId;
    wxTreeItemId variableRootId;
    wxTreeItemId propertyRootId;
    wxTreeItemId methodRootId;

    if (showChildrenMask & TREE_SHOW_CHILD_OBJECT)
    {
        //Object
        objectRootId = this->m_treeOPCCtrl->AppendItem(childrenId, "Object");
        wxTreeItemData *itemDataObjectRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeChildrenObjectRoot, node, objectRootId);
        m_treeOPCCtrl->SetItemData(objectRootId, itemDataObjectRoot);
        m_treeOPCCtrl->SetItemImage(objectRootId, IconFolderWhite, wxTreeItemIcon_Normal);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(objectRootId, OPCUtils::DARK_GRAY);
    }

    if (showChildrenMask & TREE_SHOW_CHILD_VARIABLE)
    {
        //Variable
        variableRootId = m_treeOPCCtrl->AppendItem(childrenId, _T("Variable"));
        wxTreeItemData *itemDataVariableRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeChildrenVariableRoot, node, variableRootId);
        m_treeOPCCtrl->SetItemData(variableRootId, itemDataVariableRoot);
        m_treeOPCCtrl->SetItemImage(variableRootId, IconFolderWhite, wxTreeItemIcon_Normal);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(variableRootId, OPCUtils::DARK_GRAY);
    }

    if (showChildrenMask & TREE_SHOW_CHILD_PROPERTY)
    {
        //Property
        propertyRootId = m_treeOPCCtrl->AppendItem(childrenId, _T("Property"));
        wxTreeItemData *itemDataPropertyRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeChildrenPropertyRoot, node, propertyRootId);
        m_treeOPCCtrl->SetItemData(propertyRootId, itemDataPropertyRoot);
        m_treeOPCCtrl->SetItemImage(propertyRootId, IconFolderWhite, wxTreeItemIcon_Normal);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(propertyRootId, OPCUtils::DARK_GRAY);

    }

    if (showChildrenMask & TREE_SHOW_CHILD_METHOD)
    {
        //Method
        methodRootId = m_treeOPCCtrl->AppendItem(childrenId, _T("Method"));
        wxTreeItemData *itemDataMethodRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeChildrenMethodRoot, node, methodRootId);
        m_treeOPCCtrl->SetItemData(methodRootId, itemDataMethodRoot);
        m_treeOPCCtrl->SetItemImage(methodRootId, IconFolderWhite, wxTreeItemIcon_Normal);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(methodRootId, OPCUtils::DARK_GRAY);

    }

    if(node->Children() == 0)
        return;

    //Object
    if (showChildrenMask & TREE_SHOW_CHILD_OBJECT)
        ITERATE_CHILDREN(Object, node, i)
    {
        wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(objectRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
        wxTreeItemData *itemData = OPCUtils::CreateItemData<ObjectDesign>(NodeTypeChildObject, &(*i), nodeItemId, node);
        m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        PopulateChildrenTree(nodeItemId,  &(*i), showChildrenMask, nodeAdded, userOwner);
        PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

        //Find the new item added to focus.
        if (   nodeAdded != 0
            && nodeAdded == &(*i))
        {
            m_selectedItemId = nodeItemId;
        }

        if (!OPCUtils::IsUserNodeOwner(&(*i)))
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        TypeDesign *objType = OPCUtils::GetObjectTypeDesign(this->m_model, &(*i));

        if (   objType != 0
            && OPCUtils::IsSameTypeDefinition(this->m_model, objType, "FolderType", NodeTypeObjectType))
            this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconFolderYellow, wxTreeItemIcon_Normal);
        else
             this->m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
    }

    //Variable
    if (showChildrenMask & TREE_SHOW_CHILD_VARIABLE)
        ITERATE_CHILDREN(Variable, node, i)
    {
        wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(variableRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
        wxTreeItemData *itemData = OPCUtils::CreateItemData<VariableDesign>(NodeTypeChildVariable, &(*i), nodeItemId, node);
        m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        PopulateChildrenTree(nodeItemId,  &(*i), showChildrenMask, nodeAdded, userOwner);
        PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

        //Find the new item added to focus.
        if (   nodeAdded != 0
            && nodeAdded == &(*i))
        {
            m_selectedItemId = nodeItemId;
        }

        if (!OPCUtils::IsUserNodeOwner(&(*i)))
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
    }

    //Property
    if (showChildrenMask & TREE_SHOW_CHILD_PROPERTY)
        ITERATE_CHILDREN(Property, node, i)
    {
        wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(propertyRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
        wxTreeItemData *itemData = OPCUtils::CreateItemData<PropertyDesign>(NodeTypeChildProperty, &(*i), nodeItemId, node);
        m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        PopulateChildrenTree(nodeItemId,  &(*i), showChildrenMask, nodeAdded, userOwner);
        PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

        //Find the new item added to focus.
        if (   nodeAdded != 0
            && nodeAdded == &(*i))
        {
            m_selectedItemId = nodeItemId;
        }

        if (!OPCUtils::IsUserNodeOwner(&(*i)))
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
    }

    //Method
    if (showChildrenMask & TREE_SHOW_CHILD_METHOD)
         ITERATE_CHILDREN(Method, node, i)
    {
        wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(methodRootId, OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName()));
        wxTreeItemData *itemData = OPCUtils::CreateItemData<MethodDesign>(NodeTypeChildMethod, &(*i), nodeItemId, node);
        m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        PopulateChildrenTree(nodeItemId,  &(*i), showChildrenMask, nodeAdded, userOwner);
        PopulateReferencesTree(nodeItemId, &(*i), nodeAdded, userOwner);

        //Find the new item added to focus.
        if (   nodeAdded != 0
            && nodeAdded == &(*i))
        {
            m_selectedItemId = nodeItemId;
        }

        if (!OPCUtils::IsUserNodeOwner(&(*i)))
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
    }
}

void ModelTree::PopulateReferencesTree(const wxTreeItemId& parentId, NodeDesign* node, void *nodeAdded, bool userOwner)
{
    //Check if Node is a Method. Method has no Reference, so we should exit.
    if (OPCUtils::IsNodeMethod(parentId, this->m_treeOPCCtrl))
        return;

    wxTreeItemId referencesId = this->m_treeOPCCtrl->AppendItem(parentId, "References");

    //Store the node so we can access it if we add references
    wxTreeItemData *itemDataReferencesRoot = OPCUtils::CreateItemData<NodeDesign>(NodeTypeReferencesRoot, node, referencesId);
    m_treeOPCCtrl->SetItemData(referencesId, itemDataReferencesRoot);
    m_treeOPCCtrl->SetItemImage(referencesId, IconReference, wxTreeItemIcon_Normal);
    if (!userOwner)
        m_treeOPCCtrl->SetItemTextColour(referencesId, OPCUtils::DARK_GRAY);

    if(node->References() == 0)
        return;

    ITERATE_REFERENCES(node, i)
    {
        wxTreeItemId nodeItemId  = m_treeOPCCtrl->AppendItem(referencesId, OPCUtils::GetStringFromQName(i->TargetId()));
        wxTreeItemData *itemData = OPCUtils::CreateItemData<Reference>(NodeTypeReference, &(*i), nodeItemId, node);
        m_treeOPCCtrl->SetItemData(nodeItemId, itemData);
        if (!userOwner)
            m_treeOPCCtrl->SetItemTextColour(nodeItemId, OPCUtils::DARK_GRAY);

        //Find the new item added to focus.
        if (   nodeAdded != 0
            && nodeAdded == &(*i))
        {
            m_selectedItemId = nodeItemId;
        }

        m_treeOPCCtrl->SetItemImage(nodeItemId, IconBallBlack, wxTreeItemIcon_Normal);
    }
}

void ModelTree::PropagateUpdate(string prevSymName, string newSymName,
                                std::string prevTargetId, std::string newTargetId,
                                bool userNodeOwner, const enum NodeType nodeUpdatedType)
{
    if (prevSymName == newSymName) //Skip if no changes made to the sym name.
        return;

    if (nodeUpdatedType == NodeTypeDataType)
        ITERATE_MODELLIST(DataType, dataType, m_model)
        {
            //Node being updated is a DataType: Update Sub Types
            string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(dataType->BaseType());
            if (elementBaseType == prevSymName)
                OPCUtils::SetBaseType(*dataType, newSymName, userNodeOwner);

            if (elementBaseType == "Structure") //Node being updated is a DataType:
            {                                   //Structure will have Fields that we need to check.
                                                //We will not worry about the BaseType name because it is
                                                //a special Type that will never change.
                for (ListOfFields::Field_iterator field(dataType->Fields()->Field().begin());
                     field != dataType->Fields()->Field().end();
                     ++field
                    )
                {
                    string fieldDataType = OPCUtils::GetName<Parameter::DataType_optional>(field->DataType());
                    if (fieldDataType == prevSymName)
                    {
                        if (newSymName == "")
                        {
                            /*
                            //We'll just have to delete it because it will cause an error in the compilation.
                            //TODO: Maybe we should ask first the user if it wants to delete even when there are using it.
                            method->InputArguments()->Argument().erase(i);
                            --i;
                            */

                            //Update to a BaseDataType when the dataType'd value has been deleted.
                            xml_schema::ncname nc("BaseDataType");
                            xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            field->DataType(dataTypeAtt);

                            //Update with an empty value when the dataType'd value has been deleted.
                            //    Parameter::DataType_optional dataTypeAtt;
                            //    i->DataType(dataTypeAtt);
                        }
                        else
                        {
                            xml_schema::ncname nc(newSymName);
                            //There's no need for prefix because we know only user node can be changed.
                            xml_schema::qname qn(nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            field->DataType(dataTypeAtt);
                        }
                    }
                }
            }
        }

    ITERATE_MODELLIST(ObjectType, objType, m_model)
    {
        //If the node being updated is an ObjectType, all the subtypes should get updated.
        if (nodeUpdatedType == NodeTypeObjectType)
        {
            string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(objType->BaseType());
            if (elementBaseType == prevSymName)
                OPCUtils::SetBaseType(*objType, newSymName, userNodeOwner);
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*objType));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*objType));
    }

    if (nodeUpdatedType == NodeTypeReferenceType)
        ITERATE_MODELLIST(ReferenceType, i, m_model)
        {
            //If the node being updated is a ReferenceType: Update all the subtypes.
            string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(i->BaseType());
            if (elementBaseType == prevSymName)
                OPCUtils::SetBaseType(*i, newSymName, userNodeOwner);
        }

    ITERATE_MODELLIST(VariableType, varType, m_model)
    {
        //Node being updated is a VariableType: Update all the subtypes.
        if (nodeUpdatedType == NodeTypeVariableType)
        {
            string elementBaseType = OPCUtils::GetName<TypeDesign::BaseType_optional>(varType->BaseType());
            if (elementBaseType == prevSymName)
                OPCUtils::SetBaseType(*varType, newSymName, userNodeOwner);
        }

        //If the node being updated is a DataType, update element DataType attribute.
        if (nodeUpdatedType == NodeTypeDataType)
        {
            string elementDataType = OPCUtils::GetName<VariableDesign::DataType_optional>(varType->DataType());
            if (elementDataType == prevSymName)
            {
                if (newSymName != "")
                {
                    xml_schema::ncname nc(newSymName);
                    //There's no need for prefix because we know only user node can be changed.
                    xml_schema::qname qn(nc);
                    varType->DataType(qn);
                }
                else
                {
                    //Update with an empty value when the dataType'd value has been deleted.
                    VariableTypeDesign::DataType_optional dt;
                    varType->DataType(dt);
                }
            }
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*varType));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*varType));
    }

    //If the node being updated is a DataType, check DataType referenced by all input and out parameters.
    if (nodeUpdatedType == NodeTypeDataType)
        ITERATE_MODELLIST(Method, method, m_model)
        {
            if (method->InputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator i(method->InputArguments()->Argument().begin());
                     i != method->InputArguments()->Argument().end();
                     ++i
                     )
                {
                    string parameterDataType = OPCUtils::GetName<Parameter::DataType_optional>(i->DataType());
                    if (parameterDataType == prevSymName)
                    {
                        if (newSymName == "")
                        {
                            /*
                            //We'll just have to delete it because it will cause an error in the compilation.
                            //TODO: Maybe we should ask first the user if it wants to delete even when there are using it.
                            method->InputArguments()->Argument().erase(i);
                            --i;
                            */

                            //Update to a BaseDataType when the dataType'd value has been deleted.
                            xml_schema::ncname nc("BaseDataType");
                            xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);

                            //Update with an empty value when the dataType'd value has been deleted.
                            //    Parameter::DataType_optional dataTypeAtt;
                            //    i->DataType(dataTypeAtt);
                        }
                        else
                        {
                            xml_schema::ncname nc(newSymName);
                            //There's no need for prefix because we know only user node can be changed.
                            xml_schema::qname qn(nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);
                        }
                    }
                }
            }

            if (method->OutputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator i(method->OutputArguments()->Argument().begin());
                     i != method->OutputArguments()->Argument().end();
                     ++i
                     )
                {
                    string parameterDataType = OPCUtils::GetName<Parameter::DataType_optional>(i->DataType());
                    if (parameterDataType == prevSymName)
                    {
                        if (newSymName == "")
                        {
                            /*
                            //We'll just have to delete it because it will cause an error in the compilation.
                            //TODO: Maybe we should ask first the user if it wants to delete even when there are using it.
                            method->OutputArguments()->Argument().erase(i);
                            --i;
                            */

                            //Update to a BaseDataType when the dataType'd value has been deleted.
                            xml_schema::ncname nc("BaseDataType");
                            xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);

                            //Update with an empty value when the dataType'd value has been deleted.
                            //    Parameter::DataType_optional dataTypeAtt;
                            //    i->DataType(dataTypeAtt);
                        }
                        else
                        {
                            xml_schema::ncname nc(newSymName);
                            //There's no need for prefix because we know only user node can be changed.
                            xml_schema::qname qn(nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);
                        }
                    }
                }
            }
        }

    ITERATE_MODELLIST(Object, obj, m_model)
    {
        //If the node being updated is an ObjectType, all the TypeDefinition(instance of ObjectType) referencing should get updated.
        if (nodeUpdatedType == NodeTypeObjectType)
        {
            string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(obj->TypeDefinition(), "");
            if (typeDef == prevSymName)
                OPCUtils::SetTypeDef(*obj, newSymName, userNodeOwner);
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*obj));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*obj));
    }
}

void ModelTree::PropagateUpdateChildren(string prevSymName, string newSymName,
                                        std::string prevTargetId, std::string newTargetId,
                                        bool userNodeOwner, const enum NodeType nodeUpdatedType,
                                        NodeDesign *nodeWithChildren)
{
    if(nodeWithChildren->Children() == 0)
        return;

    //Object
    ITERATE_CHILDREN(Object, nodeWithChildren, i)
    {
        //If the node being updated is an ObjectType, all the TypeDefinition(instance of ObjectType) referencing should get updated.
        if (nodeUpdatedType == NodeTypeObjectType)
        {
            string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(i->TypeDefinition(), "");
            if (typeDef == prevSymName)
                OPCUtils::SetTypeDef(*i, newSymName, userNodeOwner);
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
    }

    //Variable
    ITERATE_CHILDREN(Variable, nodeWithChildren, i)
    {
        //If the node being updated is an VariableType, all the TypeDefinition(instance of VariableType) referencing should get updated.
        if (nodeUpdatedType == NodeTypeVariableType)
        {
            string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(i->TypeDefinition(), "");
            if (typeDef == prevSymName)
                OPCUtils::SetTypeDef(*i, newSymName, userNodeOwner);
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
    }

    //Property
    ITERATE_CHILDREN(Property, nodeWithChildren, i)
    {
        //If the node being updated is a DataType, update element DataType attribute.
        if (nodeUpdatedType == NodeTypeDataType)
        {
            string elementDataType = OPCUtils::GetName<VariableDesign::DataType_optional>(i->DataType());
            if (elementDataType == prevSymName)
            {
                xml_schema::ncname nc(newSymName);
                //There's no need for prefix because we know only user node can be changed.
                xml_schema::qname qn(nc);
                i->DataType(qn);
            }
            else if (prevSymName == "")
            {
                //Update with an empty value when the dataType'd value has been deleted.
                PropertyDesign::DataType_optional dt;
                i->DataType(dt);
            }
        }

        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*i));
    }

    //Method
    ITERATE_CHILDREN(Method, nodeWithChildren, method)
    {
        //If the node being updated is a Method (virtual root), all the TypeDefinition(instance of Method) referencing should get updated.
        if (nodeUpdatedType == NodeTypeMethod)
        {
            string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(method->TypeDefinition(), "");
            if (typeDef == prevSymName)
                OPCUtils::SetTypeDef(*method, newSymName, userNodeOwner);
        }

        //If the node being updated is a DataType, check DataType referenced by all input and out parameters.
        if (nodeUpdatedType == NodeTypeDataType)
        {
            if (method->InputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator i(method->InputArguments()->Argument().begin());
                     i != method->InputArguments()->Argument().end();
                     ++i
                     )
                {
                    string parameterDataType = OPCUtils::GetName<Parameter::DataType_optional>(i->DataType());
                    if (parameterDataType == prevSymName)
                    {
                        if (newSymName == "")
                        {
                            /*
                            //We'll just have to delete it because it will cause an error in the compilation.
                            //TODO: Maybe we should ask first the user if it wants to delete even when there are using it.
                            method->InputArguments()->Argument().erase(i);
                            --i;
                            */

                            //Update to a BaseDataType when the dataType'd value has been deleted.
                            xml_schema::ncname nc("BaseDataType");
                            xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);

                            //Update with an empty value when the dataType'd value has been deleted.
                            //    Parameter::DataType_optional dataTypeAtt;
                            //    i->DataType(dataTypeAtt);
                        }
                        else
                        {
                            xml_schema::ncname nc(newSymName);
                            //There's no need for prefix because we know only user node can be changed.
                            xml_schema::qname qn(nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);
                        }
                    }
                }
            }

            if (method->OutputArguments() != 0)
            {
                for (ListOfArguments::Argument_iterator i(method->OutputArguments()->Argument().begin());
                     i != method->OutputArguments()->Argument().end();
                     ++i
                     )
                {
                    string parameterDataType = OPCUtils::GetName<Parameter::DataType_optional>(i->DataType());
                    if (parameterDataType == prevSymName)
                    {
                        if (newSymName == "")
                        {
                            /*
                            //We'll just have to delete it because it will cause an error in the compilation.
                            //TODO: Maybe we should ask first the user if it wants to delete even when there are using it.
                            method->OutputArguments()->Argument().erase(i);
                            --i;
                            */

                           //Update to a BaseDataType when the dataType'd value has been deleted.
                            xml_schema::ncname nc("BaseDataType");
                            xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);

                            //Update with an empty value when the dataType'd value has been deleted.
                            //    Parameter::DataType_optional dataTypeAtt;
                            //    i->DataType(dataTypeAtt);
                        }
                        else
                        {
                            xml_schema::ncname nc(newSymName);
                            //There's no need for prefix because we know only user node can be changed.
                            xml_schema::qname qn(nc);
                            Parameter::DataType_optional dataTypeAtt(qn);
                            i->DataType(dataTypeAtt);
                        }
                    }
                }
            }
        }
        PropagateUpdateChildren(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*method));
        PropagateUpdateReferences(prevSymName, newSymName, prevTargetId, newTargetId, userNodeOwner, nodeUpdatedType, &(*method));
    }
}

void ModelTree::PropagateUpdateReferences(string prevSymName, string newSymName,
                                          std::string prevTargetId, std::string newTargetId,
                                          bool userNodeOwner, const enum NodeType nodeUpdatedType,
                                          NodeDesign *nodeWithReferences)
{
    if(nodeWithReferences->References() != 0)
        ITERATE_REFERENCES(nodeWithReferences, i)
        {
            if (nodeUpdatedType == NodeTypeReferenceType)
            {
                string referenceType = OPCUtils::GetStringFromQName(i->ReferenceType());
                if (referenceType == prevSymName)
                {
                    if (newSymName == "")
                    {
                        //When Reference Type is deleted. Update it with its basetype.
                        xml_schema::ncname nc("References");
                        xml_schema::qname qn("http://opcfoundation.org/UA/", nc);
                        Reference::ReferenceType_type refType(qn);
                        i->ReferenceType(refType);

                        /*
                        //TODO: We will just delete the reference for now.
                        //      If we put null string or removed, the compiler will complain.
                        //      Maybe we should ask first the user if it wants to delete even when there are using it.
                        nodeWithReferences->References()->Reference().erase(i);
                        --i;
                        continue;
                        */


                        /*
                        xml_schema::ncname nc("null");
                        //There's no need for prefix because we know only user node can be changed.
                        xml_schema::qname qn(nc);
                        i->ReferenceType(qn);
                        */
                    }
                    else
                    {
                        xml_schema::ncname nc(newSymName);
                        //There's no need for prefix because we know only user node can be changed.
                        xml_schema::qname qn(nc);
                        i->ReferenceType(qn);
                    }
                }
            }

            //TODO: References should be (Object, Variable) instances. But if we allow it to be anything including Types,
            //      then we may have no way of checking specific NodeType here and we just allow for everything.
            string sTargetId = OPCUtils::GetStringFromQName(i->TargetId());
            if (sTargetId == prevTargetId)
            {
                if (newTargetId != "")
                {
                    Reference::TargetId_type targetId(newTargetId);
                    i->TargetId(targetId);
                }
                else
                {
                   //We have to erase the Reference as it will be an error to the compiler having it still.
                   nodeWithReferences->References()->Reference().erase(i);
                    --i;
                }
            }
        }
}

wxTreeItemId ModelTree::GetLastSelectedItem()
{
    return this->m_selectedItemId;
}
