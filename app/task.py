from app.classes.contributor import *
from typing import List, Dict
import logging

logger = logging.getLogger("Task")

class ContributorList:
    """
    A list of contributors
    """
    contributors_dict: Dict[str, Contributor] = {}

    def __init__(self):
        self.contributors_dict = {}

    def _add_contributor(self, contributor: Contributor):
        self.contributors_dict[contributor.name] = contributor

    def add_line_raw(self, line: str) -> Tuple[bool, str]:
        """
        Add a line to the contributor list
        :param line: The line to add to the list of contributors in the form of <name> <hash> <date>
        :return: True if the line is valid, False otherwise and the error message
        """
        line_list: List[str] = line.split(" ")
        if len(line_list) != 3:
            return False, "Invalid line"

        name: str = line_list[0]
        c_hash: str = line_list[1]
        dt_str: str = line_list[2]
        if name not in self.contributors_dict:
            try:
                current_contributor: Contributor = Contributor(name)
            except ValueError as e:
                return False, e.args[0]
            self._add_contributor(current_contributor)

        current_contributor: Contributor = self.contributors_dict[name]
        return current_contributor.add_commit_raw(c_hash, dt_str)

    def get_leaders(self) -> List[Contributor]:
        """
        Get the list of leaders from the contributor list
        :return: The list of 3 contributors with the most commits
        """

        return sorted(self.contributors_dict.values(), key=lambda x: (-x.get_commits_amount(), x.name.lower()))[:3]


def get_leaders(file_list: List[str]) -> str:
    """
    Get the list of leaders from the contributor list
    :param file_list: The list of lines to process from the file
    :return: String with 3 leaders with the most commits
    """
    logger.info("---------------- Starting task ----------------")
    contributor_list: ContributorList = ContributorList()
    for i, line in enumerate(file_list):
        result: Tuple[bool, str] = contributor_list.add_line_raw(line)
        if not result[0]:
            logger.warning(f"Faulty line {i + 1}: {result[1]}")
    logger.info("---------------- Ending task ----------------")
    resulting_string = "\n".join([c.name for c in contributor_list.get_leaders()])
    return resulting_string
