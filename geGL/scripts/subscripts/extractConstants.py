#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0={}
for line in fileinput.input():
  if re.search("#define",line) and re.search("GL_",line):
    words = line.split()
    if len(words)==3:
      data0[words[1]] = words[2];
data1 =  sorted(data0.items())
for val in data1:
    print "#define "+val[0]+" "+val[1]

