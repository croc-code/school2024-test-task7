# Тестовое задание для отбора на Летнюю ИТ-школу КРОК по разработке

## Условие задания
Будучи тимлидом команды разработки, вы получили от менеджера проекта задачу повысить скорость разработки. Звучит, как начало плохого анекдота, но, тем не менее, решение вам все же нужно найти. В ходе размышлений и изучений различного внешнего опыта других команд разработки вы решили попробовать инструменты геймификации. То есть применить техники и подходы игрового характера с целью повышения вовлеченности команды в решение задач.

Вами была придумана рейтинговая таблица самых активных контрибьютеров за спринт. Что это значит в теории: по окончании итерации (4 рабочие недели) выгружается список коммитов, сделанных в релизную ветку продукта, и на его основе вычисляются трое самых активных разработчиков, сделавших наибольшее количество коммитов. В зависимости от занятого места, разработчик получает определенное количество внутренней валюты вашей компании, которую он впоследствии может обменять на какие-то товары из внутреннего магазина.

На практике вы видите решение следующим образом: на следующий день после окончания спринта в 00:00 запускается автоматическая процедура, которая забирает файл с данными о коммитах в релизную ветку, сделанных в период спринта, после чего выполняется поиск 3-х самых активных контрибьютеров. Имена найденных разработчиков записываются в файл, который впоследствии отправляется вам на почту.

В рамках практической реализации данной задачи вам необходимо разработать процедуру формирование отчета “Топ-3 контрибьютера”. Данная процедура принимает на вход текстовый файл (commits.txt), содержащий данные о коммитах (построчно). Каждая строка содержит сведения о коммите в релизную ветку в формате: “_<Имя пользователя> <Сокращенный хэш коммита> <Дата и время коммита>_”.
Например: AIvanov 25ec001 2024-04-24T13:56:39.492

К данным предъявляются следующие требования:
- имя пользователя может содержать латинские символы в любом регистре, цифры (но не начинаться с них), а также символ "_";
- сокращенный хэш коммита представляет из себя строку в нижнем регистре, состояющую из 7 символов: букв латинского алфавита, а также цифр;
- дата и время коммита в формате YYYY-MM-ddTHH:mm:ss.

В результате работы процедура формирует новый файл (result.txt), содержащий информацию об именах 3-х самых активных пользователей по одному в каждой строке в порядке убывания места в рейтинге. Пример содержимого файла:
AIvanov
AKalinina
CodeKiller777

Ручной ввод пути к файлу (через консоль, через правку переменной в коде и т.д.) недопустим. Необходимость любых ручных действий с файлами в процессе работы программы будут обнулять решение.

## Автор решения
Сибова Вероника Сергеевна
- [Telegram](https://web.telegram.org/k/): @nikusick888
- e-mail: nika.sibova.03@inbox.ru

## Описание реализации

В рамках поставленной задачи мной было реализовано три класса:
1) FileManager
2) CommitParser
3) Analyser

### FileManager
Класс для работы с файлами

Функции:
- **public:**
  - Чтение из файла(read)
    > [!CAUTION]
    > Файл **commits.txt** должен находиться в рабочей директории! В противном случае будет выведена ошибка.

  - Запись в файл(write)
    > [!IMPORTANT]
    > После работы программы файл **result.txt** будет находиться в рабочей директории (там же, где и commits.txt).

### CommitParser
Класс для работы с коммитами

Функции:
- **public:**
  - Парсинг строки(parse)<br>
  На вход функция принимает необработанную строку. Если строка валидна, то функция возвращает разобранную на компоненты строку. В противном случае возвращает None.
- **private:**
  - Валидация имени(_is_valid_name)<br>
  Для валидации имени был использован модуль re.
  - Валидация хэша коммита(_is_valid_c_hash)<br>
  Для валидации хэша был использован модуль re. 
  - Валидация даты(_is_valid_date)<br>
  Параметры валидности:
    * Дата соответствует заданному формату
    * Разница между датой запуска программы и датой создания коммита должна быть меньше или равной 4 неделям (из условий задачи)
  - Получение даты(_get_date)<br>
  На вход функция принимает строку, которую пытается преобразовать в объект типа datetime.datetime. 
  В случае успеха возвращает полученный объект, в случае неудачи ворвращает None.

### Analyser 
Класс для получения результатов анализа и формирования отчета.

Функции:
- **public:**
  * Формирование отчета(generate_report)<br>
  Данная функция берет данные из commits.txt, обрабатывает их и формирует топ-3 лучших работника, которые потом записываются в result.txt.

## Инструкция по сборке и запуску решения

Запуск процедуры осуществляется после клонирования репозитория. Установка дополнительных библиотек не требуется.
```console
$ git clone https://github.com/nikusick/school2024-test-task7.git
$ python main.py
```