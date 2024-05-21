import re
import sys
import logging
from typing import Dict, List, Tuple
from operator import itemgetter
from dataclasses import dataclass

# устанавливаем паттерн логирования
logging.basicConfig(filename='error.log', level=logging.ERROR, format='%(asctime)s %(levelname)s:%(message)s')


# функция для логирования ошибок
def log_error(message: str) -> None:
    logging.error(message)


# функция для логирования критических ошибок
def log_critical(message: str) -> None:
    logging.critical(message)


# класс, в котором хранятся все константы
@dataclass(frozen=True)
class Constants:
    INPUT_FILENAME = 'commits.txt'  # название входного файла
    RESULT_FILENAME = 'result.txt'  # название файла, в который будет записан результат
    WINNER_COUNT = 3  # кол-во победителей
    USER_NAME_PATTERN = re.compile(r'^[a-zA-Z_][a-zA-Z0-9_]*$')  # паттерн для проверки имени пользователя
    COMMIT_HASH_PATTERN = re.compile(r'^[a-z0-9]{7}$')  # паттерн для проверки хэша коммита
    COMMIT_DATA_PATTERN = re.compile(r'^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d*$')  # паттерн для проверки даты


# функция, проверяющая, что имя пользователя удовлетворяет заданному паттерну
def check_username(name: str) -> bool:
    return bool(Constants.USER_NAME_PATTERN.fullmatch(name))


# функция, проверяющая, что хэш коммита удовлетворяет заданному паттерну, а также его уникальность
def check_hash(user_hash: str, unique_hashes: set) -> bool:
    return bool(Constants.COMMIT_HASH_PATTERN.fullmatch(user_hash)) and user_hash not in unique_hashes


# функция, проверяющая, что дата удовлетворяет заданному паттерну
def check_date(date: str) -> bool:
    return bool(Constants.COMMIT_DATA_PATTERN.fullmatch(date))


# функия, считывающая данные из входного файла и собирающего dict[<имя пользвателя>,
# <кол-во сделанных этим пользователем коммитов>]
def read_file(filename: str) -> Dict[str, int]:
    commits_count: Dict[str, int] = {}
    unique_hashes: set = set()  # множество для хранения уникальных хэшей коммитов

    try:
        with open(filename, 'r') as file:
            for line in file:
                username, commit_hash, commit_date = line.strip().split()
                # проверка на то, что имя пользователя удовлетворяет заданному паттерну
                if not check_username(username):
                    log_error(f'Invalid username: {username}')
                    continue
                # проверка на то, что хэш коммита удовлетворяет заданному паттерну и его уникальность
                if not check_hash(commit_hash, unique_hashes):
                    log_error(f'Invalid commit hash: {commit_hash}')
                    continue
                # проверка на то, что хэш коммита удовлетворяет заданному паттерну
                if not check_date(commit_date):
                    log_error(f'Invalid commit date: {commit_date}')
                    continue

                # если все проверки пройдены добавляем 1 к кол-ву коммитов пользователя и
                # обновляем список уникальных хэшей коммитов
                commits_count[username] = commits_count.get(username, 0) + 1
                unique_hashes.add(commit_hash)

    # если файл для чтения не найден или возникла какая-нибудь другая ошибка завершаем работу програмы и
    # логируем ошибку
    except FileNotFoundError:
        log_critical(f'The file {filename} was not found.')
        sys.exit(1)
    except Exception as exp:
        log_error(f'Error reading the file {filename}: {exp}')
        sys.exit(1)

    return commits_count


# функция, выбирающая трех лучших работников по кол-ву коммитов, работает в среднем за O(nlogn)
def choose_winners(commits_count: Dict[str, int], winner_count: int) -> str:
    sorted_commits: List[Tuple[str, int]] = sorted(commits_count.items(), key=itemgetter(1), reverse=True)
    winners: str = ' '.join(username for username, _ in sorted_commits[:winner_count])
    return winners


# функция, которая записывает полученный результат в выходной файл
def write_result(winners: str) -> None:
    try:
        with open(Constants.RESULT_FILENAME, 'w') as file:
            file.write(winners)
    # если возникла какая-нибудь ошибка завершаем работу програмы и логируем ошибку
    except Exception as exp:
        log_error(f'Error writing to the file {Constants.RESULT_FILENAME}: {exp}')
        sys.exit(1)


def main() -> None:
    commits_count = read_file(Constants.INPUT_FILENAME)
    winners = choose_winners(commits_count, Constants.WINNER_COUNT)
    write_result(winners)


if __name__ == '__main__':
    main()
