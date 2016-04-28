#!/usr/bin/python

import sys
import re

import fileinput

data0=""
for line in fileinput.input():
    data0+=line

data1 = data0.split("\n")
if data1[-1]=="":
  data1 = data1[:-1]

names=[]

for i in data1:
  components = i.split(",")
  names += [components[1]]

extensions=["SUN","NV","ARB","SGI","EXT","MESA","INTEL","ATI","IBM","HP","APPLE","AMD","GREMEDY","OES","PGI","3DFX","INGR"]

extNames=dict()

for i in extensions:
  extNames[i]=[]
extNames[""]=[]

for i in names:
  wasInserted = False
  for e in extensions:
    if i.find(e)!=-1:
      extNames[e]+=[i]
      wasInserted = True
  if not wasInserted:
    extNames[""]+=[i]

maxLength = dict()

for i in extNames.keys():
  maxLength[i] = max(map(lambda x:len(x),extNames[i]))

def toPFN(name):
    return "PFN"+name.upper()+"PROC"

for e in extNames.keys():
  header = ""
  header +="#pragma once\n"
  header += "\n"
  header += "#include<GL/gl.h>\n"
  header += "#include<GL/glext.h>\n"
  header += "\n"
  header += "namespace ge{\n"
  header += "  namespace gl{\n"
  if e=="":
    for i in extNames[e]:
      spaces=" "*(maxLength[e]-len(i))
      header += "    extern "+toPFN(i)+" "+spaces+i+spaces+";\n"
  else:
    if e[0] >= "0" and e[0] <= "9":
      header += "    namespace e"+e.lower()+"{\n"
    else:
      header += "    namespace "+e.lower()+"{\n"
    for i in extNames[e]:
      spaces=" "*(maxLength[e]-len(i))
      header += "      extern "+toPFN(i)+" "+spaces+i+spaces+";\n"
    header += "    }\n"
  header += "  }\n"
  header += "}\n"
  if e=="":
    open("base.h","w").write(header)
  else:
    open(e.lower()+".h","w").write(header)

for e in extNames.keys():
    source = ""
    if e=="":
        source += "#include\"base.h\"\n"
    else:
        source += "#include\""+e.lower()+".h\"\n"
    source += "\n"
    namespace = "ge::gl"
    source += "using namespace ge::gl"
    if e!="":
        source+="::"
        namespace+="::"
        if e[0] >= "0" and e[0] <= "9":
            namespace+="e"+e.lower()
            source+="e"+e.lower()
        else:
            namespace+=e.lower()
            source+=e.lower()
    source+=";\n"
    source+="\n"
    for i in extNames[e]:
        spaces=" "*(maxLength[e]-len(i))
        source+=toPFN(i)+" "+spaces+i+spaces+" = NULL;\n"
    if e=="":
        open("base.cpp","w").write(source)
    else:
        open(e.lower()+".cpp","w").write(source)
    

