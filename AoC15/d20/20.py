from collections import defaultdict
from itertools import combinations
from functools import reduce
import math
def primes(n):
    d = []
    d.append(1)
    while n%2 == 0:
        d.append(2)
        n //= 2

    for x in range(2, int(math.sqrt(n))+1):
        while n % x == 0:
            d.append(x)
            n //= x
    d.append(n) 
    return d
    
def get_res(num):
    l = primes(num)
    tres = 0
    s = set()
    for i in range(1, len(l)):
        for c in combinations(l, i):
            r = reduce(lambda a,b: a*b, c)
            if not r in s and r <= num:
                tres += r*10
                s.add(r)
    return tres
    
def get_res2(num):
    l = primes(num)
    tres = 0
    s = set()
    for i in range(1, len(l)):
        for c in combinations(l, i):
            r = reduce(lambda a,b: a*b, c)
            if not r in s and r <= num:
                if num // r <= 50:
                    tres += r*11
                s.add(r)
    return tres
    
idx1 = 10000
while get_res(idx) < 34000000:
    idx1 += 1
print(idx1)

idx = 10000
while get_res2(idx) < 34000000:
    idx += 1

print(idx)
