lines = []
with open("i1") as file:
    lines = file.readlines()

arr = []
for line in lines:
    x,y,z = line.split('x')
    arr.append((int(x), int(y), int(z)))
    
res = 0
for l,w,h in arr:
    a,b,c = 2*l*w, 2*w*h, 2*h*l 
    res += a+b+c+min(a,b,c)//2 
print(res)

res2 = 0
for l,w,h in arr:
    lst = sorted([l,w,h])
    a, b = lst[0], lst[1] 
    res2 += 2*a + 2*b + l*w*h
print(res2)

