#!/usr/bin/env python3

from itertools import takewhile, groupby, permutations
from functools import reduce

import sys

def flatten(l):
    result = []
    for element in l:
        if type(element) is list:
            result = result + flatten(element)
        else:
            result.append(element)
    return result

def unique(l):
    seen = set()
    return [x for x in l if x not in seen and not seen.add(x)]

def read_words(filename):
    return unique( \
        flatten( \
            [y[1:-1] for y in x.strip().split(',')] \
            for x in open(filename, 'r').readlines()))

def naturals():
    n = 0
    while True:
        yield n
        n += 1

def separated_by_length(l):
    result = { }
    for w in l:
        result.setdefault(len(w), []).append(w)
    return result

def choose(n, k):
    assert(n >= k)
    if k == 0:
        yield []
    elif n == k:
        yield list(range(0, n))
    else:
        for elem in choose(n - 1, k):
            yield elem
        for elem in choose(n - 1, k - 1):
            yield elem + [n - 1]

def categories(word):
    return sorted([len(list(v)) for k, v in groupby(sorted(word))])

def match(word, candidates):
    keys = "".join(list(set(word)))
    if len(keys) > 10:
        print("There are words with > 10 different letters: " + word)
        return 0
    results = []
    candidates_group = { }
    for key, value in map(lambda x: ("".join(sorted(x)), x), candidates):
        candidates_group.setdefault(key, []).append(value)
    candidates_group = [(k, v) for k, v in candidates_group.items()
                        if len(v) > 1]
    if len(candidates_group) == 0:
        return 0
    print(word, len(candidates_group))
    word_categories = categories(word)
    result = 0
    for key, value in candidates_group:
        if word_categories == categories(key):
            result = reduce(max, map(int, value), result)
    return result

def max_match(w, v, squares):
    letters = "".join(set(w))
    if len(letters) > 10:
         return 0
    result = 0
    for subset in choose(10, len(letters)):
        for perm in permutations(subset):
            digits = "".join([str(d) for d in perm])
            mapping = dict(zip(letters, digits))
            w_cand = "".join([mapping[x] for x in w])
            v_cand = "".join([mapping[x] for x in v])
            if w_cand in squares and v_cand in squares:
                result = max(result, max(int(v_cand), int(w_cand)))
    return result

def main(filename):
    words = read_words(filename)
    max_word_len = \
            reduce(max, map(lambda w: len(w), words), 0)
    squares = takewhile(lambda w: len(w) <= max_word_len, \
                        (map(lambda x: str(x * x), naturals())))
    squares = dict([(k, set(v))
                    for k, v in separated_by_length(squares).items()])
    print(list(map(lambda item: (item[0], len(item[1])), squares.items())))
    result = 0
    for w in words:
        for q in words:
            if (w != q and w != "".join(reversed(q))
                                and sorted(w) == sorted(q)):
                result = max(result, max_match(w, q, squares[len(w)]))
    print(result)

if __name__ == "__main__":
    main(sys.argv[1])

