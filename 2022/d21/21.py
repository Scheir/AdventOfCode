arr = []
for row in open("i1"):
    arr.append(row.strip())

d = {}
for row in arr:
    a,b = row.split(": ")
    d[a] = int(b) if b.isnumeric() else b

def solve(x,p2=False):
    v = d.get(x)
    ret = 0
    if x == "root":
        lhs,oper,rhs = v.split()
        return solve(lhs) + (-solve(rhs) if p2 else solve(rhs)) 
    if type(v) == int:
        return v
    else:
        lhs,oper,rhs = v.split()
        if oper == "+":
            ret = solve(lhs) + solve(rhs)
        if oper == "-":
            ret = solve(lhs) - solve(rhs)
        if oper == "/":
            ret =  solve(lhs) / solve(rhs)
        if oper == "*":
            ret = solve(lhs) * solve(rhs)

    return ret

print(int(solve("root")))

def binary_search(low, high):
    m = (low+high)//2
    d["humn"] = m
    ret = solve("root",p2=True)
    if ret == 0:
        return m
    elif ret > 0:
        return binary_search(m,high)
    else:
        return binary_search(low,m)

ret = binary_search(0,100000000000000000)
print(ret)
