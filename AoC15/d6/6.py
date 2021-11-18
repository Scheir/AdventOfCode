arr = []
with open("i1") as file:
    for line in file:
        la = line.rstrip().split(" ")
        if la[0] == "toggle":
            arr.append((la[0], la[1], la[3]))
        else:
            arr.append((la[1], la[2], la[4]))


vec = [[0]*1000 for x in range(1000)]
vec2 = [[0]*1000 for x in range(1000)]
for x in arr:
    a,b,c = x
    b = b.split(",")
    c = c.split(",")
    for dx in range(int(b[0]), int(c[0])+1):
        for dy in range(int(b[1]), int(c[1])+1):
            if a == "toggle":
                vec[dx][dy] = 1 if vec[dx][dy] == 0 else 0
                vec2[dx][dy] += 2 
            elif a == "off":
                vec[dx][dy] = 0
                vec2[dx][dy] = max(0, vec2[dx][dy]-1)
            elif a == "on":
                vec[dx][dy] = 1
                vec2[dx][dy] += 1
res, res2 = 0,0
for x in vec:
    res += x.count(1)
print(res)
for x in vec2:
    res2 += sum(x)
print(res2)
