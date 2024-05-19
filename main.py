# Процедура для построения рейтинга самых активных разработчиков
def active_rating(filename: str) -> None:
    """
    :param filename - имя входного файла
    """
    contributors_score = dict()  # Словарь с рейтингом контрибъютеров

    with open(filename, 'r', encoding='utf-8') as commit_file:  # октрываем файл с коммитами
        lines = commit_file.readlines() 

        for line in lines:
            parts = line.rstrip('\n').split(' ')                # Разделяем строку на имя, хеш, время
            if parts[0] not in list(contributors_score.keys()): # Если имени контрибъютора нет в ключах contributors_score
                contributors_score[parts[0]] = 0                # создаем ключ и присваиваем ему 0
            else:
                contributors_score[parts[0]] += 1               # если имя есть, увеличиваем значение (количество коммитов)

    cnt_list = [0, 0, 0]    # Количество коммитов в тройке самых активных
    names = ['', '', '']    # Имена самых активных

    for i in range(3):
        # Ищем контрибъютора с максимальным рейтингом зи оставшихся
        for name, count in contributors_score.items():
            if count > cnt_list[i]:    # Если количество коммитов у контрибъютора с именем name больше максимального значения 
                cnt_list[i] = count    # Запоминаем его рейтинг и имя
                names[i] = name

        contributors_score.pop(names[i]) # Удаляем контрибъютора с максимальным рейтингом из словаря

    with open('result.txt', 'w', encoding='utf-8') as res_file:
        for name in names:
            res_file.write(name+'\n')

if __name__ == '__main__':
    active_rating('commits.txt')    