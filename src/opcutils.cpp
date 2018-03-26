#include "opcutils.h"
#include "synthesis/opc.hxx"
#include "simpleJSON/JSON.h"

#include <ctime>
#include <wx/treectrl.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/process.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/txtstrm.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/gdicmn.h>

using namespace std;

wxColour OPCUtils::DARK_GRAY(128, 128, 128);

wxTreeItemData* OPCUtils::CreateItemData(enum NodeType nodeType, wxTreeItemId itemId)
{
    return new OPCItemData<void>(nodeType, itemId);
}

string OPCUtils::GenerateStringId(const char* prefix)
{
    int static counter = 0;
    ++counter;

    time_t t;
    time(&t);   // get time now
    struct tm *now = localtime(&t);

    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%y%m%d%H%M%S", now);

    stringstream ss;
    ss  << prefix << "-" << timeStr << "-" << counter;

    return ss.str();
}

string OPCUtils::GetStringFromQName(const ::xml_schema::qname &qName)
{
    stringstream ss;
    ss << qName.name();
    return ss.str();
}

bool OPCUtils::IsSameTypeDefinition(ModelDesign *model, TypeDesign *type, const char* baseTypeToSearch, const NodeType nodeType)
{
    //Get the BaseType and search the actual object
    string typeBase = OPCUtils::GetName<TypeDesign::BaseType_optional>(type->BaseType(), "");
    string symName  = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(type->SymbolicName(), "");

    //Recursion will stop at the BaseObjectType
    //Compare the baseType if you're looking for is in fact the *itself
    //or its BaseType.
    if (   symName.compare(baseTypeToSearch) == 0
        || typeBase.compare(baseTypeToSearch) == 0)
        return true;
    else if(typeBase.compare("") == 0)
        return false;

    TypeDesign *parentType = 0;

    //wxLogMessage(wxString::Format("typeBase:%s symName:%s baseTypeToSearch:%s NodeType:%d", typeBase, symName, baseTypeToSearch, nodeType));
    if (nodeType == NodeTypeObjectType)
    {
        ITERATE_MODELLIST(ObjectType, i, model)
        {
            string typeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
            //Find the type that the subtype has typedef'd from.
            if (0 == typeSymName.compare(typeBase))
            {
                parentType = &(*i);
                break;
            }
        }
    }
    else if(nodeType == NodeTypeDataType)
    {
        ITERATE_MODELLIST(DataType, i, model)
        {
            string typeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
            //Find the type that the subtype has typedef'd from.
            if (0 == typeSymName.compare(typeBase))
            {
                parentType = &(*i);
                break;
            }
        }
    }
    else if(nodeType == NodeTypeVariableType)
    {

        VariableTypeDesign *variableType = dynamic_cast<VariableTypeDesign*>(type);
        if (variableType != 0)
        {
            wxString dataType = OPCUtils::GetName<VariableTypeDesign::DataType_optional>(variableType->DataType(), string(""));

            ITERATE_MODELLIST(DataType, i, model)
            {
                string typeSymName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(i->SymbolicName());
                //Find the type that the subtype has typedef'd from.
                if (0 == typeSymName.compare(dataType))
                {
                    parentType = &(*i);
                    break;
                }
            }
        }
    }
    if (   parentType != 0
        && parentType->BaseType() != 0)
        return OPCUtils::IsSameTypeDefinition(model, parentType, baseTypeToSearch, nodeType);

    return false;
}

TypeDesign* OPCUtils::GetObjectTypeDesign(ModelDesign *model, InstanceDesign *instance)
{
    TypeDesign *objType = 0;
    string typeDef = OPCUtils::GetName<InstanceDesign::TypeDefinition_optional>(instance->TypeDefinition());

    for (ModelDesign::ObjectType_iterator iobjType (model->ObjectType().begin());
         iobjType != model->ObjectType().end ();
         ++iobjType)
    {
        string symName = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(iobjType->SymbolicName());

        //Find the ObjectType that the Object has typedef'd from.
        if (0 == symName.compare(typeDef))
        {
           objType = &(*iobjType);
           break;
        }
    }

    return objType;
}

