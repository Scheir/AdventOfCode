from hashlib import md5
string = "iwrupvqb"
idx = 1
p1 = True
while True:
    next_string = string+str(idx)
    h = md5(next_string.encode())
    if p1:
        arr = list(h.hexdigest())[:5]
        if arr.count('0') == 5:
            print(idx)
            p1 = False
    arrp2 = list(h.hexdigest())[:6]
    if arrp2.count('0') == 6:
        print(idx)
        exit()
    idx += 1
    
