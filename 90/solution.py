import sys

sets = set()
SQUARES = ['01', '04', '09', '16', '25', '36', '49', '64', '81']
OPT_SQUARES = [x.replace('9', '6') for x in SQUARES]

def gen(count, digit, set):
    if count == 6:
        sets.add(set)
        return
    if digit > 9:
        return
    gen(count, digit+1, set)
    nset = set + chr(digit+ord('0'))
    gen(count+1, digit+1, nset)

def obtains(cube, digit):
    if digit in cube:
        return True
    if digit == '9' or digit == '6':
        return '9' in cube or '6' in cube
    return False

def match(one, two):
    for s in OPT_SQUARES:
        ok = False
        if obtains(one, s[0]) and obtains(two, s[1]):
            ok = True
        if obtains(one, s[1]) and obtains(two, s[0]):
            ok = True
        if not ok:
            return False
    return True

gen(0, 0, "")

ans = 0
for ar1 in sets:
    for ar2 in sets:
        if ar2 < ar1:
            continue
        if match(ar1, ar2):
            ans = ans + 1
print ans

