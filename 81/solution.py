import urllib2
import numpy

response = urllib2.urlopen('http://projecteuler.net/project/matrix.txt')
html = response.read()

rows = []
for line in html.split('\n'):
    if line == '':
        continue
    rows.append([int(x.strip()) for x in line.split(',')])

matrix = numpy.matrix(rows)
print matrix

INF = 10000000
for i in range(len(matrix)):
    for j in range(len(matrix)):
        mv = INF
        if i > 0:
            mv = min(mv, matrix[i - 1, j])
        if j > 0:
            mv = min(mv, matrix[i, j - 1])
        if mv == INF:
            mv = 0
        matrix[i, j] = matrix[i, j] + mv

print matrix[len(matrix) - 1, len(matrix) - 1]
