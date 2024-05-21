#include <commits_leader.h>

using namespace std;
// если файл пустой, если меньше 3 человек
void readCommitsNumberFromFile(map<string, int> &commitsNumber, char *filename)
{
    ifstream srcFile(filename);
    string line, word, delimiter = " ";

    while (getline(srcFile, line))
    {
        word = line.substr(0, line.find(delimiter));
        auto it = commitsNumber.find(word);
        cout << word << endl;

        if (it != commitsNumber.end())
        {
            commitsNumber[word]++;
        }
        else
            commitsNumber[word] = 0;
    }
    srcFile.close();
}

void writeLeaderBoard(multimap<int, string> contributorsRaiting, char *filename)
{
    ofstream outputFile(filename);
    auto iter = contributorsRaiting.end();

    for (int i = 0; i < 3; i++)
    {
        if (iter == contributorsRaiting.begin())
            break;
        iter--;
        outputFile << iter->second << '\n';
    }
    outputFile.close();
}

int main(int argc, char **argv)
{

    map<string, int> commitsNumber;
    multimap<int, string> contributorsRaiting;

    readCommitsNumberFromFile(commitsNumber, argv[1]);

    auto it = commitsNumber.begin();
    while (it != commitsNumber.end())
    {
        cout << it->first << " ";
        it++;
    }

    for (auto &[key, value] : commitsNumber)
    {
        contributorsRaiting.insert({value, key});
    }

    cout << "\n----------------" << endl;
    auto it2 = contributorsRaiting.begin();
    while (it2 != contributorsRaiting.end())
    {
        cout << it2->first << " ";
        it2++;
    }
    writeLeaderBoard(contributorsRaiting, argv[2]);
}