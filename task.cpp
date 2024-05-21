#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

// Компаратор для сортировки вектора
bool comparator(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

// Проверка входных данных
bool checker(const string& line){
    vector<string> tokens;
    string::size_type start = 0;
    string::size_type end = line.find(' ');
    bool flag = false;

    regex usernameRegex(R"(^[a-zA-Z][a-zA-Z0-9_]*$)");
    regex commitHashRegex(R"(^[a-f0-9]{7}$)");
    regex dateTimeRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])T([01]\d|2[0-3]):([0-5]\d):([0-5]\d)$)");

    while (end != string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find(' ', start);
    }

    tokens.push_back(line.substr(start));

    for(int i = 0; i < tokens.size(); i+=3){
        if(regex_match(tokens[i], usernameRegex)){
            flag = true;
        }
    }
    for(int i = 1; i < tokens.size(); i+=3){
        if(regex_match(tokens[i], commitHashRegex)){
            flag = true;
        }
    }
    for(int i = 2; i < tokens.size(); i+=3){
        if(regex_match(tokens[i], dateTimeRegex)){
            flag = true;
        }
    }

    return flag;
}

int main(){
    ifstream infile("commit.txt");
    vector<pair<string, int>> commit_counter;
    vector<string> nicknames;

    // Читаем файл
    if(!infile.is_open()){
        return 1;
    } else {
        string line, temp;
        while (getline(infile, line)) {
            if(checker(line)){
                size_t pos = line.find(' ');
                string nickname = line.substr(0, pos);
                nicknames.push_back(nickname);
            }
        }
    }
    infile.close();
    commit_counter.reserve(nicknames.size());

    // Заполняем, сортируем и берем лучших
    for(auto& i : nicknames){
        commit_counter.emplace_back(i, count(nicknames.begin(), nicknames.end(), i));
    }
    sort(commit_counter.begin(), commit_counter.end(), comparator);
    commit_counter.erase(unique(commit_counter.begin(), commit_counter.end()), commit_counter.end());

    // Запись в файл
    ofstream outfile("result.txt");
    if (outfile.is_open()) {
        for (size_t i = 0; i < 3 && i < commit_counter.size(); ++i) {
            outfile << commit_counter[i].first << ' ';
        }

        outfile.close();
    } else {
        cerr << "error" << endl;
    }

    return 0;
}