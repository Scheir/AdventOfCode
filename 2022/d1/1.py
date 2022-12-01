arr = []
s = 0
for row in open("i1"):
    if row == "\n":
        arr.append(s)
        s = 0
    else:
        s += int(row.strip())

print("P1:", max(arr))
print("P2:", sum(sorted(arr)[-3:]))
