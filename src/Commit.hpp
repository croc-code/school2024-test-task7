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
		std::string authorUsername{};
		std::string commitHash{};
		std::tm commitTime{};
	public:
		Commit(std::string  _username, std::string  _commitHash, const std::string& _commitTime);

//		Commit();

//		Commit(const Commit& commit);

//		Commit(Commit&& moved) noexcept;

		[[nodiscard]] bool isRecentEnough(int validDayDiff) const;

		[[nodiscard]] std::string getAuthorUsername() const;

		[[nodiscard]] std::string getHash() const;

		[[nodiscard]] std::tm getTime() const;
	};

} //Parser


#endif //SCHOOL2024_TEST_TASK7_COMMIT_HPP
