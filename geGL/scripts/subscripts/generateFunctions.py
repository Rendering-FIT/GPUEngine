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

def printFunction(data):
    params = data.split(",")
    pfn = ("pfn"+params[1]+"proc").upper()
    #print "#if !defined("+pfn+")"
    print pfn+" "+"m_"+params[1]+";"#" = nullptr;"
    #print "#endif"

for x in data0:
    printFunction(x)

