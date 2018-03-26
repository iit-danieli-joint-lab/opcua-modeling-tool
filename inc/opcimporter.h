#ifndef OPCIMPORTER_H
#define OPCIMPORTER_H

#include "wx/string.h"

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

#include <map>
#include <memory>
#include <string>

class XMLReader;
class OPCImporter
{
    public:
        OPCImporter();
        ~OPCImporter();

    public:

        /*
        1.) Parse the xml file to import.
        2.) Open the default template as a text file.
        3.) Extract the default template until the mark for the import.
        4.) Extract the children of the root element file imported.
        5.) Continue extracting the default template where it left off.
        4.) Open the temporary merged file where all the extracted values were saved.
        */
        bool Import(const char* importFilename);

        bool MergeUMXToBuiltInTypes(const char* umxFilename, wxString& errorOut,
                                    std::map<std::string, std::string>& modelNSInfoMap);

        std::string GetMergedFile();

    private:
        xercesc::DOMNode* GetDOM(const char* filename, XMLReader& reader) throw(wxString);
        void MergeInherited(xercesc::DOMElement* rootElement, xercesc::DOMLSSerializer* mainSerializer,
                            const char* rootElementFilename, XMLReader& mainRootElementXMLReader,
                            xercesc::DOMNode* mainDocRootNode);

    private:
        std::string m_mergedFile;

};

#endif // OPCIMPORTER_H
