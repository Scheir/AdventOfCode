class node:
    def __init__(self,name,p):
        self.name = name #Dir name
        self.parent = p #Parent dir 
        self.dirs = set() #Child dirs
        self.files = {} #Files in dir
        self.size = 0 #Total recursive size of dir
    def __str__(self):
        return f'{self.name}, {self.size}'

# Could wrap all of these in a tree class.. 
# With search, insert etc..
# Set all values
def set_all_values(n):
    # The files in (n) dir
    n.size = sum(n.files.values())
    for x in n.dirs:
        set_all_values(x)
        n.size += x.size 
        
#Get all values
def get_all_values(n):
    ret = [n.size]
    for x in n.dirs:
        ret.extend(get_all_values(x))
    return ret

# DFS Print nodes
def print_folder_structure(n, level=0):
    print(f"{'  '*level} - {n.name} (dir, tot size={n.size}")
    for x in n.dirs:
        # print folders
        print_folder_structure(x,level+1)
    #print files
    for x,s in n.files.items():
        print(f"{'  '*(level+1)} - {f'{x}, size={s}'} (file)")

# Populate tree
arr = [x.strip() for x in open("i1")]
root = node("/", None)
for row in arr:
    cur = row.split()
    if cur[1] == "cd":
        arg = cur[2]
        if arg == "..":
            n = n.parent
        elif arg == "/":
            n = root
        else:
            try:
                n = next((x for x in n.dirs if x.name == arg))
            except Exception:
                print(f"{arg}: No such file or directory")

    elif cur[0] != "$":
        a,b = cur 
        if a == "dir":
            # Create the dir if it doesnt exist
            if not any(x.name == b for x in n.dirs):
                n.dirs.add(node(b, n))
        else:
            # Add the file and size to n.files
            n.files  |= {b:int(a)}


set_all_values(root)

print("## FOLDER STRUCTURE ##")
print_folder_structure(root)
print("## END FOLDER STRUCTURE\n")

values = get_all_values(root)
print("P1:", sum(x for x in values if x < 100000))

# P2
NEEDED = root.size - (70000000 - 30000000)
print("P2", min(x for x in values if x > NEEDED))
