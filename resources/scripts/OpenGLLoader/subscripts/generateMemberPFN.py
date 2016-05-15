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

def printMemberPFN(data):
    params = data.split(",")
    pfn = ("memberpfn"+params[1]+"proc").upper()
    i = 2;
    while i<len(params):
      if re.search("\[.*\]",params[i+1]):
        params[i] = params[i]+"*"
      i+=2;

    #print "#if !defined("+pfn+")"
    print "using "+pfn+" = "+params[0]+"(FunctionTable::*"+")("+",".join(params[2::2])+")const;"
    #print "#endif"

for x in data0:
    printMemberPFN(x)



