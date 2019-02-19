#!/usr/bin/python

import os

glHeader     = "/usr/include/GL/gl.h"
glextHeader  = "/usr/include/GL/glext.h"
glcoreHeader = "/usr/include/GL/glcorearb.h"

geGLIncludeDir = "../src/geGL/"
geGLSrcDir     = "../src/geGL/"
outputDir      = geGLIncludeDir+"Generated/"

subscriptsDir = "subscripts/"

allFormatedFunctions  = "allFormatedFunctions.txt"
coreFormatedFunctions = "coreFormatedFunctions.txt"

os.system(
"./"+subscriptsDir+"printHEADER.py "+glHeader+" "+glextHeader+" |"+
"./"+subscriptsDir+"decomment.py |"+
"./"+subscriptsDir+"depreprocess.py |"+
"./"+subscriptsDir+"matchbrackes.py |"+
"./"+subscriptsDir+"getFunctions.py |"+
#"./"+subscriptsDir+"glExtensionFilter.py |"+
"./"+subscriptsDir+"glFuncFormater.py >"+
allFormatedFunctions)

os.system(
"./"+subscriptsDir+"printHEADER.py "+glcoreHeader+" |"+
"./"+subscriptsDir+"decomment.py |"+
"./"+subscriptsDir+"matchbrackes.py |"+
"./"+subscriptsDir+"depreprocess.py |"+
"grep \"extern\" |"+
"./"+subscriptsDir+"glExtensionFilter.py |"+
"sed \"s/extern //g\" |"+
"grep \"gl\" |"+
"./"+subscriptsDir+"glFuncFormater.py >"+
coreFormatedFunctions)


os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generatePFN.py >"+
outputDir+"OpenGLPFN.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateMemberPFN.py >"+
outputDir+"MemberOpenGLPFN.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateFunctions.py >"+
outputDir+"OpenGLFunctions.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateMemberFunctions.py >"+
outputDir+"MemberOpenGLFunctions.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateFunctionTableCalls.py >"+
outputDir+"FunctionTableCalls.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateContextDeclarations.py >"+
outputDir+"ContextDeclarations.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateContextCalls.py >"+
outputDir+"ContextCalls.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateNumberOfFunctions.py >"+
outputDir+"NumberOfFunctions.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateLoaderLoadingCalls.py >"+
outputDir+"LoaderLoadingCalls.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateLoaderImplementation.py >"+
outputDir+"LoaderImplementation.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateTrapCalls.py >"+
outputDir+"TrapCalls.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateTrapImplementation.py >"+
outputDir+"TrapImplementation.h")

os.system(
"./"+subscriptsDir+"printHEADER.py "+glHeader+" "+glextHeader+" |"+
"./"+subscriptsDir+"extractConstants.py |"+
"./"+subscriptsDir+"decorateHeader.py >"+
outputDir+"OpenGLConstants.h")

os.system(
"./"+subscriptsDir+"printHEADER.py "+glHeader+" "+glextHeader+" |"+
"./"+subscriptsDir+"decomment.py |"+
"./"+subscriptsDir+"depreprocess.py |"+
"./"+subscriptsDir+"extractTypes.py |"+
"./"+subscriptsDir+"decorateHeader.py >"+
outputDir+"OpenGLTypes.h")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateStaticCalls.py >"+
geGLSrcDir+"StaticCalls.cpp")

os.system(
"cat "+allFormatedFunctions+" |"+
"./"+subscriptsDir+"generateStaticDeclarations.py >"+
geGLIncludeDir+"StaticCalls.h")

os.system("rm "+allFormatedFunctions)
os.system("rm "+coreFormatedFunctions)


#./printHEADER.py /usr/include/GL/gl.h /usr/include/GL/glext.h | ./decomment.py | ./depreprocess.py | grep "typedef" | grep -v "PFN" | sort | grep "GL" > ~/Desktop/exttypes.txt
