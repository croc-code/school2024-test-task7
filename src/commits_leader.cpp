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

bool checkNickname(string nickname) {
  if ('0' <= nickname[0] && nickname[0] <= '9')
    return false;
  for (auto iter = nickname.begin(); iter != nickname.end(); iter++) {
    if (!(('0' <= *iter && *iter <= '9') || ('a' <= *iter && *iter <= 'z') ||
          ('A' <= *iter && *iter <= 'Z') || *iter == '_')) {
      return false;
    }
  }
  return true;
}

bool checkHash(string hash) {
  if (hash.length() != 7)
    return false;
  for (auto iter = hash.begin(); iter != hash.end(); iter++) {
    if (!(('0' <= *iter && *iter <= '9') || ('a' <= *iter && *iter <= 'z'))) {
      return false;
    }
  }
  return true;
}

bool checkTime(string time) {
  (void)time;
  std::regex timestamp_regex(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3})");

  return std::regex_match(time, timestamp_regex);
}

bool checkDataCorrectness(string line, map<string, int> commitsNumber,
                          string &nickname, map<string, int>::iterator &it) {
  string hash, time, delimiter = " ";
  nickname = line.substr(0, line.find(delimiter));
  it = commitsNumber.find(nickname);
  if (!checkNickname(nickname)) {
    cout << "Некорректный никнейм " << nickname << endl;
    return false;
  }

  line.erase(0, line.find(delimiter) + 1);
  hash = line.substr(0, line.find(delimiter));
  if (!checkHash(hash)) {
    cout << "Некорректный хэш коммита " << hash << endl;
    return false;
  }

  line.erase(0, line.find(delimiter) + 1);
  time = line.substr(0, line.find(delimiter));
  if (!checkTime(time)) {
    cout << "Некорректное время коммита " << time << endl;
    return false;
  }
  return true;
}

bool readCommitsNumberFromFile(map<string, int> &commitsNumber,
                               char *filename) {
  ifstream srcFile(filename);
  string nickname, line;
  std::map<std::string, int>::iterator it;

  while (getline(srcFile, line)) {
    if (!checkDataCorrectness(line, commitsNumber, nickname, it))
      return false;
    if (it != commitsNumber.end()) {
      commitsNumber[nickname]++;
    } else
      commitsNumber[nickname] = 1;
  }
  srcFile.close();
  return true;
}

void writeLeaderBoard(multimap<int, string, greater<int>> contributorsRaiting,
                      char *filename) {
  ofstream outputFile(filename);
  auto iter = contributorsRaiting.begin();

  for (int i = 0; i < 3 && iter != contributorsRaiting.end(); i++) {
    outputFile << iter->second << '\n';
    iter++;
  }
  outputFile.close();
}

void getLeaders(char *inputFilename, char *outputFilename) {

  map<string, int> commitsNumber;
  multimap<int, string, greater<int>> contributorsRaiting;

  if (!readCommitsNumberFromFile(commitsNumber, inputFilename)) {
    cout << "Ошибка в формате строки" << endl;
    return;
  }

  for (auto &[key, value] : commitsNumber) {
    contributorsRaiting.insert({value, key});
  }
  writeLeaderBoard(contributorsRaiting, outputFilename);
}