#ifndef MODELTREE_H
#define MODELTREE_H

#include <opcglobal.h>

#include <string>
#include <memory>
#include <map>

#include "wx/treebase.h"

class ModelDesign;
class NodeDesign;
class wxTreeCtrl;

class ModelTree
{
    public:
        ModelTree(wxTreeCtrl *treeOPCCtrl);
        ~ModelTree();

    public:
        //The main opc elements root nodes are created with their Children and References recursively constructed.
        //Other nodes children and references are created dynamically when the node is clicked/selected.
        void CreateTree(ModelDesign* model,
                        bool showChildren = true,
                        bool showReferences = true,
                        void *nodeAdded = 0,
                        int showRootMask =(  RootMaskShowDataType
                                             | RootMaskShowEventType
                                             | RootMaskShowObjectType
                                             | RootMaskShowReferenceType
                                             | RootMaskShowVariableType
                                             | RootMaskShowMethod
                                             | RootMaskShowObject)
        );

         //Recursively create the sub-tree of the node for the children
        void PopulateChildrenTree(const wxTreeItemId &parentId, NodeDesign *node,
                                short int showChildrenMask, void *nodeAdded, bool userOwner);

        //Recursively create the sub-tree of the node for the children
        void PopulateReferencesTree(const wxTreeItemId &parentId, NodeDesign *node, void *nodeAdded, bool userOwner);

        //Update all nodes referencing(Children, Reference) the node updated.
        //@param userNodeOwner - TODO: We may need to remove this. We know it
        //                             is always going to be a userNode because we don't allow
        //                             changes for built-in.
        void PropagateUpdate(std::string prevSymName, std::string newSymName,
                             std::string prevTargetId, std::string newTargetId,
                             bool userNodeOwner, const enum NodeType nodeUpdatedType);
        void PropagateUpdateChildren(std::string prevSymName, std::string newSymName,
                                     std::string prevTargetId, std::string newTargetId,
                                     bool userNodeOwner, const enum NodeType nodeUpdatedType,
                                     NodeDesign *nodeWithChildren);
        void PropagateUpdateReferences(std::string prevSymName, std::string newSymName,
                                       std::string prevTargetId, std::string newTargetId,
                                       bool userNodeOwner, const NodeType nodeUpdatedType,
                                       NodeDesign *nodeWithReferences);
        wxTreeItemId GetLastSelectedItem();
    private:
		//Recursively create the sub-tree of the ObjectType.
        void PopulateObjectSubTypesTree(const wxTreeItemId &parentId, std::string baseType, bool setParentItemData,
                                        std::map<std::string, std::string> &excludeTypeList, short int showChildrenMask,
                                        bool showChildren, bool showReferences, void *nodeAdded);

		//Recursively create the sub-tree of the ObjectType.
        void PopulateVariableSubTypesTree(const wxTreeItemId &parentId, std::string baseType, bool setParentItemData,
                                          bool showChildren, bool showReferences, void *nodeAdded);

        //Recursively create the sub-tree of the DataType.
        void PopulateDataSubTypesTree(const wxTreeItemId &parentId, std::string baseType, bool setParentItemData,
                                      void *nodeAdded);

        //Recursively create the sub-tree of the ReferenceType.
        void PopulateReferenceSubTypesTree(const wxTreeItemId &parentId, std::string baseType, bool setParentItemData,
                                           void *nodeAdded);

    private:
        ModelDesign* m_model;
        wxTreeCtrl *m_treeOPCCtrl;
        wxTreeItemId m_selectedItemId;
};

#endif // MODELTREE_H
