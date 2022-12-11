arr = [row.strip() for row in open("i1")]

def cycle(idx,x,CRT):
    div,mod = divmod(idx-1,40)
    in_range = x-((idx-1)%40)
    CRT[div][mod] = "#" if <= 1 else ' '
    if idx == 20 or (idx-20)%40 == 0:
        return x * idx
    return 0
    
CRT = [['.'] * 40 for _ in range(6)]
x = 1
res = 0
idx = 0
for row in arr:
    if row == "noop":
        idx += 1 
        res += cycle(idx,x,CRT) 
        continue
    a,b = row.split()
    idx += 1
    res += cycle(idx,x,CRT) 
    idx += 1
    res += cycle(idx,x,CRT) 
    x += int(b)

print(res)
for row in CRT:
    print(''.join(row))
