//
// Created by DJ Tape on 21.05.2024.
//

#include "ConfigHandler.hpp"

//#include <utility>

ConfigHandler::ConfigHandler::ConfigHandler(std::string _configFilePath):
	configFilePath(std::move(_configFilePath))
	{
		std::ifstream configFile{configFilePath};
		if (!configFile.is_open()) {
			throw std::runtime_error("Error opening a config file by path: " + configFilePath);
		}

		nlohmann::json j{};
		configFile >> j;

		commitsFilePath = j["commitsFilePath"].get<std::string>();
		outputFilePath = j["outputFilePath"].get<std::string>();

		configFile.close();
	}

std::string ConfigHandler::ConfigHandler::getCommitsFilePath() const {
	return commitsFilePath;
}

std::string ConfigHandler::ConfigHandler::getOutputFilePath() const {
	return outputFilePath;
}