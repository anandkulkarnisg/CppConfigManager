#include<iostream>
#include<string>

#include "CppXMLConfigReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Case 1 : A valid xml file.
	CppXMLConfigReader reader("test.xml", "ApplicationSettings", "root");
	reader.init();
	
	// After starting check if the config is valid.
	std::cout << reader.isConfigValid() << std::endl;

	// Test the result here.
	std::map<std::string, std::string> resultMap = reader.getConfigMap();
	for(const auto& iter : resultMap)
		std::cout << iter.first << " , " << iter.second << std::endl;	

	int configItem = reader.getIntValue("cycleSleepDurationMilliSecs", 100);
	std::cout << "Integer configuration cycleSleepDurationMilliSecs = " << configItem << std::endl;

	// Try an invalid configuration.
	int invalidConfigItem = reader.getIntValue("AbracaDabra", 120);
	std::cout << "Invalid configItem request of AbracaDabra = " << invalidConfigItem << std::endl;

	// Try a boolean value.
	bool displayStatus = reader.getBoolValue("displayMode", true);
	if(!displayStatus)
	{
		std::cout << "display is not set" << std::endl;
	}
	else
	{
		std::cout << "display is set" << std::endl;
	}

	// Try a float value.
	float queueCapacityAdjFactor = reader.getFloatValue("queueCapacityAdjFactor", 12.50);
	std::cout << "queueCapacityAdjFactor = " << queueCapacityAdjFactor << std::endl;
	return(0);
}

