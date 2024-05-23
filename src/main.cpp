#include <iostream>
#include "ConfigHandler.hpp"
#include "TopContributors.hpp"

int main() {
	try {
		ConfigHandler::ConfigHandler Config{};
		Parser::CommitParser parser{Config.getCommitsFilePath()};
		Contributors::TopContributors topContributors{};
		auto commitRecords = parser.ParseCommits();
		topContributors.FindTop(commitRecords);
		topContributors.WriteTopToFile(Config.getOutputFilePath());
	} catch(const std::exception& e) {
		std::cout << "Error occurred: " << e.what() << std::endl;
	}
	return 0;
}
