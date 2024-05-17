from app.file_manager import search_file, read_file
from app.task import do_task
import logging
import os

logging.basicConfig(
    filename=os.path.join("log.txt"),
    filemode='a',
    format='%(asctime)s,%(msecs)d - %(name)s - %(levelname)s: %(message)s',
    datefmt='%H:%M:%S',
    level=logging.INFO
)

path = search_file("input.txt")
do_task(read_file(path))