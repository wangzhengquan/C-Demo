#include "usg_common.h"

class PropertiesConfig {
	std::string propertiesFile;
	std::map<std::string, std::string> propertiesMap;
public:

	PropertiesConfig(std::string _propertiesFile="./config.properties");
	std::string get(std::string name);
	int getInt(std::string name);
};