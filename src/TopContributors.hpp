//
// Created by DJ Tape on 22.05.2024.
//

#ifndef SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP
#define SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP

#include <iostream>
#include <vector>
#include "CommitParser.hpp"

namespace Contributors {

	static const unsigned DEFAULT_TOP_COUNT{3};

	class TopContributors {
	private:
		unsigned topCount{};
		std::vector<std::pair<std::string, int>> topContributorsList{};
	public:
		explicit TopContributors(unsigned _topCount=DEFAULT_TOP_COUNT);

		void FindTop(Parser::CommitMap commitMap);

		void WriteTopToFile(const std::string& _outputFile);

		void setTopCount(unsigned _topCount=DEFAULT_TOP_COUNT);
	};

}


#endif //SCHOOL2024_TEST_TASK7_TOPCONTRIBUTORS_HPP
