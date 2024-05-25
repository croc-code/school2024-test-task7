//
// Created by DJ Tape on 22.05.2024.
//

#include "TopContributors.hpp"

Contributors::TopContributors::TopContributors(unsigned int _topCount): topCount(_topCount)
{
	if (topCount == 0)
		topCount = 1;
}

void Contributors::TopContributors::setTopCount(unsigned int _topCount) {
	this->topCount = _topCount;
}

void Contributors::TopContributors::FindTop(const Parser::CommitMap*& commitMap) {
	for (const auto& pair : *commitMap) {
		topContributorsList.emplace_back(pair.first, pair.second.size());
		for (size_t i{}; i < pair.second.size(); ++i) {
			delete pair.second[i];
		}
	}
	delete commitMap;
	// сортировка контрибьютеров по количеству коммитов
	std::sort(topContributorsList.begin(), topContributorsList.end(),
			  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool {
				  return a.second > b.second;
	});
}

void Contributors::TopContributors::WriteTopToFile(const std::string &_outputFile) {
	std::ofstream outputFile{_outputFile};
	if(!outputFile.is_open()) {
		throw std::runtime_error("Error opening output file by path: " + _outputFile);
	}

	size_t i{};
	for(; i < topCount; ++i) {
		outputFile << topContributorsList[i].first << std::endl;
	}
	// Если на какое-то место претендуют сразу несколько контрибьютеров, то выводим их всех
	while (topContributorsList[i].second == topContributorsList[i-1].second and i < topContributorsList.size()) {
		outputFile << topContributorsList[i++].first << std::endl;
	}
	outputFile.close();
}
