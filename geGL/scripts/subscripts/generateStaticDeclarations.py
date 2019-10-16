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

def printContextDeclaration(data):
    params = data.split(",")
    args = ",".join(map(lambda x:x[0]+" "+x[1],zip(params[2::2],params[3::2])))
    params2 = map(lambda x:re.sub(r"\[.*\]","",x),params);
    print "    GEGL_EXPORT "+params[0]+" "+params[1]+"("+args+");"

print "#include<geGL/OpenGL.h>"
print "namespace ge{"
print "  namespace gl{"
for x in data0:
    printContextDeclaration(x)
print "  }"
print "}"

