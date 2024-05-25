//
// Created by DJ Tape on 22.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP
#define SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP

#include <iostream>
#include <vector>
#include "CommitParser.hpp"

namespace Contributors {

	// Значение по умолчанию для количества лучших контрибьюторов, которых нужно записать в файл
	static const unsigned DEFAULT_TOP_COUNT{3};

	/**
		Функционал:
	 		Сортировка контрибьютеров по количеству коммитов
	 		Запись DEFAULT_TOP_COUNT лучших контрибьютеров в файл
	*/
	class TopContributors {
	private:
		unsigned topCount{DEFAULT_TOP_COUNT};
		std::vector<std::pair<std::string, int>> topContributorsList{};
	public:
		explicit TopContributors(unsigned _topCount=DEFAULT_TOP_COUNT);

		~TopContributors();

		void FindTop(const Parser::CommitMap& commitMap);

		void WriteTopToFile(const std::string& _outputFile);

		void setTopCount(unsigned _topCount=DEFAULT_TOP_COUNT);
	};

}


#endif //SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP
