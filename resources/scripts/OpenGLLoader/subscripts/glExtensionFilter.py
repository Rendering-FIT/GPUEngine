#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=""
for line in fileinput.input():
    data0+=line

#ext = re.compile(r"AMD|NV|ATI|IBM|HP|EXT|ARB|OES|SUN|SGI|MESA|INTEL|APPLE|3DFX|GREMEDY|OVR|PGI|INGR|KHR|\[")
ext = re.compile(r"AMD|NV|ATI|IBM|HP|ARB|OES|SUN|SGI|MESA|INTEL|APPLE|3DFX|GREMEDY|OVR|PGI|INGR|KHR|\[")

for i in data0.split("\n"):
    if ext.findall(i)!=[]:
        continue
    if i=="":
        continue
    print i
