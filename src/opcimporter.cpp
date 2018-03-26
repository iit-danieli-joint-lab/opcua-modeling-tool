#include "opcimporter.h"
#include "opcglobal.h"
#include "xmlreader.h"

#include "wx/filename.h"
#include "wx/dir.h"
#include "wx/stdpaths.h"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <fstream>
#include <iostream>
#include <list>

using namespace std;
using namespace xercesc;

//TODO: UMXModelManager

OPCImporter::OPCImporter()
{
    //ctor
}

OPCImporter::~OPCImporter()
{
    //dtor
}

std::string OPCImporter::GetMergedFile()
{
    //Since we want an absolute path of the temp merged file location, and not relative, then
    //we have to convert it because code synthesis requires a URL.
    string url = m_mergedFile;
    for (size_t i = 0; i < url.length(); ++i)
    {
        if (url[i] == '\\')
              url[i] = '/';
    }
    url = "file:///" +  url; //NB: In windows, we need to add the third / in the file:// to make the vol as the root directory.
                             //    In linux, there's no need to add the 3rd because an absolute path starts with a / already.

    return url;
}

DOMNode* OPCImporter::GetDOM(const char* filename, XMLReader& reader) throw(wxString)
{
    try
    {
        DOMNode *inhertiedDocRootNode = reader.OpenXmlDOM(filename);

        if (inhertiedDocRootNode == 0)
            throw;

        return inhertiedDocRootNode;
    }catch(...)
    {
        throw wxString::Format("Error: Opening Inherited XML: %s", filename);
    }
}

void OPCImporter::MergeInherited(DOMElement* rootElement, DOMLSSerializer* mainSerializer,
                                 const char* rootElementFilename, XMLReader &mainRootElementXMLReader,
                                 DOMNode* mainDocRootNode)
{
        XMLCh *namespaceTag = XMLString::transcode("Namespace"); //
        XMLCh *namespaceURI = XMLString::transcode("http://opcfoundation.org/UA/ModelDesign.xsd");
        xercesc::DOMNodeList* namespaceList = rootElement->getElementsByTagNameNS(namespaceURI, namespaceTag);

        const XMLSize_t nsListNodeCount = namespaceList->getLength() ;
        for( XMLSize_t ix = 0; ix < nsListNodeCount; ++ix ){
            DOMElement* currentElement = dynamic_cast<DOMElement*>(namespaceList->item(ix));

            char *ns = xercesc::XMLString::transcode(mainSerializer->writeToString(currentElement));
            XMLString::release(&ns);

            XMLCh *filePathCh = XMLString::transcode("FilePath");
            DOMAttr *filePathAttr = currentElement->getAttributeNode(filePathCh);
            XMLString::release(&filePathCh);
            if (filePathAttr == 0)
                continue;

            const XMLCh *filePathAttrVal = filePathAttr->getValue();
            if (filePathAttrVal == 0)
                continue;

            char* filePath = XMLString::transcode(filePathAttrVal);
            wxString sFilePath = wxString(filePath);
            XMLString::release(&filePath);

            XMLReader readerInherited;
            wxFileName fUMX(rootElementFilename);
            wxFileName fInherited(fUMX.GetPath(), sFilePath);
            if (!fInherited.Exists())
            {
                fInherited.SetExt("xml");
                if (!fInherited.Exists())
                {
                    cerr << "THROW: Could not find Namespace FilePath:" << sFilePath << "\n";
                    throw wxString::Format("Error: Could not find Namespace FilePath:%s", sFilePath);
                }
            }


            DOMNode *inheritedDOM = GetDOM(fInherited.GetFullPath(), readerInherited);
            DOMElement* inheritedRootElement = dynamic_cast<DOMElement*>(inheritedDOM);
            //Recursively merge inherited namespaces. This will allow multi-level inheritance.
            MergeInherited(inheritedRootElement, mainSerializer, fInherited.GetFullPath(),
                           mainRootElementXMLReader, mainDocRootNode);

            /* Merged the inherited DOM */
            xercesc::DOMNodeList* children = inheritedDOM->getChildNodes();
            const XMLSize_t nodeCount = children->getLength() ;
            for( XMLSize_t ix = 0; ix < nodeCount; ++ix)
            {
                xercesc::DOMNode* currentNode = children->item(ix) ;
                try
                {
                    const XMLCh *chNodeName = currentNode->getLocalName();
                    char* nodeName = XMLString::transcode(chNodeName);
                    wxString sNodeName = nodeName;
                    XMLString::release(&nodeName);

                    const XMLCh *chNodeNS = currentNode->getNamespaceURI();
                    wxString sNodeNS;
                    if (chNodeNS != 0)
                    {
                        char* nodeNS = XMLString::transcode(chNodeNS);
                        sNodeNS = nodeNS;
                        XMLString::release(&nodeNS);
                    }

                    cout << "Reading element:" << sNodeName << " ns:" << sNodeNS << "\n";

                    //TODO: Skip inherited Namespaces for now.
                    //      I think we need to merge the inherited namespaces and mark it as node_owner=builtin.
                    //      When we merge namespaces, make sure those existing in the map should not be overwritten.
                    if (    sNodeName.compare("Namespaces") == 0
                        &&  sNodeNS.compare("http://opcfoundation.org/UA/ModelDesign.xsd") == 0)
                        continue;

                    DOMNode *importedNode = mainRootElementXMLReader.GetDocument()->importNode(currentNode, true);
                    /* Add a StringId attribute to the inherited node because we don't allow it to be modified from the current project. */
                    if( DOMNode::ELEMENT_NODE == currentNode->getNodeType()) //We have to make sure that is an element node as everything is a node, otherwise we may add an attribute to a blank line #text type which will crash.
                    {

                        DOMElement* importedElement = dynamic_cast<DOMElement*>(importedNode);
                        importedElement->setAttribute(XMLString::transcode("StringId"), XMLString::transcode("node_owner=builtin"));
                        char *inheritedNodeString = xercesc::XMLString::transcode(mainSerializer->writeToString(importedNode));
                        XMLString::release(&inheritedNodeString);
                    }

                    /*Append the element to the one and only main xml project. */
                    mainDocRootNode->appendChild(importedNode);
                }catch(DOMException &ex)
                {
                    char* message = XMLString::transcode(ex.msg);
                    cerr << "DOMNode::appendChild Exception message is: \n"
                         << message << "\n";
                    XMLString::release(&message);
                }
            }

        }
        XMLString::release(&namespaceURI);
        XMLString::release(&namespaceTag);
}

