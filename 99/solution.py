#!/usr/bin/env python3

from math import log

def read_pairs(filename):
    lines = open(filename, "rt").readlines()
    for k, v in [x.strip().split(',') for x in lines]:
        yield (int(k), int(v))

def main():
    best_base, best_index = 1, 1
    count = 0
    ans = 0
    for base, index in read_pairs("base_exp.txt"):
        count += 1
        if best_index * log(best_base) < index * log(base):
            best_base, best_index = base, index
            ans = count
    print(ans)


if __name__ == "__main__":
    main()
