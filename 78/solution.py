#! /usr/bin/env python

import math
import os

def zeroes_count(x):
    if x == 0:
        return 1
    if x % 10 == 0:
        return zeroes_count(x / 10) + 1
    return 0

n = 10000
d = [[1]]
for i in xrange(1, n + 1):
    d.append([0 for _ in xrange(i + 1)])
    d[i][i] = 1
    for k in reversed(xrange(1, i)):
        if i - k >= k:
            d[i][k] = d[i][k] + d[i - k][k]
        d[i][k] = d[i][k] + d[i][k + 1]
        d[i][k] = d[i][k] % 100000
p = zip([x[1] if len(x) > 1 else x[0] for x in d], range(n + 1))
p.sort()
print p[:10]
