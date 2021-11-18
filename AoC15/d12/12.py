import re
import json

def solve(d):
    if type(d) == int:
        return d
    elif type(d) == list:
        return sum([solve(x) for x in d])
    elif type(d) != dict:
        return 0
    elif "red" in d.values():
        return 0
    return sum([solve(x) for x in d.values()]) 

arr = []
with open("i1") as file:
    for l in file:
        arr.append(l.rstrip())

res = 0
for l in arr:
    res += sum([int(x) for x in re.findall("-?\d+", l)])

with open('i1') as json_file:
    data = json.load(json_file)

print(solve(data))