bool OPCUtils::IsNodeMethod(const wxTreeItemId& treeNodeId, wxTreeCtrl *treeOPCCtrl)
{
    wxTreeItemData *data        = treeOPCCtrl->GetItemData(treeNodeId);
    OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(data);
    return (pvData->NodeType == NodeTypeMethod);
}

bool OPCUtils::IsStringValidQName(wxWindow *control, std::string str, std::string ctrlName)
{
    int charVal = 0;
    if (str.length() > 0)
        charVal = static_cast<int>(str[0]);

    cout << ctrlName << " char:" << charVal << "\n";
    if(   str.length() == 0
       || str.find(' ') != string::npos
       || (!(   (charVal >= 'A' && charVal <= 'Z')
             || (charVal >= 'a' && charVal <= 'z')
             )
           )
       )
    {
        wxMessageBox(wxString::Format("%s is empty or has spaces or doesn't start with a character.", ctrlName), "Error");
        if (control != 0)
            control->SetFocus();

        return false;
    }

    return true;
}

bool OPCUtils::IsUserNodeOwner(NodeDesign *node)
{
    //Null node is assumed to be built-in types. Since all of the drop down boxes
    //are hard coded list, therefore the contents of the list are built-in types.
    if (node == 0)
        return false;

    stringstream nodeIdSS;
    nodeIdSS << node->StringId();
    return (nodeIdSS.str().find("node_owner=builtin") != 0);
}

bool OPCUtils::SetSymName(NodeDesign *node, std::string symName)
{
    if (!OPCUtils::IsStringValidQName(0, symName, "Symbolic Name"))
        return false;

    //Symbolic Name
    xml_schema::ncname nc(symName);
    xml_schema::qname qn(nc);
    if(node->SymbolicName() == 0)
    {
        NodeDesign::SymbolicName_optional sn(qn);
        node->SymbolicName(sn);
    }
    else
        node->SymbolicName(qn);

    return true;
}

void OPCUtils::SetBaseType(TypeDesign &type, string sBaseType, bool userOwner)
{
    if (sBaseType.length() > 0)
    {
        xml_schema::ncname nc(sBaseType);
        //TODO: Replace this with actual namespace instead of checking userOwner.
        //      Refer to wxTreeDialog.cpp for retrieving namespace from the element.
        xml_schema::qname qn((userOwner ? "" : "http://opcfoundation.org/UA/"), nc);
        if (type.BaseType() == 0)
        {
            TypeDesign::BaseType_optional baseType(qn);
            type.BaseType(baseType);
        }
        else
            type.BaseType(qn);
    }
}

void OPCUtils::SetTypeDef(InstanceDesign &instance, string sTypeDefinition, bool userOwner)
{
    if (sTypeDefinition.length() > 0)
    {
        xml_schema::ncname nc(sTypeDefinition);
        //TODO: Is there a way to get the prefix, instead of assumaing
        //      that is is a ua?
        xml_schema::qname qn((userOwner ? "" : "http://opcfoundation.org/UA/"), nc);
        if (instance.TypeDefinition() == 0)
        {
            InstanceDesign::TypeDefinition_optional typeDef(qn);
            instance.TypeDefinition(typeDef);
        }
        else
            instance.TypeDefinition(qn);
    }
    else
    {
        //Update with an empty value when the typedef'd value has been deleted.
        InstanceDesign::TypeDefinition_optional typeDef;
        instance.TypeDefinition(typeDef);
    }
}

OPCUtils::OPCUtils()
{
    //Intentionally empty.
}

