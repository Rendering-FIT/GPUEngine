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


for i in data0.split("\n"):
  if i.find("default")<0:
    continue
  print re.sub(r"^[^ ]* ","",i)

