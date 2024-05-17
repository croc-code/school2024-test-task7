from app.classes.commits import *
from app.classes.contributor import *
from file_manager import *
from typing import List, Dict


class ContributorList:
    contributors_dict: Dict[str, Contributor] = {}

    def __init__(self):
        self.contributors_dict = {}

    def _add_contributor(self, contributor: Contributor):
        self.contributors_dict[contributor.name] = contributor

    def add_line_raw(self, line: str) -> bool:
        line_list: List[str] = line.split(" ")
        if len(line_list) != 3:
            return False

        name: str = line_list[0]
        c_hash: str = line_list[1]
        dt_str: str = line_list[2]
        if name not in self.contributors_dict:
            self._add_contributor(Contributor(name))
        else:
            current_contributor: Contributor = self.contributors_dict[name]
            current_contributor.add_commit_raw(c_hash, dt_str)

