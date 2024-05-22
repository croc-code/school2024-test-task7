#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <filesystem>

struct Contributor {
    std::string name;
    int commitsCount;
};

bool compareContributors(const Contributor &a, const Contributor &b) {
    return a.commitsCount > b.commitsCount;
}

//Проверка даты на попадание в диапазон 4 недели от текущего времени
bool isWithinFourWeeks(const std::string& commit_date) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // Приведение строки commit_date к типу time_point
    std::tm commit_tm = {};
    std::istringstream ss(commit_date);
    ss >> std::get_time(&commit_tm, "%Y-%m-%dT%H:%M:%S");
    std::chrono::system_clock::time_point commit_point = std::chrono::system_clock::from_time_t(std::mktime(&commit_tm));

    /*
    Проверка, была ли дата коммита менее чем 4 недели назад.
    Высчитывая разницу в кол-ве часов и включительно день в день, учитывая, что процедура запускается в 00:00.
    Поэтому кол-во часов умножается не на 28, а на 29. 
    Например, если программа была запущена в 00:00 в среду, то засчитываются даты начиная со среды 4 недели тому назад
    (для 22.05.2024 это будет 24.04.2024)
    */ 
    std::chrono::system_clock::duration diff = now - commit_point;
    std::chrono::hours diff_in_hours = std::chrono::duration_cast<std::chrono::hours>(diff);
    return diff_in_hours.count() < 29 * 24;
}

std::vector<Contributor> countCommits(const std::filesystem::path& commitstxt){
    std::unordered_map<std::string, int> commitsCountMap;
    std::vector<Contributor> contributors;

    std::ifstream commits_stream(commitstxt);
    if (commits_stream.is_open()){
        std::string line;
        while(std::getline(commits_stream, line)){
            std::string name = line.substr(0, line.find(' '));
            std::string commit_date = line.substr(line.find_last_of(' ') + 1);

            //Если коммит был сделан в течение последних 4 недель, то он засчитывается пользователю
            if(isWithinFourWeeks(commit_date)){
                commitsCountMap[name]++;
            }
        } 
        commits_stream.close();
        
        for (const auto &entry : commitsCountMap) {
            contributors.push_back({entry.first, entry.second});
        }
        std::sort(contributors.begin(), contributors.end(), compareContributors);
        
    } else {
        std::cerr << "Ошибка при открытии файла " << commitstxt.filename().string() << '\n';
    }
    return contributors;
}

void writeResult(){
    std::ofstream output("result.txt");

    std::vector<Contributor> contributors = countCommits("commits.txt");

    //Проверка, что вектор не пустой
    if(!contributors.empty()){    
        if (output.is_open()) {
            for (int i = 0; i < 3 && i < contributors.size(); ++i) {
                    output << contributors[i].name << '\n';
                }
                output.close();
                std::cout << "Отчет успешно сформирован и сохранен в файле result.txt" << std::endl;
        } else {
            std::cerr << "Ошибка при открытии файла для записи" << std::endl;
        }
    }
    
}

int main() {
    writeResult();
    
    return 0;
}