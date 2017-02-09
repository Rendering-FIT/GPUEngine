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

#def getReturn(type):
#    if type == "void" or type == "GLvoid":
#        return ""
#    return "return "
#
#def printLoadingCall(data):
#    params = data.split(",")
#    pfn = ("pfn"+params[1]+"proc").upper()
#    memberpfn = ("memberpfn"+params[1]+"proc").upper()
#    print "this->m_"+params[1]+" = (FunctionTable::"+pfn+")this->m_functionLoader->load(\""+params[1]+"\");"
#    print "if(this->m_"+params[1]+")this->m_ptr_"+params[1]+" = (FunctionTable::"+memberpfn+")&LoaderTableDecorator::m_"+params[1]+"_impl;"
#
#for x in data0:
#    printLoadingCall(x)


print "using MEMBER_FUNCTION_POINTER = void(FunctionTable::*)();"

print "char const* functionNames[] = {"
for line in data0:
    print "  \""+line.split(",")[1]+"\","
print "};"

print "MEMBER_FUNCTION_POINTER const functionPointers[] = {"
for line in data0:
    print "  (MEMBER_FUNCTION_POINTER)(&LoaderTableDecorator::m_"+line.split(",")[1]+"_impl),"
print "};"

print "for(size_t i=0;i<GE_GL_NOF_OPENGL_FUNCTIONS;++i)"
print "  this->baseFunctions[i] = this->m_functionLoader->load(functionNames[i]);"

print "for(size_t i=0;i<GE_GL_NOF_OPENGL_FUNCTIONS;++i)"
print "  if(this->baseFunctions[i])this->memberFunctions[i] = functionPointers[i];"
print "  else this->memberFunctions[i] = nullptr;"
