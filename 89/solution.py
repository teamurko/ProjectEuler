#!/bin/python

TAUSEND="M"
THOUSAND=1000
NEUNHUNDERT="CM"
NINEHUNDRED=900
FUNFHUNDERT="D"
FIVEHUNDRED=500
VIERHUNDERT="CD"
FOURHUNDRED=400
HUNDERT="C"
HUNDRED=100
NEUNZIG="XC"
NINETY=90
FUNFZIG="L"
FIFTY=50
VIERZIG="XL"
FORTY=40
ZEHN="X"
TEN=10
NEUN="IX"
NINE=9
FUNF="V"
FIVE=5
VIER="IV"
FOUR=4
EIN="I"
ONE=1

ROMES=[TAUSEND, NEUNHUNDERT, FUNFHUNDERT, VIERHUNDERT, HUNDERT, \
       NEUNZIG, FUNFZIG, VIERZIG, ZEHN, NEUN, FUNF, VIER, EIN]

DECS=[THOUSAND, NINEHUNDRED, FIVEHUNDRED, FOURHUNDRED, HUNDRED,
      NINETY, FIFTY, FORTY, TEN, NINE, FIVE, FOUR, ONE]

def toDecimal(rome):
    result=0
    for r, d in zip(ROMES, DECS):
        while rome.startswith(r):
            result += d
            rome = rome[len(r):]
    return result

def toRome(dec):
    result=""
    for r, d in zip(ROMES, DECS):
        while dec >= d:
            dec -= d
            result = result + r
    return result

fin=open("roman.txt", "r")
numbers=[x.strip() for x in fin.readlines()]
for x in numbers:
    print x, toDecimal(x), toRome(toDecimal(x)), len(toRome(toDecimal(x)))
print sum(map(lambda x: len(x)-len(toRome(toDecimal(x))), numbers))


