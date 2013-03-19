#! /usr/bin/env python

def mul(coefs, other):
    return [other[0] * coefs[0] + 2 * other[1] * coefs[1],
            other[0] * coefs[1] + other[1] * coefs[0]]

def pair_pow(coefs, index):
    if index == 0:
        return [1, 0]
    return mul(coefs, pair_pow(coefs, index - 1))

def main():
    index = 1
    coefs = [1, 1]
    limit = 2 * 10**12 - 1
    while coefs[0] <= limit:
        coefs = mul(coefs, [1, 1])
    print (coefs[0] + 1) / 2, (coefs[1] + 1) / 2

if __name__ == "__main__":
    main()
