#include <iostream>
#include "ConfigHandler.hpp"

int main() {
	std::cout << "Hello, World!" << std::endl;
	try {
		ConfigHandler::ConfigHandler Cfg{};
		std::cout << Cfg.getOutputFilePath() << std::endl << Cfg.getCommitsFilePath();
	} catch(const std::exception& e) {
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}
	return 0;
}
