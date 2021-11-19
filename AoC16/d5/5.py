from hashlib import md5
word = "uqwqemis"
idx = 1
pword = ""
pword2 = [' ']*8
while len(pword) != 8 or pword2.count(' ') > 0:
    search_string = word + str(idx)
    h = md5(search_string.encode())
    lst = list(h.hexdigest())[:7]
    if lst[:5].count('0') == 5:
        if len(pword) != 8:
            pword += lst[-2]
        if lst[-2].isdigit() and int(lst[-2]) < 8 and pword2[int(lst[-2])] == " ":
            pword2[int(lst[-2])] = lst[-1]
    idx += 1

print(pword)
print(''.join(pword2))
