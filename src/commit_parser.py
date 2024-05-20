import re
from datetime import datetime, timedelta


class CommitParser:
    """
    Parses commit messages.
    """
    name_pattern = r'^[a-zA-Z_]+\w*'
    commit_pattern = r'[a-z0-9]{7}'
    date_format = '%Y-%m-%dT%H:%M:%S'

    def __init__(self):
        self.name_regex = re.compile(self.name_pattern)
        self.commit_regex = re.compile(self.commit_pattern)

    def _get_date(self, date: str) -> datetime or None:
        """
        Parses the date string and returns it as a datetime object.
        :param date: String date to parse
        :return: If success, returns datetime else None
        """
        try:
            return datetime.strptime(date, self.date_format)
        except Exception:
            return None

    def _is_valid_name(self, name: str) -> bool:
        """
        Checks if the name is valid.
        :param name: String name to check
        :return: If valid, returns True else False
        """
        return bool(self.name_regex.fullmatch(name))

    def _is_valid_c_hash(self, commit: str) -> bool:
        """
        Checks if the commit hash is valid.
        :param commit: String commit hash to check
        :return: If valid, returns True else False
        """
        return bool(self.commit_regex.fullmatch(commit))

    def _is_valid_date(self, date: str) -> bool:
        """
        Checks if the date string is valid.
        :param date: String date to check
        :return: If valid, returns True else False
        """
        if c_date := self._get_date(date):
            cur_date = datetime.now()
            return cur_date - c_date <= timedelta(weeks=4)
        return False

    def parse(self, line: str) -> list[str] or None:
        """
        Parses a line of commit messages.
        :param line: String line to parse
        :return: Parsed line if line is valid else None
        """
        line_args = line.split()
        if len(line_args) != 3:
            return None
        name, commit, date = line_args
        if self._is_valid_name(name) and self._is_valid_c_hash(commit) and self._is_valid_date(date):
            return line_args
