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

def printTrapFunctions(data):
    params = data.split(",")
    print "GEGL_EXPORT "+params[0]+" geglTrap"+params[1]+"("+",".join(params[2::2])+"){printMissingFunctionError(\""+params[1]+"\");std::exit(1);return ("+params[0]+")0;}"



print "GEGL_EXPORT void printMissingFunctionError(char const*fce){std::cerr<<\"Function \"<<fce<<\" is nullptr\"<<std::endl;}"
for x in data0:
    printTrapFunctions(x)

