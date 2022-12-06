s = open("i1").read().strip()
print(next(i+4 for i in range(len(s)) if len(set(s[i:i+4])) == 4))
print(next(i+14 for i in range(len(s)) if len(set(s[i:i+14])) == 14))
