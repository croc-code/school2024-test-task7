from typing import List, Dict, Union
import re
from datetime import datetime as dt

commit_regex = re.compile(r"[a-f0-9]{7}")
date_mask = "%Y-%m-%dT%H:%M:%S"


class Commit:
    c_hash: str = None
    datetime: dt = None

    @staticmethod
    def _get_date(dt_str: str) -> Union[dt.time, None]:
        try:
            return dt.strptime(dt_str, date_mask)
        except ValueError:
            return None

    @staticmethod
    def _check_hash(c_hash: str) -> bool:
        return bool(re.match(commit_regex, c_hash))

    def __new__(cls, *args, c_hash: str = None, dt_str: str = None, **kwargs):
        if c_hash is None:
            raise ValueError("Commit hash is required")
        if dt_str is None:
            raise ValueError("Date string is required")
        if not cls._check_hash(c_hash):
            raise ValueError("Invalid commit hash")
        if not cls._get_date(dt_str):
            raise ValueError("Invalid date string")
        return super().__new__(cls)

    def __init__(self, c_hash: str, dt_str: str):
        self.hash = c_hash
        self.datetime = self._get_date(dt_str)

    def validate(self) -> bool:
        if self.hash is not None and self.datetime is not None:
            return True
        return False



