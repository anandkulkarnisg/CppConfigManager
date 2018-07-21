#include "CppXMLConfigReader.h"

using namespace std;

// Constructor.
CppXMLConfigReader::CppXMLConfigReader(const std::string& configFileName, const std::string& applicationSettingsName, const std::string& rootSectionName)
{
	std::unique_ptr<XMLConfig> mPtr= std::unique_ptr<XMLConfig>(new XMLConfig(configFileName, applicationSettingsName, rootSectionName));
	m_XMLConfigManager = std::move(mPtr);
}

// Initialize the config reader here.
void CppXMLConfigReader::init()
{
	try
	{
		m_XMLConfigManager->readConfigFile();
	}
	catch(const std::runtime_error& error)
	{
		std::cout << "Failed to initialize the XMLConfigManager. The error is = " << error.what() << std::endl;	
	}

	if(m_XMLConfigManager->isConfigValid())
	{
		m_configMapItems = m_XMLConfigManager->getConfigMap();	
	}
}

// Valid status of the config.
bool CppXMLConfigReader::isConfigValid()
{
	return(m_XMLConfigManager->isConfigValid());	
}

std::map<std::string, std::string> CppXMLConfigReader::getConfigMap()
{
	return(m_configMapItems);
}

// All the specific config type returners implemented here.
int CppXMLConfigReader::getIntValue(const std::string& key, const int& defaultVal) const
{
	int returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = std::stoi(iter->second);	
		}
		catch(const std::invalid_argument& e)
		{
			std::cout << "Exception happened while converting " << iter->second << " Into an integer value." << std::endl;
		}
	}
	return(returnVal);
}

long CppXMLConfigReader::getLongValue(const std::string& key, const long& defaultVal) const
{
	long returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = std::stol(iter->second);
		}
		catch(const std::invalid_argument& e)
		{
			std::cout << "Exception happened while converting " << iter->second << " Into a long value." << std::endl;
		}
	}
	return(returnVal);
}

float CppXMLConfigReader::getFloatValue(const std::string& key, const float& defaultVal) const
{
	float returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = std::stof(iter->second);
		}
		catch(const std::invalid_argument& e)
		{
			std::cout << "Exception happened while converting " << iter->second << " Into an float value." << std::endl;
		}
	}
	return(returnVal);
}

double CppXMLConfigReader::getDoubleValue(const std::string& key, const double& defaultVal) const
{
	double returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = std::stod(iter->second);
		}
		catch(const std::invalid_argument& e)
		{
			std::cout << "Exception happened while converting " << iter->second << " Into an double value." << std::endl;
		}
	}
	return(returnVal);
}

bool CppXMLConfigReader::getBoolValue(const std::string& key, const bool& defaultVal) const
{
	bool returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		if(iter->second == "true" || iter->second == "1")
			returnVal=true;
		else
			returnVal=false;
	}
	return(returnVal);
}

std::string CppXMLConfigReader::getStringValue(const std::string& key, const std::string& defaultVal) const
{
	std::string returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if( iter != m_configMapItems.end())
	{
		returnVal = iter->second;
		return(returnVal);	
	}
	return(returnVal);
}
