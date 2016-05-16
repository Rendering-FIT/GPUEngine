#!/usr/bin/python

import sys
import re
import os

#if len(sys.argv)<2:
#    sys.exit(0)

import fileinput
from subprocess import Popen, PIPE

data0=""
for line in fileinput.input():
    data0+=line

data1 = Popen(["g++","-std=c++1y","-E","-"],stdout=PIPE,stdin=PIPE).communicate(data0)[0]

data2 = re.sub(r"#.*","",data1)
print data2
