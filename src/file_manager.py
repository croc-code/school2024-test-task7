
class FileManager:

    def read(self, file_name):
            with open(file_name, 'r') as f:
                return f.readlines()

    def write(self, file_name, lines):
        with open(file_name, mode='w') as file:
            for line in lines:
                file.write(line + '\n')
