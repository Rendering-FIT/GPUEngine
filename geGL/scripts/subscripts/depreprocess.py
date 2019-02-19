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

data2 = re.sub(r"#.*","",data1).split("\n")
data3 = filter(lambda x: not re.match(r'^\s*$', x), data2)

data4 = []
headerLine=""
for line in data3:
    if headerLine == "":
        if re.search(";",line):
            data4+=[line]
        else:
            headerLine = line
    else:
        if re.search(";",line):
            headerLine+=line;
            data4+=[headerLine]
            headerLine = ""
        else:
            headerLine+=line
if headerLine != "":
    data4 += [headerLine]

for x in data4:
    print ' '.join(x.split())
