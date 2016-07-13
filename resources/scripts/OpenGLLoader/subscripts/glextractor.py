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


closed=""
depth=0
for i in data0:
    if i=="\n" and depth!=0:
        continue
    if i=="(":
        depth+=1
    if i==")":
        depth-=1
    closed+=i

data0=re.sub(r"[ \t]+"," ",closed,flags=0)

glDefines="""
#define GL_VERSION_1_1   1
#define GL_VERSION_1_2   1
#define GL_VERSION_1_3   1
#define GL_VERSION_1_4   1
#define GL_ARB_imaging   1
#define GL_ARB_multitexture 1
"""
glDefines=""

data00 = Popen(["g++","-std=c++1y","-E","-"],stdout=PIPE,stdin=PIPE).communicate(glDefines+data0)[0]
data01 = re.compile(r"^.*PFN.*",flags=re.MULTILINE).findall(data00)
data02 = map(lambda x:re.sub(r"^typedef.*PFN([a-zA-Z0-9_]*)PROC.*",r"\1",x).lower(),data01)

for i in data01:
    print i
exit(0)

reg = data02[0]
for i in data02[1:]:
    reg+="|"+i
comreg = re.compile(reg)

data03 = zip(data0.lower().split("\n"),data0.split("\n"))
data04=[]
for i in data03:
    if i[1].find("PFN")!=-1:
        continue
    if comreg.findall(i[0])!=[]:
        data04+=[i[1]]

data05 = map(lambda x:x.replace("GLAPI ",""),map(lambda x:x.replace("APIENTRY",""),map(lambda x:x.replace("GLAPIENTRY",""),data04)))
data06 = map(lambda x:re.sub(r" ,",r",",re.sub(r", ",r",",re.sub(r"\* ","*",re.sub(r" \*","*",x)))),data05)
data07 = map(lambda x:re.sub(r"([a-zA-Z0-9_* ]*?[a-zA-Z0-9_*]+) ? ?(gl[a-zA-Z0-9_]*) ?\( ?(.*) ?\);",r"\1,\2,\3",x),data06)
data07 = list(set(data07))

#for i in data07:
#    print i
#exit(0)

def genTypeName(string):
    spacepos=string.rfind(" ");
    starpos =string.rfind("*");
    if(spacepos>starpos):
        return (string[:string.rfind(" ")],string[string.rfind(" ")+1:])
    else:
        return (string[:string.rfind("*")+1],string[string.rfind("*")+1:])

listOfFCE=[]

for i in data07:
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

for i in listOfFCE:
    print i

exit(0)

