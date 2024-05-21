//
// Created by DJ Tape on 21.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP
#define SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP

#include <iostream>
#include <regex>
#include "Commit.hpp"

namespace Parser {
	class CommitParser {
	private:
		std::string commitsFile{};
		static const auto recordPattern;
		static Commit parseCommit(const std::string& fileLine);
	public:
		explicit CommitParser(std::string _commitsFile);
	};
} //Parser


#endif //SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP
