from .file_manager import FileManager
from .commit_parser import CommitParser
from collections import defaultdict


class Analyser:

    def generate_report(self, input_file_name, output_file_name):
        try:
            contributors = defaultdict(int)
            file_parser = FileManager()
            commit_parser = CommitParser()
            for line in file_parser.read(input_file_name):
                parsed_line = commit_parser.parse(line)
                if parsed_line:
                    contributors[parsed_line[0]] += 1
            file_parser.write(output_file_name, sorted(contributors.keys(),
                                                   key=lambda key: contributors[key], reverse=True)[:3])
        except Exception as e:
            print(e)
