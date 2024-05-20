from app.file_manager import search_file, read_file, write_file
from app.task import get_leaders
import logging
import os

logging.basicConfig(
    filename=os.path.join("log.txt"),
    filemode='a',
    format='%(asctime)s,%(msecs)d - %(name)s - %(levelname)s: %(message)s',
    datefmt='%H:%M:%S',
    level=logging.INFO
)

logger = logging.getLogger("main")

if __name__ == "__main__":
    path = search_file("commits.txt")
    if not path:
        logger.error("File commits.txt not found")
        exit(1)
    file_lines = read_file(path)
    leaders = get_leaders(file_lines)
    write_file("result.txt", leaders)
