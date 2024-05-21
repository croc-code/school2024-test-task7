from components.FileManager import FileManager
from components.CommitsHandler import CommitsHandler

'''
Данный файл имитирует работу приложения

Сначала мы считываем данные, затем запускаем обработчика коммитов

Далее формируем список-ответ на поставленную задачу

В случае, если в процессе работы программы произошла ошибка, программа выведет сообщение и завершит работу

В ином случае программа запишет результат в файл result.txt и выведет сообщение об успешном выполнении
'''


data = FileManager.read("commits.txt")
handler = CommitsHandler(data)
result = handler.get_result()

if result:
    result = "\n".join(result)
    FileManager.write("result.txt", result)
    print("Program has been finished successfully!")
else:
    print("Invalid string format in input file (commits.txt)")
