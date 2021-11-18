import re
def rules(string):
    ok = not re.search("[iol]", string) 
    if ok:
        ok = False
        for x in range(len(string)-2):
            a,b,c = string[x:x+3]
            if ord(a) == ord(b)-1 and ord(b) == ord(c)-1:
                ok = True
                break
    if ok:
        s = set(sorted(list(string)))
        ss = set() 
        for x in s:
            if string.count(x+x) >= 1:
                if x == 'z':
                    if 'a' not in ss:
                        ss.add(x)
                else: 
                    if chr(ord(x)-1) not in ss:
                        ss.add(x)
    return ok and len(ss) >= 2

def increment(string):
    arr = list(string)
    idx = -1
    while arr[idx] == 'z':
        arr[idx] = 'a'
        idx -= 1
    arr[idx] = chr(ord(string[idx])+1)
    return ''.join(arr)

test = "hxbxwxba"
test1 = "ghiaasdbb"


while not rules(test):
    test = increment(test)
print(test)

test = increment(test)
while not rules(test):
    test = increment(test)
print(test)
