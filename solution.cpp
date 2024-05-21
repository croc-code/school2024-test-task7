#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Функция сравнения двух контрибьютеров по количеству коммитов
bool CompareCommiters(const std::pair<std::string, int> &a,
                      const std::pair<std::string, int> &b);

// Функция преобразования даты в структуру std::tm
std::tm DateStringToDate(const std::string &date);

// Функция, проверяющая, что коммит был сделан не позднее четырёх недель назад
bool IsInLastFourWeeks(const std::string &date);

int main() {
  std::ios_base::sync_with_stdio(false);
  const int NUMBER_OF_TOP_COMMITERS = 3;
  // Открываем файлы для чтения и записи
  std::ifstream Input("commits.txt");
  std::ofstream Output("result.txt");

  // Создаём хэш-таблицу для хранения количества коммитов каждого контрибьютера
  std::map<std::string, int> commiters;

  // Считываем файл построчно
  std::string line;
  while (std::getline(Input, line)) {
    std::istringstream iss(line);
    std::string username, commit_hash, commit_date;
    iss >> username >> commit_hash >> commit_date;

    // Если коммит был сделан более четырёх недель назад, то пропускаем его
    if (!IsInLastFourWeeks(commit_date)) {
      continue;
    }

    // Если контрибьютера нет в хэш-таблице, то добавляем его. Если есть, то
    // увеличиваем количество его коммитов на 1
    if (!commiters.count(username)) {
      commiters[username] = 1;
    } else {
      ++commiters[username];
    }
  }
  Input.close();

  // Сортируем контрибьютеров по количеству их коммитов
  std::vector<std::pair<std::string, int>> sorted_commiters(commiters.begin(),
                                                            commiters.end());
  std::sort(sorted_commiters.begin(), sorted_commiters.end(), CompareCommiters);

  // Выводим топ-3 контрибьютеров в файл (или всех, если их меньше трёх)
  size_t top_commiters = std::min(NUMBER_OF_TOP_COMMITERS,
                                  static_cast<int>(sorted_commiters.size()));
  for (size_t i = 0; i < top_commiters; ++i) {
    Output << sorted_commiters[i].first << std::endl;
  }

  Output.close();
  return 0;
}

bool CompareCommiters(const std::pair<std::string, int> &a,
                      const std::pair<std::string, int> &b) {
  return a.second > b.second;
}

std::tm DateStringToDate(const std::string &date) {
  // Преобразуем строку в структуру std::tm
  std::istringstream iss(date);
  std::tm time = {};
  iss >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
  return time;
}

bool IsInLastFourWeeks(const std::string &date) {
  // Преобразуем строку в структуру std::tm и получаем текущее время
  std::tm commit_date = DateStringToDate(date);
  std::time_t now = std::time(nullptr);

  // Считаем разницу во времени между текущим временем и временем коммита
  double diff = std::difftime(now, std::mktime(&commit_date));
  // Разница должна быть не более четырёх недель и неотрицательной
  return (diff <= 4 * 7 * 24 * 60 * 60) && (diff >= 0);
}