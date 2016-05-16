#!/usr/bin/python

import sys
import re
import os


if len(sys.argv)<2:
  exit(0)

print "#define GL_GLEXT_PROTOTYPES"
for x in sys.argv[1:]:
  print open(x).read()
