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

def printTrapFunctionTest(data):
    params = data.split(",")
    print "if("+"table->"+params[1]+" == nullptr)table->"+params[1]+" = geglTrap"+params[1]+";"

for x in data0:
    printTrapFunctionTest(x)