wxImageList* OPCUtils::GetCommonImageList()
{
    wxImageList* imageList = new wxImageList(16, 16, 1);

    wxImage imageFolderHammer;
    imageFolderHammer.LoadFile("icons/folder-hammer.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageFolderHammer);

    wxImage imageBallGreen;
    imageBallGreen.LoadFile("icons/ball-green.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageBallGreen);

    wxImage imageFolderYellow;
    imageFolderYellow.LoadFile("icons/folder-yellow.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageFolderYellow);

    wxImage imageFolderWhite;
    imageFolderWhite.LoadFile("icons/folder-white.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageFolderWhite);

    wxImage imageReference;
    imageReference.LoadFile("icons/reference.bmp", wxBITMAP_TYPE_BMP);
    imageList->Add(imageReference);

    wxImage imageBallBlack;
    imageBallBlack.LoadFile("icons/ball-black.bmp", wxBITMAP_TYPE_BMP);
    imageList->Add(imageBallBlack);

    wxImage imageChildren;
    imageChildren.LoadFile("icons/children.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageChildren);

    wxImage imageNodeType;
    imageNodeType.LoadFile("icons/document-type.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageNodeType);

    wxImage imageHierarchy;
    imageHierarchy.LoadFile("icons/hierarchy.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageHierarchy);

    wxImage imageLetterE;
    imageLetterE.LoadFile("icons/letter-e.png", wxBITMAP_TYPE_PNG);
    imageList->Add(imageLetterE);

    return imageList;
}

string OPCUtils::GetTargetId(wxTreeItemId node, string targetId, wxTreeCtrl* treeOPCCtrl)
{
    //Retrieve the node data selected.
    wxTreeItemData *nodeData    = treeOPCCtrl->GetItemData(node);
    OPCItemData<void> *pvData   = reinterpret_cast<OPCItemData<void> *>(nodeData);
    wxTreeItemId parentNode     = treeOPCCtrl->GetItemParent(node);

    switch(pvData->NodeType)
    {
        //This means that they are a child and has a parent, so we continue
        //going up to their ancestors.
        case NodeTypeChildrenRoot:
        case NodeTypeChildrenObjectRoot:
        case NodeTypeChildrenVariableRoot:
        case NodeTypeChildrenPropertyRoot:
        case NodeTypeChildrenMethodRoot:
            {
            if (parentNode.IsOk())
                return OPCUtils::GetTargetId(parentNode, targetId, treeOPCCtrl);
            break;
            }

        case NodeTypeObjectType:
        case NodeTypeVariableType:
        case NodeTypeDataType:
        case NodeTypeReferenceType:
        case NodeTypeObject:
        case NodeTypeMethod:
        case NodeTypeChildObject:
        case NodeTypeChildVariable:
        case NodeTypeChildProperty:
        case NodeTypeChildMethod:
        {
            OPCItemData<NodeDesign> *pvElement  = reinterpret_cast<OPCItemData<NodeDesign> *>(nodeData);

            if (targetId.compare("") != 0)
                targetId = "_" + targetId;

            targetId = OPCUtils::GetName<NodeDesign::SymbolicName_optional>(pvElement->Element->SymbolicName()) + targetId;

            if (parentNode.IsOk())
            {
                wxTreeItemData *parentNodeData        = treeOPCCtrl->GetItemData(parentNode);
                OPCItemData<void> *parentNodePvData   = reinterpret_cast<OPCItemData<void> *>(parentNodeData);

                if (parentNodePvData != 0)
                {
                    //We know that this node is still a child because the parent is a rppt.
                    //So we keep on appending the ancestors.
                    if (   parentNodePvData->NodeType == NodeTypeChildrenRoot
                        || parentNodePvData->NodeType == NodeTypeChildrenObjectRoot
                        || parentNodePvData->NodeType == NodeTypeChildrenVariableRoot
                        || parentNodePvData->NodeType == NodeTypeChildrenPropertyRoot
                        || parentNodePvData->NodeType == NodeTypeChildrenMethodRoot
                        )
                        return OPCUtils::GetTargetId(parentNode, targetId, treeOPCCtrl);
                }
            }

            break;
        }
        default:
            ;
            //Do nothing
    }

    return targetId;
}

string OPCUtils::NodeTypeToString(enum NodeType nodeType)
{
    string nodeTypeString;
    switch(nodeType)
    {
        case NodeTypeRoot:
            nodeTypeString = "NodeTypeRoot";
            break;
        case NodeTypeObjectTypeRoot:
            nodeTypeString = "NodeTypeObjectTypeRoot";
            break;
        case NodeTypeObjectType:
            nodeTypeString = "NodeTypeObjectType";
            break;
        case NodeTypeVariableTypeRoot:
            nodeTypeString = "NodeTypeVariableTypeRoot";
            break;
        case NodeTypeVariableType:
            nodeTypeString = "NodeTypeVariableType";
            break;
        case NodeTypeReferenceTypeRoot:
            nodeTypeString = "NodeTypeReferenceTypeRoot";
            break;
        case NodeTypeReferenceType:
            nodeTypeString = "NodeTypeReferenceType";
            break;
        case NodeTypeDataTypeRoot:
            nodeTypeString = "NodeTypeDataTypeRoot";
            break;
        case NodeTypeDataType:
            nodeTypeString = "NodeTypeDataType";
            break;
        case NodeTypeStructDataType:
            nodeTypeString = "NodeTypeStructDataType";
            break;
        case NodeTypeEnumDataType:
            nodeTypeString = "NodeTypeEnumDataType";
            break;
        case NodeTypeMethodRoot:
            nodeTypeString = "NodeTypeMethodRoot";
            break;
        case NodeTypeMethod:
            nodeTypeString = "NodeTypeMethod";
            break;
        case NodeTypeObjectRoot:
            nodeTypeString = "NodeTypeObjectRoot";
            break;
        case NodeTypeObject:
            nodeTypeString = "NodeTypeObject";
            break;
        case NodeTypeChildrenRoot:
            nodeTypeString = "NodeTypeChildrenRoot";
            break;
        case NodeTypeChildrenObjectRoot:
            nodeTypeString = "NodeTypeChildrenObjectRoot";
            break;
        case NodeTypeChildObject:
            nodeTypeString = "NodeTypeChildObject";
            break;
        case NodeTypeChildrenVariableRoot:
            nodeTypeString = "NodeTypeChildrenVariableRoot";
            break;
        case NodeTypeChildVariable:
            nodeTypeString = "NodeTypeChildVariable";
            break;
        case NodeTypeChildrenPropertyRoot:
            nodeTypeString = "NodeTypeChildrenPropertyRoot";
            break;
        case NodeTypeChildProperty:
            nodeTypeString = "NodeTypeChildProperty";
            break;
        case NodeTypeChildrenMethodRoot:
            nodeTypeString = "NodeTypeChildrenMethodRoot";
            break;
        case NodeTypeChildMethod:
            nodeTypeString = "NodeTypeChildMethod";
            break;
        case NodeTypeReferencesRoot:
            nodeTypeString = "NodeTypeReferencesRoot";
            break;
        case NodeTypeReference:
            nodeTypeString = "NodeTypeReference";
            break;
        default:
            nodeTypeString = "Unknown Node Type:" + nodeType;
    }

    return nodeTypeString;
}

bool OPCUtils::GithubConnect(wxString username, wxString password,
                             wxString gitCmd,
                             JSONValue **jsonValue)
{
    bool retVal = false;

    wxProcess *proc = new wxProcess(wxPROCESS_REDIRECT);
    wxFileName fCompiler(wxStandardPaths::Get().GetExecutablePath());
    wxString cmd = wxString::Format("%scurl -s -u %s:%s %s",
                                    fCompiler.GetPathWithSep(),
                                    username, password,
                                    gitCmd);

    // If flags contain wxEXEC_SYNC, return -1 on failure and the exit code of the
    // process if everything was ok. Otherwise (i.e. if wxEXEC_ASYNC), return 0 on
    // failure and the PID of the launched process if ok.
    long procRetVal = wxExecute(cmd, wxEXEC_ASYNC, proc);
    wxLogMessage("wxLogin::OnbtnOKClick() Username:", username);
    cout << "cmd:" << cmd <<"\n";
    if (procRetVal == 0)
        wxLogMessage("Error executing curl Username:", username);
    else
    {
        proc->Redirect();

        wxInputStream* stdOut = proc->GetInputStream();
        wxTextInputStream txtStreamStdOut(*stdOut);
        wxString strReturn;
        while(!stdOut->Eof())
            strReturn = strReturn + txtStreamStdOut.ReadLine();

        if (strReturn != "")
        {
            *jsonValue = JSON::Parse(static_cast<const char*>(strReturn.c_str()));
            if (!(*jsonValue)->IsObject())
                wxLogMessage("JSON not an object. Failed to parse github ret value:%s", strReturn);
            else
                retVal = true;
        }
        else
            ::wxMessageBox("Failed to connect. Check your internet connection.", "Error");
    }

    return retVal;
}
