#include "xmlreader.h"
#include "opcglobal.h"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace xercesc;

XMLReader::XMLReader() : m_parser(0), m_errHandler(0)
{
    //ctor
}

XMLReader::~XMLReader()
{
    //dtor
}

DOMDocument *XMLReader::GetDocument()
{
	return m_parser->getDocument();
}

DOMNode* XMLReader::OpenXmlDOM(const char* filenameToImport)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
        return 0;
    }

    m_parser.reset(new XercesDOMParser());
    m_parser->setValidationScheme(XercesDOMParser::Val_Always);
    m_parser->setDoNamespaces(true);    // optional

    m_errHandler.reset((ErrorHandler*) new HandlerBase());
    m_parser->setErrorHandler(m_errHandler.get());

    try {
         m_parser->parse(filenameToImport);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return 0;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return 0;
    }
    catch (...) {
        cerr << "Unexpected Exception \n" ;
        return 0;
    }

    return m_parser->getDocument()->getDocumentElement();
}

