import os
import re
from collections import defaultdict

input_file = 'commits.txt'
output_file = 'result.txt'

USER_PATTERN = r'^[a-zA-Z_][a-zA-Z0-9_]*$'
COMMIT_HASH_PATTERN = r'^[0-9a-f]{7}$'
DATE_PATTERN = r'^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}$'

def read_commits(file_path):
    try:
        unique_commits = set()  # Множество для хранения уникальных хэшей коммитов
        with open(file_path, 'r') as file:
            lines = file.readlines()
            print(f"Файл {file_path} прочитан, количество строк: {len(lines)}")
            unique_lines = []  # Список для хранения уникальных строк
            for line in lines:
                commit_hash = line.split()[1]
                if commit_hash not in unique_commits:
                    unique_commits.add(commit_hash)
                    unique_lines.append(line)
                else:
                    print(f"Дублирующийся хэш коммита: {commit_hash}")
            return unique_lines
    except Exception as e:
        print(f"Ошибка при чтении файла {file_path}: {e}")
        return []

def is_valid_commit(line):
    parts = line.split()
    if len(parts) != 3:
        return False
    user, commit_hash, date = parts
    return (re.match(USER_PATTERN, user) is not None) and \
           (re.match(COMMIT_HASH_PATTERN, commit_hash) is not None) and \
           (re.match(DATE_PATTERN, date) is not None)

def count_commits(lines):
    commit_counts = defaultdict(int)
    for line in lines:
        if not is_valid_commit(line):
            print(f"Некорректная строка коммита: {line}")
            continue
        try:
            user = line.split()[0]
            commit_counts[user] += 1
        except Exception as e:
            print(f"Ошибка при обработке строки: {line}, ошибка: {e}")
    print(f"Подсчет коммитов завершен: {dict(commit_counts)}")
    return commit_counts

def get_top_contributors(commit_counts, top_n=3):
    sorted_contributors = sorted(commit_counts.items(), key=lambda item: item[1], reverse=True)
    top_contributors = [user for user, count in sorted_contributors[:top_n]]
    print(f"Топ-{top_n} контрибьютеров: {top_contributors}")
    return top_contributors

def write_result(file_path, top_contributors):
    try:
        with open(file_path, 'w') as file:
            for user in top_contributors:
                file.write(f"{user}\n")
        print(f"Результат записан в файл {file_path}")
    except Exception as e:
        print(f"Ошибка при записи файла {file_path}: {e}")

def clear_file(file_path):
    try:
        open(file_path, 'w').close()
        print(f"Файл {file_path} очищен")
    except Exception as e:
        print(f"Ошибка при очистке файла {file_path}: {e}")

def main():
    print(f"Текущий рабочий каталог: {os.getcwd()}")

    if not os.path.isfile(input_file):
        print(f"Файл {input_file} не найден!")
        clear_file(output_file)
        return

    lines = read_commits(input_file)
    if not lines:
        print("Нет данных для обработки.")
        clear_file(output_file)
        return

    commit_counts = count_commits(lines)
    if not commit_counts:
        print("Нет данных о коммитах.")
        clear_file(output_file)
        return

    top_contributors = get_top_contributors(commit_counts)
    if not top_contributors:
        print("Нет контрибьютеров для записи.")
        clear_file(output_file)
        return
    write_result(output_file, top_contributors)

main()
