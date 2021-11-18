import copy
def encode(s):
    new_string = ""
    for x in s:
        if x == '"':
            new_string += "\\\""
        elif x == "\\":
            new_string += "\\\\"
        else:
            new_string += x
    return len(new_string)+2

arr = []
with open("i1") as file:
    for l in file:
        arr.append(list(l.rstrip()))

res = 0
total = 0
arr2 = copy.deepcopy(arr)
for l in arr:
    total += len(l)
    escapes = 0
    for x in range(len(l)-1):
        c = l[x]
        if c == '\\':
           if l[x+1] in ('\\', '"'):
               escapes += 1
               l[x+1] = "+"
           else:
               escapes += 3
    res += len(l) - 2 - escapes

res = total - res 
print(res)

res2 = 0
for l in arr2:
    res2 += encode(l)

res2 = res2 - total
print(res2)



