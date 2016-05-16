#!/usr/bin/python

import sys
import re
import os

import fileinput
from subprocess import Popen, PIPE

data0=""
for line in fileinput.input():
    data0+=line

data0=data0.split("\n")[:-1]

print "#pragma once"
for x in data0:
    print x


