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

data0=data0.split("\n")

data1 = map(lambda x:re.sub(r" ,",r",",re.sub(r", ",r",",re.sub(r"\* ","*",re.sub(r" \*","*",x)))),data0)
data2 = map(lambda x:re.sub(r"([a-zA-Z0-9_* ]*?[a-zA-Z0-9_*]+) ? ?(gl[a-zA-Z0-9_]*) ?\( ?(.*) ?\);",r"\1,\2,\3",x),data1)
data2 = map(lambda x:re.sub(r"\s*$","",x),data2)
data3 = list(set(data2))

#for i in data3:
#  if i=="":
#    continue
#  if len(i.split(","))==3 and i.split(",")[2]=="void":
#    print ",".join(i.split(",")[:-1])
#  else:
#    print i

def genTypeName(string):
    spacepos=string.rfind(" ");
    starpos =string.rfind("*");
    if(spacepos>starpos):
        return (string[:string.rfind(" ")],string[string.rfind(" ")+1:])
    else:
        return (string[:string.rfind("*")+1],string[string.rfind("*")+1:])

listOfFCE=[]

for i in data3:
    if i=="":
      continue
    components = i.split(",")
    final = ""
    if components[0][-1]==" ":
        final+=components[0][:-1]
    else:
        final+=components[0]
    final+=","+components[1]
    for j in components[2:]:
        if j!="void":
            final+=","+genTypeName(j)[0]
            final+=","+genTypeName(j)[1]
    listOfFCE+=[final]

uniqListofFCE=dict()
for i in listOfFCE:
    uniqListofFCE[i.split(",")[1]]=i


for i in uniqListofFCE.keys():
    print uniqListofFCE[i]


#for i in listOfFCE:
#    print i


