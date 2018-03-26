#ifndef XMLREADER_H
#define XMLREADER_H

#include <memory>

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

class XMLReader
{
    public:
        XMLReader();
        ~XMLReader();

    public:
        xercesc::DOMNode *OpenXmlDOM(const char* filename);
		xercesc::DOMDocument *GetDocument();

	private:
		std::auto_ptr<xercesc::XercesDOMParser> m_parser;
		std::auto_ptr<xercesc::ErrorHandler>    m_errHandler;
};

#endif // XMLREADER_H
