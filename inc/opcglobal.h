#ifndef OPCGLOBAL_H
#define OPCGLOBAL_H

//Make sure to update OPCUtils::NodeTypeToString when there is a change with enum NodeType.
enum NodeType{
    /* Tree structure: START */
    NodeTypeRoot = 0,
        NodeTypeObjectTypeRoot,
            NodeTypeObjectType,
        NodeTypeVariableTypeRoot,
            NodeTypeVariableType,
        NodeTypeReferenceTypeRoot,
            NodeTypeReferenceType,
        NodeTypeDataTypeRoot,
            NodeTypeDataType,

            NodeTypeStructDataType,
            NodeTypeEnumDataType,

        NodeTypeMethodRoot,
            NodeTypeMethod,
        NodeTypeObjectRoot,
            NodeTypeObject,
    /* Tree structure: END */



    /* Children And References are part composition of any non-Root Node. */
    NodeTypeChildrenRoot,
        NodeTypeChildrenObjectRoot,
            NodeTypeChildObject,
        NodeTypeChildrenVariableRoot,
            NodeTypeChildVariable,
        NodeTypeChildrenPropertyRoot,
            NodeTypeChildProperty,
        NodeTypeChildrenMethodRoot,
            NodeTypeChildMethod,

    NodeTypeReferencesRoot,
        NodeTypeReference,

};

enum MenuPopup
{
    MenuPopup_ID_ADD,
    MenuPopup_ID_EDIT,
    MenuPopup_ID_DEL,
    MenuPopup_ID_GOTO_NODE,
    MenuPopup_ID_MOVE_UP,
    MenuPopup_ID_MOVE_DOWN,
    MenuPopup_ID_OTHERS,
};

enum Icon
{
    IconFolderWithHammer = 0,
    IconBallGreen,
    IconFolderYellow,
    IconFolderWhite,
    IconReference,
    IconBallBlack,
    IconChildren,
    IconDocumentType,
    IconStructType,
    IconEnumType,
};

//Tree Children selection values for showing individual child.
//TODO: Change this to enum
#define TREE_SHOW_CHILD_OBJECT     1
#define TREE_SHOW_CHILD_VARIABLE   2
#define TREE_SHOW_CHILD_PROPERTY   4
#define TREE_SHOW_CHILD_METHOD     8
#define TREE_SHOW_CHILD_FIELD     16

enum RootMask
{
   RootMaskShowDataType         =  1,
   RootMaskShowEventType        =  2,
   RootMaskShowObjectType       =  4,
   RootMaskShowReferenceType    =  8,
   RootMaskShowVariableType     = 16,
   RootMaskShowMethod           = 32,
   RootMaskShowObject           = 64,
};

#define NO_VALUE "<not present>"


#define MODEL_TEMPLATE_FILENAME "new_model_template.xml"
#define MODEL_BUILTIN_FILENAME  "model_builtin.xml"

#define ITERATE_MODELLIST(TYPENAME, ITER, MODEL)    for (ModelDesign::TYPENAME##_iterator ITER(MODEL->TYPENAME().begin());                          \
                                                         ITER != MODEL->TYPENAME().end();                                                           \
                                                         ++ITER)

#define ITERATE_FROM_CHILDREN(TYPENAME, CHILDREN, ITER) for (ListOfChildren::TYPENAME##_iterator ITER(CHILDREN->TYPENAME().begin());                \
                                                             ITER != CHILDREN->TYPENAME().end();                                                    \
                                                             ++ITER)

#define ITERATE_CHILDREN(TYPENAME, PARENTNODE, ITER) for (ListOfChildren::TYPENAME##_iterator ITER(PARENTNODE->Children()->TYPENAME().begin());     \
                                                          ITER != PARENTNODE->Children()->TYPENAME().end();                                         \
                                                          ++ITER)

#define ITERATE_REFERENCES( PARENTNODE, ITER)   for (ListOfReferences::Reference_iterator ITER(PARENTNODE->References()->Reference().begin());      \
                                                     ITER != PARENTNODE->References()->Reference().end();                                           \
                                                     ++ITER)
#endif // OPCGLOBAL_H
