from itertools import *
from collections import*
import re
from functools import *

string = ""
rules = {}
string,rls = open("i1").read().split("\n\n")
for i in rls.strip().split("\n"):
    a,b = i.split(" -> ")
    rules[a] = b

cntr = Counter([string[i:i+2] for i in range(len(string)-1)])
for _ in range(40):
    temp_cntr = Counter()
    for keys,val in cntr.items():
        if keys not in rules:
            continue
        temp_cntr[keys[0]+rules[keys]] += val 
        temp_cntr[rules[keys]+keys[1]] += val 
    cntr = temp_cntr
    if _ in [9,39]:
        res_cntr = Counter()
        for keys in cntr:
            res_cntr[keys[0]] += cntr[keys]
        # NASTY OFF BY ONE BECAUSE OF ADDED CHAR IN THE END
        res_cntr[string[-1]] += 1
        print(max(res_cntr.values()) - min(res_cntr.values()))


