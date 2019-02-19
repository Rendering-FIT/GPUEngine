#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=""
for line in fileinput.input():
    data0+=line

data0=data0.split("\n")[:-1]

def printPFN(data):
    params = data.split(",")
    pfn = ("pfn"+params[1]+"proc").upper()
    i = 2;
    while i<len(params):
      if re.search("\[.*\]",params[i+1]):
        params[i] = params[i]+"*"
      i+=2;
    #print "#if !defined("+pfn+")"
    print "typedef "+params[0]+"(*"+pfn+")("+",".join(params[2::2])+");"
    #print "#endif"

for x in data0:
    printPFN(x)



