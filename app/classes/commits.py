from typing import List, Dict, Union
import re
from datetime import datetime as dt
import logging

commit_regex = re.compile(r"[a-z0-9]{7}")
date_mask_mil = "%Y-%m-%dT%H:%M:%S.%f"
date_mask_sec = "%Y-%m-%dT%H:%M:%S"


class Commit:
    """Class to represent a commit"""
    c_hash: str = None
    datetime: dt = None

    @staticmethod
    def _get_date(dt_str: str) -> Union[dt.time, None]:
        try:
            if "." in dt_str:
                return dt.strptime(dt_str, date_mask_mil)
            else:
                return dt.strptime(dt_str, date_mask_sec)
        except ValueError:
            return None

    @staticmethod
    def _check_hash(c_hash: str) -> bool:
        return bool(re.fullmatch(commit_regex, c_hash))

    def __new__(cls, *args, c_hash: str = None, dt_str: str = None, **kwargs):
        if c_hash is None and dt_str is None and len(args) == 2:
            c_hash = args[0]
            dt_str = args[1]
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
        """
        Check if the commit is valid
        :return: True if valid, False otherwise
        """
        if self.hash is not None and self.datetime is not None:
            return True
        return False