bool OPCImporter::MergeUMXToBuiltInTypes(const char* umxFilename, wxString& errorOut,
                                         std::map<std::string, std::string>& modelNSInfoMap)
{
    bool success = false;

    m_mergedFile = "";
    std::ofstream mergedOutFile;

    DOMLSSerializer *serializer = 0;
    DOMNode *docBuiltinRootNode = 0;
    DOMNode *docUMXRootNode     = 0;
    XMLCh *ls                   = 0;
    try
    {
        XMLReader readerBuiltin;
        DOMNode *docBuiltinRootNode  = readerBuiltin.OpenXmlDOM(MODEL_TEMPLATE_FILENAME);

        XMLReader readerUMX;
        DOMNode *docUMXRootNode      = readerUMX.OpenXmlDOM(umxFilename);

        if (docUMXRootNode == 0)
            throw _("Error: Opening the XML Built-in types.");

        if (docBuiltinRootNode == 0)
            throw _("Error: Opening the XML project.");


        /****************************************************************************/
        /* Initialize */
        //Return the first registered implementation that has the desired features.
        //In this case, we are after a DOM implementation that has the LS feature... or Load/Save.
        ls = XMLString::transcode("LS");
        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(ls);

        // Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
        serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();
        /****************************************************************************/




        /****************************************************************************/
        /* Saved all the namespace attributes of the ModelDesign element.
         * We will use this to create a namespace_infomap during saving/serializing */
        modelNSInfoMap.clear();
        const DOMNamedNodeMap *namespaceInfoMap = docUMXRootNode->getAttributes();
        const XMLSize_t nsMapCount = namespaceInfoMap->getLength();
        for( XMLSize_t ix = 0; ix < nsMapCount; ++ix)
        {
            xercesc::DOMNode* currentNode = namespaceInfoMap->item(ix);

            char *ns = XMLString::transcode(serializer->writeToString(currentNode));
            wxString sNS = ns;
            XMLString::release(&ns);

            char *nodeName = XMLString::transcode(currentNode->getNodeName());
            wxString sNodeName = nodeName;
            XMLString::release(&nodeName);

            char *nodeValue = XMLString::transcode(currentNode->getNodeValue());
            wxString sNodeValue = nodeValue;
            XMLString::release(&nodeValue);

            int indexFound = sNodeName.find("xmlns:"); //Ignore the default namespace (xmnls without a colon).
            if (indexFound >= 0)
            {
                wxString nsPrefix = sNodeName.substr(indexFound + strlen("xmlns:"), sNodeName.Len());
                //Ignore the standard namespaces that we will set all the time.
                if (! (   nsPrefix.Cmp(_("ua"))  == 0
                       || nsPrefix.Cmp(_("opc")) == 0
                       || nsPrefix.Cmp(_("uax")) == 0
                       || nsPrefix.Cmp(_("xsd")) == 0
                       || nsPrefix.Cmp(_("xsi")) == 0) )
                {
                    cout << "MapInfo Namespace: [" << sNodeName << "]"
                            << "sNodeName Len:" << sNodeName.Len() << " indexFound:" << indexFound
                            << " ns prefix:" << nsPrefix
                            << " value:" << sNodeValue.ToStdString() << " element text: " << sNS.ToStdString() << "\n";
                    modelNSInfoMap[nsPrefix.ToStdString()] = sNodeValue.ToAscii();
                }
            }
        }
        /****************************************************************************/




        /****************************************************************************/
        /* Merge the Built-in OPC Types */
        xercesc::DOMNodeList* children = docBuiltinRootNode->getChildNodes();
        const XMLSize_t nodeCount = children->getLength() ;
        for( XMLSize_t ix = 0; ix < nodeCount; ++ix){
            xercesc::DOMNode* currentNode = children->item(ix) ;
            try
            {
                DOMNode *importedNode = readerUMX.GetDocument()->importNode(currentNode, true);
                docUMXRootNode->appendChild(importedNode);
            }catch(DOMException &ex)
            {
                char* message = XMLString::transcode(ex.msg);
                cerr << "DOMNode::appendChild Exception message is: \n"
                     << message << "\n";
                XMLString::release(&message);
            }
        }
        /****************************************************************************/




        /****************************************************************************/
        /* Merge all namespaces xml files required in this project. These usually are the inherited types. */
        DOMElement* umxRootElement = dynamic_cast<DOMElement*>(docUMXRootNode);
        MergeInherited(umxRootElement, serializer, umxFilename, readerUMX, docUMXRootNode);
        /****************************************************************************/




        /****************************************************************************/
        /* Write the updated umx DOM to a temp file which will be opened by the ModelDesign */
        char *documentText = xercesc::XMLString::transcode(serializer->writeToString(readerUMX.GetDocument()));
        wxString sDocText = documentText;
        XMLString::release(&documentText);
        std::ofstream mergedOutFile;

        wxFileName filename(wxStandardPaths::Get().GetTempDir(), "umx_merged.xml");
        m_mergedFile = filename.GetFullPath();
        mergedOutFile.open(filename.GetFullPath());
        mergedOutFile << sDocText.ToStdString() << "\n";
        mergedOutFile.close();

        success = true;
    }
    catch(wxString &err)
    {
        cerr << "OPCImporter::MergeUMXToBuiltInTypes Error1: " << err << "\n";
        errorOut = err;
    }
    catch(...)
    {
        cerr << "OPCImporter::MergeUMXToBuiltInTypes Error: Failed to open " << umxFilename << "\n";
        errorOut = wxString::Format("Failed to open %s. Error parsing.", umxFilename);
    }

    if (serializer != 0)
        serializer->release();

    if (docBuiltinRootNode != 0)
        docBuiltinRootNode->release();

    if (docUMXRootNode != 0)
        docUMXRootNode->release();

    XMLString::release(&ls);

    return success;
}

