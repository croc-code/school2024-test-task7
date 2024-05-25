//
// Created by DJ Tape on 21.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP
#define SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP

#include <iostream>
#include <regex>
#include <fstream>
#include "Commit.hpp"

namespace Parser {

	using CommitMap = std::map<std::string, std::vector<Commit*>>;

	// Значение по умолчанию для продолжительности спринта(4 недели)
	static const int DEFAULT_DURATION_DAYS{28};

/**
	Парсинг файла с коммитами
	Пример:
	  CommitParser parser{NameOfTheFileWithCommitRecords};
	  Parser::CommitMap commits = parser.ParseCommits()
*/
	class CommitParser {
	private:
		int sprintDurationInDays{DEFAULT_DURATION_DAYS};
		std::ifstream commitsFile;
		static const std::regex recordPattern;
		static Commit* parseCommit(const std::string& fileLine);
	public:
		explicit CommitParser(const std::string& _commitsFile, int _sprintDurationInDays=DEFAULT_DURATION_DAYS);
		~CommitParser();
		void setSprintDuration(int _sprintDurationInDays=DEFAULT_DURATION_DAYS);
		const CommitMap* ParseCommits();
	};
} //Parser


#endif //SCHOOL2024_TEST_TASK7_COMMITPARSER_HPP
