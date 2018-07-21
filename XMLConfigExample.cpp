#include<iostream>
#include<string>

#include "XMLConfig.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Case 1 : A valid xml file.
	XMLConfig configManager("test.xml", "ApplicationSettings", "root");
	try
	{
		configManager.readConfigFile();
	}
	catch(const runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
	std::map<std::string, std::string> mapItems = configManager.getConfigMap();
	if(configManager.isConfigValid())
	{
		for(auto& iter : mapItems)
			std::cout << iter.first << " , " << iter.second << std::endl;
	}
	std::cout << "size of the map = " << mapItems.size() << std::endl;	

	// Case 2 : An invalid case of a no existing file.
	XMLConfig configManager2("tiko.xml", "ApplicationSettings", "root");
	try
	{		
		configManager2.readConfigFile();
	} 
	catch(const runtime_error& error)	
	{
		std::cout << error.what() << std::endl;
	}

	if(!configManager2.isConfigValid())
	{	
		std::cout << "Invalid configuration file. Please investigate" << std::endl;
	}
	return(0);
}

