#include "CppXMLConfigReader.h"

using namespace std;

// Constructor.
CppXMLConfigReader::CppXMLConfigReader(const string& configFileName, const string& applicationSettingsName, const string& rootSectionName)
{
  unique_ptr<XMLConfig> mPtr=make_unique<XMLConfig>(configFileName, applicationSettingsName, rootSectionName);
	m_XMLConfigManager = move(mPtr);
}

// Initialize the config reader here.
void CppXMLConfigReader::init()
{
	try
	{
		m_XMLConfigManager->readConfigFile();
	}
	catch(const runtime_error& error)
	{
		cout << "Failed to initialize the XMLConfigManager. The error is = " << error.what() << endl;	
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

map<string, string> CppXMLConfigReader::getConfigMap()
{
	return(m_configMapItems);
}

// All the specific config type returners implemented here.
int CppXMLConfigReader::getIntValue(const string& key, const int& defaultVal) const
{
	int returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = stoi(iter->second);	
		}
		catch(const invalid_argument& e)
		{
			cout << "Exception happened while converting " << iter->second << " Into an integer value." << endl;
		}
	}
	return(returnVal);
}

long CppXMLConfigReader::getLongValue(const string& key, const long& defaultVal) const
{
	long returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = stol(iter->second);
		}
		catch(const invalid_argument& e)
		{
			cout << "Exception happened while converting " << iter->second << " Into a long value." << endl;
		}
	}
	return(returnVal);
}

float CppXMLConfigReader::getFloatValue(const string& key, const float& defaultVal) const
{
	float returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = stof(iter->second);
		}
		catch(const invalid_argument& e)
		{
			cout << "Exception happened while converting " << iter->second << " Into an float value." << endl;
		}
	}
	return(returnVal);
}

double CppXMLConfigReader::getDoubleValue(const string& key, const double& defaultVal) const
{
	double returnVal = defaultVal;
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
	{
		try
		{
			returnVal = stod(iter->second);
		}
		catch(const invalid_argument& e)
		{
			cout << "Exception happened while converting " << iter->second << " Into an double value." << endl;
		}
	}
	return(returnVal);
}

bool CppXMLConfigReader::getBoolValue(const string& key, const bool& defaultVal) const
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

string CppXMLConfigReader::getStringValue(const string& key, const string& defaultVal) const
{
	auto iter = m_configMapItems.find(key.c_str());
	if(iter != m_configMapItems.end())
		return(iter->second);
	return(defaultVal);
}
