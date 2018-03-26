#ifndef OPCUTILS_H
#define OPCUTILS_H

#include <opcglobal.h>
#include <opcelement.hxx>
#include <opcitemdata.hxx>
#include <synthesis/opc.hxx>
#include <sstream>

class wxTreeItemData;
class wxImageList;
class wxWindow;
class wxString;
class wxTreeCtrl;
class JSONValue;

class OPCUtils
{
private:
    OPCUtils();

public: //static public methods

    static OPCUtils *GetInstance();

    template <class T>
    static wxTreeItemData *CreateItemData(enum NodeType nodeType, OPCElement<T> elementValue, wxTreeItemId itemId, void *data=0)
    {
        return new OPCItemData<T>(nodeType, elementValue, itemId, data);
    }

    static wxTreeItemData *CreateItemData(enum NodeType nodeType, wxTreeItemId itemId);

    template <class T>
    static std::string GetName(const T &objPtr, std::string defaultVal=NO_VALUE)
    {
        std::string name;

        if (   objPtr != 0
            && &objPtr->name() != 0)
        {
            std::stringstream ss;
            ss << objPtr->name();
            name = ss.str();
        }
        else
            name = defaultVal;

        return name;
    }

    static std::string GenerateStringId(const char *prefix);

    static std::string GetStringFromQName(const ::xml_schema::qname &qName);

    template <class T>
    static std::string GetString(T &obj)
    {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    }

    //Recursively check whether the root parent is the same as the type
    static bool IsSameTypeDefinition(ModelDesign *model, TypeDesign *type, const char* baseType, const NodeType nodeType);

    static TypeDesign* GetObjectTypeDesign(ModelDesign *model, InstanceDesign *instance);

    static bool IsNodeMethod(const wxTreeItemId& treeNodeId, wxTreeCtrl *treeOPCCtrl);

    static bool IsStringValidQName(wxWindow *control, std::string str, std::string ctrlName);

    static bool IsUserNodeOwner(NodeDesign *node);

    static bool SetSymName(NodeDesign *node, std::string symName);

    static void SetBaseType(TypeDesign &objType, std::string sBaseType, bool userOwner);

    static void SetTypeDef(InstanceDesign &instance, std::string sTypeDefinition, bool userOwner);

    static wxImageList* GetCommonImageList();

    static wxColour * GetDarkGray();

    static std::string GetTargetId(wxTreeItemId node, std::string targetId, wxTreeCtrl* treeOPCCtrl);

    static std::string NodeTypeToString(enum NodeType nodeType);

    //@param jsonValue should be deleted by the caller
    static bool GithubConnect(wxString username, wxString password, wxString gitCmd, JSONValue **jsonValue);

public:
    static wxColour DARK_GRAY;//(128, 128, 128);
};

#endif // OPCUTILS_H
