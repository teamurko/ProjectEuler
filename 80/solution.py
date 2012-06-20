#! /usr/bin/env python

import math
import fractions
import collections

def is_square(n):
    if n < 0:
        return False
    if n <= 1:
        return True
    x = math.trunc(math.sqrt(n))
    return x * x == n

def fraction_expansion(n):
    if is_square(n):
        raise Exception("Argument should not be a square, but %d provided" % n)
    y = math.trunc(math.sqrt(n))

    a = 1
    b = 0
    c = 1
    while (True):
        r = (a * y + b) / c
        yield r
        a1 = c * a
        b1 = c * (r * c - b)
        c1 = a * a * n - (b - r * c) * (b - r * c)
        a = a1
        b = b1
        c = c1
        d = fractions.gcd(a, b)
        d = fractions.gcd(c, d)
        a = a / d
        b = b / d
        c = c / d

def finite_continued_fractions(n):
    coef = collections.deque([])
    for c in fraction_expansion(n):
        coef.appendleft(c)
        a = 1
        b = 0
        for d in coef:
            b, a = a, b
            a = a + d * b
        d = fractions.gcd(a, b)
        a = a / d
        b = b / d
        yield (a, b)

def square_roots(n):
    x = fractions.Fraction(1)
    yield x
    while True:
        x = (x + n / x) / 2
        yield x

def first_n_digits(n):
    if is_square(n):
        raise Exception("Argument should be non square") 
    gen = finite_continued_fractions(n)
    for i in range(200):
        gen.next()

    s = ''
    a, b = gen.next()
    for i in xrange(100):
        s = s + chr(ord('0') + a / b)
        a = a % b * 10
    ans = 0
    for i in s:
        ans = ans + ord(i) - ord('0')

    return ans

ans = 0
for i in xrange(2, 100):
    if not is_square(i):
        ans = ans + first_n_digits(i)
print ans
