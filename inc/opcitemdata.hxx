#ifndef OPCITEMDATA_H
#define OPCITEMDATA_H

#include <wx/treectrl.h>
#include "opcelement.hxx"
#include "opcglobal.h"

template <class T>
struct OPCItemData : public wxTreeItemData{
    OPCItemData(enum NodeType nodeType,
                OPCElement<T> element, wxTreeItemId itemId, void *data=0):  NodeType(nodeType), Element(element), ItemId(itemId), Data(data)
    {
    //Explicit empty;
    }
    OPCItemData(enum NodeType nodeType, wxTreeItemId itemId): NodeType(nodeType), Element(0), ItemId(itemId), Data(0)
    {
    //Explicit empty;
    }
    enum NodeType NodeType;
    OPCElement<T> Element;
    wxTreeItemId ItemId;
    void *Data; //Extra data for any purpose
};


#endif // OPCITEMDATA_H
