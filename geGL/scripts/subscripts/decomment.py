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

data0 = re.sub(r"//.*$","",data0,flags=re.DOTALL)

print data0
