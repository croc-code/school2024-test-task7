import random
import string
from faker import Faker

fake = Faker()

def generate_commit_hash():
    return ''.join(random.choices(string.hexdigits[:16], k=7))

def generate_commit_line(usernames):
    username = random.choice(usernames)
    commit_hash = generate_commit_hash()
    commit_date = fake.iso8601(tzinfo=None)
    return f"{username} {commit_hash} {commit_date}"

def generate_usernames(num_users):
    return [fake.user_name() for _ in range(num_users)]

def generate_commit_file(filename, num_lines, num_users):
    usernames = generate_usernames(num_users)
    with open(filename, 'w') as file:
        for _ in range(num_lines):
            print(_)
            file.write(generate_commit_line(usernames) + '\n')

if __name__ == "__main__":
    generate_commit_file('commits.txt', 100000, 1000)
