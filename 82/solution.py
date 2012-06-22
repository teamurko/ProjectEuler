import itertools
import urllib2
import numpy
import operator

response = urllib2.urlopen('http://projecteuler.net/project/matrix.txt')
html = response.read()

rows = []
for line in html.split('\n'):
    if line == '':
        continue
    rows.append([int(x.strip()) for x in line.split(',')])

matrix = numpy.matrix(rows)
INF = 1000000000
d = numpy.matrix([[INF] * len(matrix)] * len(matrix))
for i in range(len(d)):
    d[i, 0] = matrix[i, 0]

for j in range(len(d) - 1):
    for i in range(len(d)):
        for k in range(len(d)):
            indices = [(x, j + 1) for x in range(min(i, k), max(i, k) + 1)]
            s = sum([matrix[x, y] for (x, y) in indices])
            d[k, j + 1] = min(d[k, j + 1], d[i, j] + s)

l = []
for i in range(len(d)):
    l.append(d[i, len(d) - 1])
print sorted(l)[0]


