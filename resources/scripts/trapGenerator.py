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

"""template<typename OUTPUT,typename...ARGS>
OUTPUT geglTrapFunction(char const*fceName){
  std::cerr<<"Function "<<fce<<" is nullptr"<<std::endl;
}
"""

def printTrapFunctionTest(data):
    params = data.split(",")
    print "  if("+params[1]+" == nullptr)"+params[1]+" = geglTrap"+params[1]+";"

def printTrapFunctions(data):
    params = data.split(",")
    print "GEGL_EXPORT "+params[0]+" geglTrap"+params[1]+"("+",".join(params[2::2])+"){std::cerr<<\"Function \\\""+params[1]+"\\\" is nullptr\" << std::endl;std::exit(1);return ("+params[0]+")0;}"


for x in data0:
    printTrapFunctions(x)

print "void ge::gl::glTest(){"
for x in data0:
    printTrapFunctionTest(x)
print "}"
