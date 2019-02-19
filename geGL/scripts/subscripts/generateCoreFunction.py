#!/bin/bash
echo -e "#define GL_GLEXT_PROTOTYPES\n" | cat - glcorearb.h | ./decomment.py | ./matchbrackes.py | g++ -E - | grep "extern" | grep -v "ARB" | sed "s/extern //g" | ./glFuncFormater.py | grep "gl"
