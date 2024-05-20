import os
from typing import Union, List


def search_file(file_name: str) -> Union[str, None]:
    """
    Search for a file in the current directory and return its path.
    :param file_name: The name of the file to search for.
    :return: The path to the file.
    """

    # get root directory
    root_dir = os.getcwd()

    # get list of files in the current directory
    file_list = os.listdir()
    if file_name in file_list:
        return os.path.join(root_dir, file_name)

    # cycle through the directories until the file is found
    for root, dirs, file in os.walk(root_dir):
        if file_name in file:
            return os.path.join(root, file_name)
    return None


def read_file(file_path: str) -> Union[List[str], None]:
    """
    Read the contents of a file.
    :param file_path: The path to the file.
    :return: The list of lines in the file.
    """

    if not os.path.exists(file_path):
        return None

    with open(file_path, 'r') as f:
        return (f.read()).split('\n')


def write_file(file_name: str, text: str) -> None:
    """
    Creates a new file (or overwrites an existing file) in the root directory and writes the given text to it.
    :param file_name: The name of the file to create or overwrite.
    :param text: The text to write to the file.
    """

    root_dir = os.getcwd()
    file_path = os.path.join(root_dir, file_name)

    with open(file_path, 'w') as f:
        f.write(text)

