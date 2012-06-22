import itertools
import urllib2
import numpy
import operator
from subprocess import *

response = urllib2.urlopen('http://projecteuler.net/project/matrix.txt')
html = response.read()

nums = []
for line in html.split('\n'):
    if line == '':
        continue
    nums = nums + [x.strip() for x in line.split(',')]

input_string = '80'
for i in nums:
    input_string = input_string + ' ' + i

proc = Popen(['./solution'], stdin=PIPE, stdout=PIPE)
output = proc.communicate(input=input_string)[0]

print output

