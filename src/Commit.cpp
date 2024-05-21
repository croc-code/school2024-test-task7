//
// Created by DJ Tape on 21.05.2024.
//

#include "Commit.hpp"
//#include <utility>

Parser::Commit::Commit(std::string _username, std::string _commitHash, const std::string& _commitTime):
		username(std::move(_username)), commitHash(std::move(_commitHash))
		{
			std::istringstream iss(_commitTime);
			iss >> std::get_time(&commitTime, "%Y-%m-%dT%H:%M:%S.%3N");
			if (iss.fail()) {
				throw std::string{"Bad time format in commit: " + commitHash};
			}
		}

std::string Parser::Commit::getUsername() const {
	return username;
}

std::string Parser::Commit::getCommitHash() const {
	return commitHash;
}

std::tm Parser::Commit::getCommitTime() const {
	return commitTime;
}
