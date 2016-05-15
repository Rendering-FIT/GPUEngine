#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=[]
for line in fileinput.input():
  if re.search("#define",line) and re.search("GL_",line):
    data0+=[' '.join(line.split())]


#data1 = list(set(data0))
#data1.sort()

for x in data0:
  print x