//TODO: Check if Import is affected with changes to the MergeUMXToBuiltInTypes()
bool OPCImporter::Import(const char* importFilename)
{
    bool success = false;

    m_mergedFile = "";

    std::ofstream outFile;
    std::ifstream inFile;

    DOMLSSerializer *serializer = 0;
    XMLCh *ls                   = 0;
    try
    {
        XMLReader readerImport;
        DOMNode *docImportRootNode  = readerImport.OpenXmlDOM(importFilename);;

        if (docImportRootNode == 0)
            return false;

        //Return the first registered implementation that has the desired features.
        //In this case, we are after a DOM implementation that has the LS feature... or Load/Save.
        ls = XMLString::transcode("LS");
        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(ls);

        // Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
        serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();

        wxFileName filename(wxStandardPaths::Get().GetTempDir(), "umx_merged.xml");
        m_mergedFile = filename.GetFullPath();
        outFile.open(filename.GetFullPath());
        inFile.open(MODEL_TEMPLATE_FILENAME);

        std::string line;
        bool endOfModelDesignElement = false;
        const char *importMarker = "<!-- IMPORT MARKER -->";
        while (std::getline(inFile, line))
        {
            outFile << line << "\n";

            //Insert the imported file content after the ModelDesign element.
            if (  !endOfModelDesignElement
               && line.compare(importMarker) == 0)
            {
                endOfModelDesignElement = true;

                //Loop all the children
                xercesc::DOMNodeList* children = docImportRootNode->getChildNodes();
                const XMLSize_t nodeCount = children->getLength() ;
                for( XMLSize_t ix = 0; ix < nodeCount; ++ix )
                {
                    xercesc::DOMNode* currentNode = children->item(ix) ;
                    char *childNodeString = xercesc::XMLString::transcode(serializer->writeToString(currentNode));
                    outFile << childNodeString << "\n";
                    XMLString::release(&childNodeString);
                }
            }
        }
        success = true;
    }catch (...)
    {
        cerr << "OPCImporter Error: Failed to merge import and template file.\n";
    }

    try{
        outFile.close();
    }catch(...)
    {
        cerr << "OPCImporter Error: Failed to close outFile.\n";
    }

    try{
        inFile.close();
    }catch(...)
    {
        cerr << "OPCImporter Error: Failed to close inFile.\n";
    }

    if (serializer != 0)
        delete serializer;

    XMLString::release(&ls);

    return success;
}
