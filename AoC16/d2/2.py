arr = []
with open("i1") as file:
    for l in file:
        arr.append(list(l.rstrip()))
x,y = 1,1
res = []
for r in arr:
    for i in r:
        if i == "D":
            y = min(2, y+1)
        elif i == "L":
            x = max(0, x-1)
        elif i == "R":
            x = min(2, x+1)
        elif i == 'U':
            y = max(0, y-1)
    res.append(3*y+x+1)
print(''.join([str(x) for x in res]))

pad = [['0','0','1','0','0'],['0','2','3','4','0'],['5','6','7','8','9'],
['0','A','B','C','0'],['0','0','D','0','0']]

x,y = 0,2
res2 = []
for r in arr:
    for i in r:
        if i == "D":
            y = min(4, y+1) if y+1 <= 4 and pad[y+1][x] != '0' else y
        elif i == "L":
            x = max(0, x-1) if x-1 >= 0 and pad[y][x-1] != '0' else x
        elif i == "R":
            x = min(4, x+1) if x+1 <= 4 and pad[y][x+1] != '0' else x
        elif i == 'U':
            y = max(0, y-1) if y-1 >= 0 and pad[y-1][x] != '0' else y
    res2.append(pad[y][x])

print(''.join(res2))
