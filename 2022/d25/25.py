from collections import deque
arr = []
for row in open("i1"):
    arr.append(row.strip())


def to_deci(x):
    ret = 0
    i = 0
    for v in x[::-1]:
        if v == "2":
            ret += (2*(5**i))
        if v == "1":
            ret += (5**i)
        if v == "-":
            ret -= (5**i)
        if v == "=":
            ret -= 2*(5**i)
        i+=1
    return ret


res = sum(to_deci(x) for x in arr)
vals = ["2","1","0","-","="]
for i in range(20):
    if res < (2*(i**5)):
        break

NUMS = i+1
winner = ["2"]*NUMS

for i in range(len(winner)):
    cand = winner.copy()
    for v in vals:
        cand[i] = v
        if to_deci(cand) >= res:
            winner = cand.copy()


print(''.join(winner))
