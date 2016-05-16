#!/usr/bin/python
#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=""
for line in fileinput.input():
  data0+=line

data0 = data0.split("\n")[::-1]

if len(sys.argv)<2:
  exit(0)



extensions = ["AMD","NV","ATI","IBM","HP","EXT","ARB","OES","SUN","SGI","MESA","INTEL","APPLE","3DFX","GREMEDY","OVR","PGI","INGR","KHR"]

pre = "#pragma once"
post = ""
fileName = sys.argv[1]


for ext in extensions:
  print fileName+"_"+ext+".h"
  print pre
  for line in data0:
    if re.search(ext,line):
      print line
  print post

reg = re.compile("|".join(extensions))

print fileName+"_CORE.h"
print pre
for line in data0:
  if reg.findall(line)!=[]:
    continue
  if line=="":
    continue
  print line
print post
