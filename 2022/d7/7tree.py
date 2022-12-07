class node:
    def __init__(self,name,p):
        self.name = name
        self.p = p
        self.neigh = [] 
        self.v = 0 
    def __str__(self):
        return f'{self.name}, {self.v}'

arr = [x.strip() for x in open("i7.txt")]

# Set all values
def set_all_values(n):
    for x in n.neigh:
        set_all_values(x)
        n.v += x.v

def get_all_values(n):
    ret = [n.v]
    for x in n.neigh:
        ret.extend(get_all_values(x))
    return ret

# Populate tree
root = node("/", None)
for row in arr:
    cur = row.split()
    if cur[1] == "cd":
        arg = cur[2]
        if arg == "..":
            n = n.p
        elif arg == "/":
            n = root
        else:
            # Create node if it doesnt exist
            n = next((x for x in n.neigh if x.name == arg), node(arg,n))
    elif cur[0] != "$":
        a,b = cur 
        if a == "dir":
            # Create if it doesnt exist
            if not any(x.name == b for x in n.neigh):
                n.neigh.append(node(b, n))
        else:
            n.v += int(a)


set_all_values(root)
values = get_all_values(root)
print(sum(x for x in values if x < 100000))

# P2
NEEDED = root.v - (70000000 - 30000000)
print(min(x for x in values if x > NEEDED))
