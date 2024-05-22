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

void Contributors::TopContributors::FindTop(Parser::CommitMap commitMap) {
	for (const auto& pair : commitMap) {
		topContributorsList.emplace_back(pair.first, pair.second.size());
	}

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
	for(size_t i{}; i < topContributorsList.size(); ++i) {
		outputFile << topContributorsList[i].first << std::endl;
		if (i >= topCount - 1 and i != topContributorsList.size() - 1
		and topContributorsList[i+i].second < topContributorsList[i].second) {
			break;
		}
	}
	outputFile.close();
}
