def solve(string):
    new_string = ""
    idx = 1
    cur = string[0]
    count = 1
    while idx != len(string):
        if string[idx] != cur:
            new_string += str(count) + str(cur)
            cur = string[idx]
            count = 1
        else:
            count += 1
        idx += 1
    return new_string + str(count) + str(cur)


string = "3113322113"
for x in range(50):
    string = solve(string)

print(len(string))
