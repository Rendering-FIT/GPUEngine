#!/bin/bash

echo -e "#define GL_GLEXT_PROTOTYPES\n" | cat - /usr/include/GL/gl.h /usr/include/GL/glext.h | ./decomment.py | ./depreprocess.py | ./matchbrackes.py | ./getFunctions.py | ./glFuncFormater.py | sort #| ./glExtensionFilter.py
