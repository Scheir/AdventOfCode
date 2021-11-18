import re
arr = []
with open("i1") as file:
    for l in file:
        lst = re.split(",?\s", l.rstrip())
        arr.append((lst[0], lst[1:]))
n = len(arr)
for x in (0,1):
    mem = {'a':x, 'b':0}
    idx = 0
    while idx < n:
        ins,lst = arr[idx]
        reg = lst[0]
        if ins == "hlf":
            mem[reg] //= 2
        elif ins == "tpl":
            mem[reg] *= 3
        elif ins == "inc":
            mem[reg] += 1
        elif ins == "jmp":
            idx += int(reg)
            continue
        elif ins == "jie":
            if mem[reg] % 2 == 0:
                idx += int(lst[1])
                continue
        elif ins == "jio":
            if mem[reg] == 1:
                idx += int(lst[1])
                continue
        idx += 1
    print(mem['b'])

