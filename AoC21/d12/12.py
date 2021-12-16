from collections import defaultdict, deque
d = defaultdict(list)
for x in open("i1"):
    x = x.strip()
    a,b = x.split("-")
    d[a].append(b)
    d[b].append(a)
print(d)

def solve(ok=False):
    res = 0
    q = deque()
    q.append(("start", set(["start"]),True))
    while q:
        cur, s, twice = q.popleft()
        if cur == "end":
            res += 1
            continue
        print(res)
        for child in d[cur]:
            if child not in s:
                ns = s.copy() 
                if child.islower():
                    ns.add(child)
                q.append((child, ns, twice))
            elif ok and twice and child not in ("start","end"): 
                q.append((child,s,False))

    return res

print(solve())
print(solve(True))
