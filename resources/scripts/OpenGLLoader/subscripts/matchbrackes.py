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

data0 = re.sub(r"/\*.*?\*/","",data0,flags=re.DOTALL)


closed=""
depth=0
for i in data0:
    if i=="\n" and depth!=0:
        continue
    if i=="(":
        depth+=1
    if i==")":
        depth-=1
    closed+=i

data0=re.sub(r"[ \t]+"," ",closed,flags=0)

print data0
