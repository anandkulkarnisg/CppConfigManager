#ifndef CppXMLConfigReader_H
#define CppXMLConfigReader_H

#include<iostream>
#include<string>

#include "XMLConfig.h"

using namespace std;

class CppXMLConfigReader
{
  private:
    std::unique_ptr<XMLConfig> m_XMLConfigManager;	// This is the XMLConfigManager based on xerces-c. This class simply wraps a higher level as helper and implements converting the config to proper type.
    std::map<std::string, std::string> m_configMapItems;	// This is the config map items returned by the XMLConfigManager.

  public:
    CppXMLConfigReader(const std::string& configFileName, const std::string& applicationSettingsName, const std::string& rootSectionName);
    CppXMLConfigReader(const CppXMLConfigReader&) = delete;
    CppXMLConfigReader operator=(const CppXMLConfigReader&) = delete;
    CppXMLConfigReader(CppXMLConfigReader&&) = delete;
    CppXMLConfigReader& operator=(CppXMLConfigReader&&) = delete;
    bool isConfigValid();
    void init();
    std::map<std::string, std::string> getConfigMap();

    // The actual helper interface that returns a suitable type for the underlying config item.All config items are returned on is available basis. If map is empty because config is invalid
    // The values are defaulted to the default value supplied to the function. This is normal behaviour for critical applications.

    int getIntValue(const std::string& key, const int& defaultVal) const;
    long getLongValue(const std::string& key, const long& defautlVal) const;
    float getFloatValue(const std::string& key, const float& defaultVal) const;
    double getDoubleValue(const std::string& key, const double& defaultVal) const;
    bool getBoolValue(const std::string& key, const bool& defautlVal) const;
    std::string getStringValue(const std::string& key, const std::string& defaultVal) const;
};

#endif
