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

def printLoadFunction(data):
    params = data.split(",")
    pfn = ("pfn"+params[1]+"proc").upper()
    print "table->"+params[1]+" = ("+"OpenGLFunctionTable::"+pfn+")getProcAddress(\""+params[1]+"\");"

for x in data0:
    printLoadFunction(x)


