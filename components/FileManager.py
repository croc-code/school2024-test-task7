import os

'''
Данный файл реализует файловый менеджер

Файловый менеджер реализован в виде паттерна Singletone, что гарантирует единственность экземпляра

Также реализованы статические методы для чтения и записи данных
'''


class FileSingleton(type):
    __instance = None

    def __call__(cls, *args, **kwargs):
        if FileSingleton.__instance is None:
            FileSingleton.__instance = super(FileSingleton, cls).__call__(*args, **kwargs)
        return FileSingleton.__instance


class FileManager(metaclass=FileSingleton):
    @staticmethod
    def read(file):
        if not os.path.exists(file):
            return None

        with open(file, 'r') as f:
            return (f.read()).split('\n')

    @staticmethod
    def write(file, data):
        with open(file, 'w') as result:
            result.writelines(data)
