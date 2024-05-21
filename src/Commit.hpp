//
// Created by DJ Tape on 21.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_COMMIT_HPP
#define SCHOOL2024_TEST_TASK7_COMMIT_HPP

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
//#include <string>

namespace Parser {
	class Commit {
	private:
		std::string username{};
		std::string commitHash{};
		std::tm commitTime{};
	public:
		Commit(std::string  _username, std::string  _commitHash, const std::string& _commitTime);

		[[nodiscard]] std::string getUsername() const;

		[[nodiscard]] std::string getCommitHash() const;

		[[nodiscard]] std::tm getCommitTime() const;
	};

} //Parser


#endif //SCHOOL2024_TEST_TASK7_COMMIT_HPP
