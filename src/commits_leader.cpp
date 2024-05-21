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
         ('A' <= *iter && *iter <= 'Z') || *iter == '_'))
         {
            cout << "letter " << *iter << endl;
      return false;
         }
  }
  return true;
}
/*
- имя пользователя может содержать латинские символы в любом регистре, цифры (но
не начинаться с них), а также символ "_";
- сокращенный хэш коммита представляет из себя строку в нижнем регистре,
состояющую из 7 символов: букв латинского алфавита, а также цифр;
- дата и время коммита в формате YYYY-MM-ddTHH:mm:ss.
*/
// добавить проверку элементов в строке
bool readCommitsNumberFromFile(map<string, int> &commitsNumber,
                               char *filename) {
  ifstream srcFile(filename);
  string line, nickname, delimiter = " ";

  while (getline(srcFile, line)) {
    nickname = line.substr(0, line.find(delimiter));
    auto it = commitsNumber.find(nickname);
    cout << nickname << endl;
    if (!checkNickname(nickname)) {
      cout << "Некорректный никнейм " << nickname << endl;
      return false;
    }

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