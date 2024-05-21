//
// Created by DJ Tape on 21.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_CONFIGHANDLER_HPP
#define SCHOOL2024_TEST_TASK7_CONFIGHANDLER_HPP

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"


namespace ConfigHandler {

	static const std::string DEFAULT_CONFIG_PATH{"../config/config.json"};

	class ConfigHandler {
	private:
		std::string configFilePath{DEFAULT_CONFIG_PATH};
		std::string commitsFilePath;
		std::string outputFilePath;
	public:
		explicit ConfigHandler(std::string filePath=DEFAULT_CONFIG_PATH);

		[[nodiscard]] std::string getCommitsFilePath() const;

		[[nodiscard]] std::string getOutputFilePath() const;
	};

} //ConfigHandler


#endif //SCHOOL2024_TEST_TASK7_CONFIGHANDLER_HPP
