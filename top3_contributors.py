contributors = {}
name_top1 = ''
name_top2 = ''
name_top3 = ''

count_top1 = -1
count_top2 = -1
count_top3 = -1

with open("commits.txt", "r") as file:
    for line in file.readlines():
        name = line.split()[0]
        # line.split == [name, hash, date]
        contributors[name] = contributors.get(name, 0) + 1

for name, count in contributors.items():
    if count <= count_top3:
        continue
    elif count < count_top2:
        # записать третье место
        name_top3 = name
        count_top3 = count
    elif count < count_top1:
        # сместить второе место на третье
        name_top3 = name_top2
        count_top3 = count_top2
        # записать второе место
        name_top2 = name
        count_top2 = count
    else:
        # сместить второе место на третье
        name_top3 = name_top2
        count_top3 = count_top2
        # сместить первое место на второе
        name_top2 = name_top1
        count_top2 = count_top1
        # записать первое место
        name_top1 = name
        count_top1 = count

with open("result.txt", "w") as file:
    file.write(name_top1)
    file.write("\n")
    file.write(name_top2)
    file.write("\n")
    file.write(name_top3)
