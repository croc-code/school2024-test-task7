//
// Created by DJ Tape on 21.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_COMMIT_HPP
#define SCHOOL2024_TEST_TASK7_COMMIT_HPP

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace Parser {
	/**
		 Функционал:
		 	Проверка свежести коммита
		 Пример:
		 	Commit commit{"Ivan_Petrov", "hash256", "2024-05-05T13:56:39.492"};
		 	if (!commit.isRecentEnough(14)) {
		 		std::cout << commit.getHash() << "Commit was made a long time ago";
		 	} else {
		 		std::cout << All is OK << std::endl;
		 	}

		 Код из примера выводит в консоль "All is OK", в случае если коммит сделан не раньше, чем 14 дней назад.
		 Текущий день при проверке не учитывается
	 */
	class Commit {
	private:
		std::string authorUsername{};
		std::string commitHash{};
		std::tm commitTime{};
	public:
		Commit(std::string  _username, std::string  _commitHash, const std::string& _commitTime);

		[[nodiscard]] bool isRecentEnough(int validDayDiff) const;

		[[nodiscard]] std::string getAuthorUsername() const;

		[[nodiscard]] std::string getHash() const;

		[[nodiscard]] std::tm getTime() const;
	};

} //Parser


#endif //SCHOOL2024_TEST_TASK7_COMMIT_HPP
