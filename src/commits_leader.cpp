#include <commits_leader.h>

template <typename ContainerType> void printContainer(ContainerType container) {
  cout << "\n----------------" << endl;
  auto it = container.begin();
  while (it != container.end()) {
    cout << it->first << " " << it->second << endl;
    it++;
  }
  cout << "\n----------------" << endl;
}

// если файл пустой, если меньше 3 человек
void readCommitsNumberFromFile(map<string, int> &commitsNumber,
                               char *filename) {
  ifstream srcFile(filename);
  string line, word, delimiter = " ";

  while (getline(srcFile, line)) {
    word = line.substr(0, line.find(delimiter));
    auto it = commitsNumber.find(word);
    cout << word << endl;

    if (it != commitsNumber.end()) {
      commitsNumber[word]++;
    } else
      commitsNumber[word] = 1;
  }
  srcFile.close();
}

void writeLeaderBoard(multimap<int, string, greater<int>> contributorsRaiting,
                      char *filename) {
  ofstream outputFile(filename);
  auto iter = contributorsRaiting.begin();

  for (int i = 0; i < 3 && iter !=contributorsRaiting.end(); i++) {
    outputFile << iter->second << '\n';
    iter++;
  }
  outputFile.close();
}

void getLeaders(char *inputFilename, char *outputFilename) {

  map<string, int> commitsNumber;
  multimap<int, string, greater<int>> contributorsRaiting;

  readCommitsNumberFromFile(commitsNumber, inputFilename);
  printContainer(commitsNumber);
  for (auto &[key, value] : commitsNumber) {
    contributorsRaiting.insert({value, key});
  }
  printContainer(contributorsRaiting);
  writeLeaderBoard(contributorsRaiting, outputFilename);
}