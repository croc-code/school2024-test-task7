import re
from datetime import datetime, timedelta


class CommitParser:
    name_pattern = r'^[a-zA-Z_]+\w*'
    commit_pattern = r'[a-z0-9]{7}'
    date_format = '%Y-%m-%dT%H:%M:%S'

    def __init__(self):
        self.name_regex = re.compile(self.name_pattern)
        self.commit_regex = re.compile(self.commit_pattern)

    def _get_date(self, date):
        try:
            return datetime.strptime(date, self.date_format)
        except Exception:
            return None

    def _is_valid_name(self, name):
        return self.name_regex.fullmatch(name)

    def _is_valid_c_hash(self, commit):
        return self.commit_regex.fullmatch(commit)

    def _is_valid_date(self, date):
        if c_date := self._get_date(date):
            cur_date = datetime.now()
            return cur_date - c_date <= timedelta(weeks=4)
        return False

    def parse(self, line):
        line_args = line.split()
        if len(line_args) != 3:
            return None
        name, commit, date = line_args
        if self._is_valid_name(name) and self._is_valid_c_hash(commit) and self._is_valid_date(date):
            return line_args
