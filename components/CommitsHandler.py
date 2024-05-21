import re

'''
Данный файл реализует обработчик коммитов

Класс обработчика содержит поля: список с коммитами и словарь с разработчиками

Реализован статический метод для проверки конкретной строки на соответствие заданному в условии формату

Метод get_result выполняет основную логику программы и возвращает список из топ-3 разработчиков
'''


class CommitsHandler:
    def __init__(self, commits):
        self.commits = commits
        self.developers = {}

    @staticmethod
    def check_commit(commit):
        user_regex = r'^[A-Za-z_][A-Za-z0-9_]*$'
        hash_regex = r'^[a-f0-9]{7}$'
        datetime_regex = r'^^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}.?\d*'

        data = commit.split()

        if len(data) != 3:
            return False

        username, commit_hash, datetime = data

        if not re.match(user_regex, username):
            return False
        elif not re.match(hash_regex, commit_hash):
            return False
        elif not re.match(datetime_regex, datetime):
            return False
        return True

    def get_result(self):
        for commit in self.commits:
            if not self.check_commit(commit):
                return False
            developer = commit.split()[0]
            if developer not in self.developers:
                self.developers[developer] = 0
            self.developers[developer] += 1
        sorted_developers = sorted(self.developers.items(), key=lambda x: x[1], reverse=True)[:3]
        return [name for name, count in sorted_developers]
