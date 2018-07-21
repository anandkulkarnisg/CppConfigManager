#include<iostream>
#include<string>

#include "CppXMLConfigReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Case 1 : A valid xml file.
	CppXMLConfigReader reader("sample.xml", "OtherStuff", "CustomRoot");
	reader.init();
	
	// After starting check if the config is valid.
	std::cout << reader.isConfigValid() << std::endl;

	// Test the result here.
	std::map<std::string, std::string> resultMap = reader.getConfigMap();
	for(const auto& iter : resultMap)
		std::cout << iter.first << " , " << iter.second << std::endl;	

	double configItem = reader.getDoubleValue("HelloConfig", 100.123);
	std::cout << "Double configuration HelloConfig = " << configItem << std::endl;

	return(0);
}

