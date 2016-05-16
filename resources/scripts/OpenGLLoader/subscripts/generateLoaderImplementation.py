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

def printFunctionImplementation(data):
    params = data.split(",")
    args = ",".join(map(lambda x:x[0]+" "+x[1],zip(params[2::2],params[3::2])))
    params2 = map(lambda x:re.sub(r"\[.*\]","",x),params);
    print params[0]+" m_"+params[1]+"_impl("+args+")const{"+getReturn(params[0])+"this->m_"+params[1]+"("+",".join(params2[3::2])+");}"


for x in data0:
    printFunctionImplementation(x)

