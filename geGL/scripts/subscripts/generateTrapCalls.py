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

def printTrapCall(data):
    params = data.split(",")
    pfn = ("memberpfn"+params[1]+"proc").upper()
    print "if(!this->m_ptr_"+params[1]+")this->m_ptr_"+params[1]+" = (FunctionTable::"+pfn+")&TrapTableDecorator::m_"+params[1]+"_trap;"

for x in data0:
    printTrapCall(x)

