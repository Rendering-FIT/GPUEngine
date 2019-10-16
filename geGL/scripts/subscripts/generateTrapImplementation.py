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

def getReturn(type):
    if type == "void" or type == "GLvoid":
        return ""
    return "return "

def printTrapImplementation(data):
    params = data.split(",")
    i = 2;
    while i<len(params):
      if re.search("\[.*\]",params[i+1]):
        params[i] = params[i]+"*"
      i+=2;
    print params[0]+" m_"+params[1]+"_trap("+",".join(params[2::2])+")const{this->m_printMissingFunctionErrorAndExit(\""+params[1]+"\");return ("+params[0]+")0;}"


for x in data0:
    printTrapImplementation(x)

