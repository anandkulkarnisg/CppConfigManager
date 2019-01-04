#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "XMLConfig.h"

using namespace xercesc;
using namespace std;

// The default and only constructor available is implemented below.
XMLConfig::XMLConfig(const std::string& inputConfigFileName, const std::string& applicationSettings, const std::string& rootSectionName) 
  : m_InputConfigFileName(inputConfigFileName) , 
  m_ApplicationSettings(applicationSettings) ,
  m_rootSectionName(rootSectionName)
{
  try
  {
    XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
  }
  catch( XMLException& e )
  {
    char* message = XMLString::transcode( e.getMessage() );
    std::cout << "XML toolkit initialization error: " << message << std::endl;
    XMLString::release( &message );
  }

  if(m_rootSectionName.empty())
    m_rootSectionName = "root";

  TAG_root = XMLString::transcode(m_rootSectionName.c_str());
  TAG_ApplicationSettings = XMLString::transcode(m_ApplicationSettings.c_str());
  m_ConfigFileParser = std::unique_ptr<xercesc::XercesDOMParser>(new XercesDOMParser);
}

// The readConfigFile Method implements reading from the supplied config file name. It parsers through the XML document and only initializes the map with key / values from the 
// sub section of m_ApplicationSettings.

void XMLConfig::readConfigFile()
{
  // Test to see if the file is ok.
  struct stat fileStatus;

  errno = 0;
  if(stat(m_InputConfigFileName.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
  {
    if( errno == ENOENT )      // errno declared by include file errno.h
      throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
    else if( errno == ENOTDIR )
      throw ( std::runtime_error("A component of the path is not a directory."));
    else if( errno == ELOOP )
      throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
    else if( errno == EACCES )
      throw ( std::runtime_error("Permission denied."));
    else if( errno == ENAMETOOLONG )
      throw ( std::runtime_error("File can not be read\n"));
  }

  // Configure DOM parser.
  m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
  m_ConfigFileParser->setDoNamespaces( false );
  m_ConfigFileParser->setDoSchema( false );
  m_ConfigFileParser->setLoadExternalDTD( false );

  try
  {
    m_ConfigFileParser->parse(m_InputConfigFileName.c_str());

    // no need to free this pointer - owned by the parent parser object
    DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();

    // Get the top-level element: NAme is "root". No attributes for "root"

    DOMElement* elementRoot = xmlDoc->getDocumentElement();
    if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));

    // Parse XML file for tags of interest: "ApplicationSettings"
    // Look one level nested within "root". (child of root)

    DOMNodeList*      children = elementRoot->getChildNodes();
    const  XMLSize_t nodeCount = children->getLength();

    // For all nodes, children of "root" in the XML tree.

    for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
    {
      DOMNode* currentNode = children->item(xx);
      if(XMLString::equals(currentNode->getNodeName(), TAG_ApplicationSettings))
      {
        if( currentNode->getNodeType() &&  // true is not NULL
            currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
        {
          // First traverse and print all values/names pairs.
          DOMNamedNodeMap* map = currentNode->getAttributes();
          int i, len = map ? map->getLength() : 0;
          for (i=0; i<len; ++i)
          {
            DOMNode *attr = map->item(i);
            const XMLCh* xmlch_nodeName = attr->getNodeName();
            const XMLCh* xmlch_nodeValue = attr->getNodeValue();

            // The pointer returned by transcode needs to be saved and released explicitly. Else leaks memory. 
            char* nodeNamePtr = XMLString::transcode(xmlch_nodeName);
            char* nodeValPtr = XMLString::transcode(xmlch_nodeValue);
            m_InternalMap[nodeNamePtr] = nodeValPtr;

            // Release the pointers.
            XMLString::release(&nodeNamePtr);
            XMLString::release(&nodeValPtr); 
          }
        }
      }
    }
  }
  catch( xercesc::XMLException& e )
  {
    char* message = xercesc::XMLString::transcode( e.getMessage() );
    ostringstream errBuf;
    errBuf << "Error parsing file: " << message << flush;
    XMLString::release( &message );
  }
}

// Indicates if the map is empty and indicates validity if the map has elements.
bool XMLConfig::isConfigValid()
{
  return(m_InternalMap.size()>0);
}

// Return The map to the end user if required.
std::map<std::string, std::string> XMLConfig::getConfigMap()
{
  return(m_InternalMap);	
}

// Destructor. Most important release all the resources here.
XMLConfig::~XMLConfig()
{

  // This is critical. Leaving to expire at the end causes segmentation fault. Seems all cleanup should be done before shutting down the Parser via XMLPlatformUtils::Terminate().
  m_ConfigFileParser.reset();	

  // Free memory
  try
  {
    XMLString::release( &TAG_root );
    XMLString::release( &TAG_ApplicationSettings );
  }
  catch( ... )
  {
    cerr << "Unknown exception encountered in TagNamesdtor" << endl;
  }

  // Terminate Xerces
  try
  {
    XMLPlatformUtils::Terminate();  // Terminate after release of memory
  }
  catch( xercesc::XMLException& e )
  {
    char* message = xercesc::XMLString::transcode( e.getMessage() );
    cerr << "XML ttolkit teardown error: " << message << endl;
    XMLString::release( &message );
  }
}

