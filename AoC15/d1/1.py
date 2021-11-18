lines = ""
with open("i1") as file:
    lines = file.readline()
print(lines.count("(") - lines.count(")"))

floor = 0
for x in range(len(lines)):
    s = lines[x]
    floor += 1 if s == '(' else -1 
    if floor < 0:
        print(x+1)
        exit()
