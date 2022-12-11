from copy import deepcopy
from collections import deque
import re
class monkey:
    p2 = 1
    def __init__(self, items, oper, comp):
        self.items = deque(items)
        self.oper_str = oper 
        self.comp_nums = comp
        self.cnt = 0
        monkey.p2 *= comp[0]
    
    def __str__(self):
        return f'{self.items},{self.cnt}'
    
    def oper(self, num):
        old = num
        return eval(self.oper_str)

    def comp(self,num):
        div,m1,m2 = self.comp_nums
        return m1 if num % div == 0 else m2

    def append(self,item):
        self.items.append(item)
        
    def pop(self,p2=False):
        self.cnt += 1
        item = self.items.popleft() # Inspect
        item = self.oper(item)# Adjust worry level
        if p2:
            item %= monkey.p2 
        else:
            item //= 3
        idx = self.comp(item) # Which monkey to throw to
        return (item,idx)
        


MONKEYS = []
for mks in open("i1").read().split("\n\n"):
    _,a,b,c,d,e = mks.strip().split("\n")
    items = [int(x) for x in re.findall("\d+",a)]
    oper = b.split(" = ")[1].strip()
    comp = [int(x) for x in re.findall("\d+",c+d+e)]
    MONKEYS.append(monkey(items,oper,comp))


P2 = deepcopy(MONKEYS)
for _ in range(20):
    for monkey in MONKEYS:
        while monkey.items:
            item,idx = monkey.pop(False)
            MONKEYS[idx].append(item)

res = sorted([x.cnt for x in MONKEYS])
print(res[-1]*res[-2])

# P2
for _ in range(10000):
    for monkey in P2:
        while monkey.items:
            item,idx = monkey.pop(True)
            P2[idx].append(item)

res = sorted([x.cnt for x in P2])
print(res[-1]*res[-2])
