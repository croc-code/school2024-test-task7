
class FileManager:
    """
    Represents a file manager
    """

    def read(self, file_name: str) -> list[str]:
        """
        Reads a file and returns its contents.
        :param file_name: Name of the file to read.
        :return: Contents of the file.
        """
        with open(file_name, 'r') as f:
            return f.readlines()

    def write(self, file_name: str, lines: list[str]) -> None:
        """
        Writes the contents of the file to file.
        :param file_name: Name of the file to write.
        :param lines: List of lines to write.
        """
        with open(file_name, mode='w') as file:
            for line in lines:
                file.write(line + '\n')
