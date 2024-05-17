from typing import List, Dict, Tuple, Set
from app.classes.commits import Commit
import re
import logging

name_regex = re.compile(r"[A-Za-z][A-Za-z0-9_]+")


class Contributor:
    name: str = None
    commits_list: List[Commit] = None

    def __new__(cls, *args, name: str = None, **kwargs):
        if name is None and len(args) == 1:
            name = args[0]
        if name is None:
            raise ValueError("Contributor name is required")
        if not name_regex.fullmatch(name):
            raise ValueError("invalid contributor name")
        return super().__new__(cls)

    def __init__(self, name: str):
        self.name = name
        self.commits_list = []

    def add_commit_raw(self, c_hash: str, dt_str: str) -> Tuple[bool, str]:
        try:
            commit = Commit(c_hash=c_hash, dt_str=dt_str)
        except ValueError as e:
            return False, e.args[0]

        self.commits_list.append(commit)
        return True, ""

    def add_commit(self, commit: Commit):
        self.commits_list.append(commit)

    def get_commits_amount(self) -> int:
        return len(self.commits_list)


if __name__ == "__main__":
    contributors = Contributor(name="")
    print(contributors.name)


