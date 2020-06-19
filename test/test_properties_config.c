#include "usg_common.h"
#include "properties_config.h"

int main() {
	PropertiesConfig config("./config.txt");

	std::cout << config.get("name") << std::endl;
}