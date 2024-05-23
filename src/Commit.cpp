//
// Created by DJ Tape on 21.05.2024.
//

#include "Commit.hpp"
Parser::Commit::Commit(std::string _username, std::string _commitHash, const std::string& _commitTime):
		authorUsername(std::move(_username)), commitHash(std::move(_commitHash))
		{
			std::istringstream iss(_commitTime);
			// парсинг времени в структуру
			iss >> std::get_time(&commitTime, "%Y-%m-%dT%H:%M:%S");
			if (iss.fail()) {
				throw std::string{"Bad time format in commit: " + commitHash};
			}
		}

bool Parser::Commit::isRecentEnough(int validDayDiff) const {
	if (0 > validDayDiff or validDayDiff > 365) {
		throw std::string{"Invalid dayDiff argument in isRecentEnough func: must be between 0 and 365"};
	}
	std::time_t now = std::time(nullptr);
	std::tm* currentTime = std::localtime(&now);
	int yearDiff = currentTime->tm_year - commitTime.tm_year;
	int dayDiff = currentTime->tm_yday - commitTime.tm_yday;
	const auto isLeapYear = [](int year) -> bool {
		if (year % 4 != 0)
			return false;
		else if (year % 100 == 0 and year % 400 != 0)
			return false;
		else
			return true;
	}(commitTime.tm_year);

	if (yearDiff > 1)
		return false;
	if (yearDiff == 0) {
		if (dayDiff <= validDayDiff)
			return true;
		return false;
	}
	// если спринт начался ещё в прошлом году
	int daysBeforeNY{365 - commitTime.tm_yday}, daysAfterNY{currentTime->tm_yday};
	if (isLeapYear) {
		++daysBeforeNY;
	}
	if (daysBeforeNY + daysAfterNY <= validDayDiff)
		return true;
	return false;
}

std::string Parser::Commit::getAuthorUsername() const {
	return authorUsername;
}

std::string Parser::Commit::getHash() const {
	return commitHash;
}

std::tm Parser::Commit::getTime() const {
	return commitTime;
}
