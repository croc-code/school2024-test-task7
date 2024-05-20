import string
import random
from datetime import datetime as dt
from datetime import timedelta

# line mask is: "{username} {short_hash} {time}"
# used to test workability
def generate() -> str:
    """
    Generates a random string
    :return: str of random string with mask line format of username, short hash, time
    :rtype: str
    """
    username = random.choice(string.ascii_letters) + ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(2))

    short_hash = ''.join(random.choice(string.ascii_lowercase + string.digits) for _ in range(7))

    date = dt.now() + timedelta(seconds=random.randint(0, 86400))
    time = date.strftime("%Y-%m-%dT%H:%M:%S")

    return f"{username} {short_hash} {time}\n"


if __name__ == "__main__":
    with open(f"commits.txt", "w") as f:
        for i in range(10000):
                f.write(generate())