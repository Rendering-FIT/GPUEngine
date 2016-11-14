#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=[]
for line in fileinput.input():
  if re.search("typedef",line) and re.search("GL",line) and not re.search("PFN",line):
    data0+=[' '.join(line.split())]

print "#include<cstddef>"
print "#include<cstdint>"
for x in data0:
  print x
print "struct _cl_context;"
print "struct _cl_event;"
