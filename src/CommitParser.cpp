//
// Created by DJ Tape on 21.05.2024.
//

#include "CommitParser.hpp"

#include <utility>

auto Parser::CommitParser::recordPattern{std::regex{R"(^(\w+_?\w*\d*)\s+(\w{7})\s+(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}))"}};

Parser::CommitParser::CommitParser(std::string  _commitsFile):
	commitsFile(std::move(_commitsFile))
	{

	}

Parser::Commit Parser::CommitParser::parseCommit(const std::string &fileLine) {
	std::smatch match;
	if (std::regex_search(fileLine, match, recordPattern)) {
		try {
			return Commit{match[1], match[2], match[3]};
		} catch (const std::string& err) {
			std::cout << err << std::endl;
		}
	}
	throw std::string{"Commit record doesn't match the correct format"};
}
