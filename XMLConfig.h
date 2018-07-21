#ifndef XMLConfig_H 
#define XMLConfig_H
/**
 *  @file
 *  Class "GetConfig" provides the functions to read the XML data.
 *  @version 1.0
 */
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <stdexcept>
#include <map>
#include <memory>

// Error codes
enum { ERROR_ARGS = 1, ERROR_XERCES_INIT, ERROR_PARSE, ERROR_EMPTY_DOCUMENT };

// Main xerces-c based parser class implementation.
class XMLConfig
{
	private:
		std::unique_ptr<xercesc::XercesDOMParser> m_ConfigFileParser;
		XMLCh* TAG_root;					
		XMLCh* TAG_ApplicationSettings;
		std::map<std::string, std::string> m_InternalMap;	// The map that internally stores all the key/value pairs of XML sub section. 
		std::string m_InputConfigFileName;					// The file from which the XML configuration will be read and validated etc.
		std::string m_ApplicationSettings;					// The ApplicationSettings tag or section of XML which has the sub section where key/value attributes are to be found.
		std::string m_rootSectionName;						// This is the root section name. If not supplied then it is default initialized to root.		

	public:
		XMLConfig(const std::string& inputConfigFileName, const std::string& applicationSettings, const std::string& rootSectionName); 
		XMLConfig(const XMLConfig&) = delete;
		XMLConfig& operator=(const XMLConfig&) = delete;
		XMLConfig(XMLConfig&&) = delete;
		XMLConfig& operator=(XMLConfig&&) = delete;
		void readConfigFile();
		
		std::map<std::string, std::string>	getConfigMap();				// This returns the key value map of all attributes for the TAG_ApplicationSettings section of the xml. 
		bool isConfigValid();	// This tells if there are attributes found as indicated by the TAG_ApplicationSettings. If map size is zero then it is false.

		~XMLConfig();

}; 

#endif
