//
// Created by DJ Tape on 21.05.2024.
//

#include "CommitParser.hpp"


const std::regex Parser::CommitParser::recordPattern{R"(^([A-Za-z_][A-Za-z0-9_]*) ([a-z0-9]{7}) (\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(?:\.\d+)?))"};

Parser::CommitParser::CommitParser(const std::string &_commitsFile, const int _sprintDurationInDays):
	sprintDurationInDays(_sprintDurationInDays)
	{
		commitsFile.open(_commitsFile);
		if (!commitsFile.is_open()) {
			throw std::runtime_error("Error opening a file by path: " + _commitsFile);
		}

		std::cout << "COMMIT_PARSER CONSTRUCTOR" << std::endl;
	}

void Parser::CommitParser::setSprintDuration(int _sprintDurationInDays) {
	this->sprintDurationInDays = _sprintDurationInDays;
}

// Парсинг отдельного коммита
Parser::Commit* Parser::CommitParser::parseCommit(const std::string &fileLine) {
	p_commit++;
	std::cout << p_commit << " CALL parseCOMMIT FUNC ";
	std::smatch match;
	if (std::regex_search(fileLine, match, recordPattern)) {
		try {
			std::cout << "CREATING COMMIT AND RETURN IT" << std::endl;
			return new Commit{match[1], match[2], match[3]};
		} catch (const std::string& err) {
			std::cout << err << std::endl;
		}
	} else {
		throw std::string{"Commit record doesn't match the correct format"};
	}
}
const Parser::CommitMap* Parser::CommitParser::ParseCommits() {
	std::string commitRecord;
	auto* contributorsCommits = new Parser::CommitMap;
	while (std::getline(commitsFile, commitRecord)) {
		try {
			std::cout << "assign a returned value to the variable" << std::endl;
			auto commit = parseCommit(commitRecord);
			// Если коммит не попадает в нужные временные рамки, то пропускаем его
			if (!commit->isRecentEnough(sprintDurationInDays)) {
				throw std::string{"Commit "} + std::string{commit->getHash()}
					  + std::string{" does not fit within the required time frame"};
			}
			std::cout << "add the commit to the map" << std::endl;
			contributorsCommits->operator[](commit->getAuthorUsername()).push_back(commit);
		} catch (const std::string& err) {
			std::cout << err << std::endl;
		}
	}
	return contributorsCommits;
}

Parser::CommitParser::~CommitParser() {
	if(commitsFile.is_open()) {
		commitsFile.close();
	}

	std::cout << "COMMIT_PARSER DESTRUCTOR" << std::endl;
}

int Parser::CommitParser::p_commit{};