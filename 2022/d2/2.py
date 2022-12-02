arr = []
for row in open("i1"):
    X = row.strip().split()
    arr.append(X)

POINTS = {"X":1, "Y":2, "Z":3}
WINNER = {"AX":3, "AY":6, "AZ":0,
          "BX":0, "BY":3, "BZ":6,
          "CX":6, "CY":0, "CZ":3}
T= {"AX": "Z", "BX": "X", "CX": "Y",
    "AY": "X", "BY": "Y", "CY": "Z",
    "AZ": "Y", "BZ": "Z", "CZ": "X"}

print(sum(POINTS[ME]+WINNER[YOU+ME] for YOU,ME in arr))
print(sum(POINTS[T[YOU+ME]]+WINNER[YOU+T[YOU+ME]] for YOU,ME in arr))
