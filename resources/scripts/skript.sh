#!/bin/sh
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | ./glCommand.py > commands.h ; vim commands.h
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Buffer" | ./glCommand.py > BufferCommands.h
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Barrier" | ./glCommand.py > BarrierCommands.h
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Program" | grep -v "Uniform\|Pipeline" | ./glCommand.py > ProgramCommands.h
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Uniform" | ./glCommand.py > UniformCommands.h 
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Dispatch" | ./glCommand.py > DispatchCommands.h 
#cat /usr/include/GL/glext.h | ./glextractor.py | grep -v "AMD\|NV\|ARB\|EXT\|ATI\|SUN\|SGIS\|OES\|INTEL\|MESA\|SGIX\|HP\|APPLE\|SGI\|IBM" | grep "Draw" | grep -v "Buffer" | ./glCommand.py > DrawCommands.h 

#./generareAllFunction.sh | grep "Buffer" | grep -v "VertexArray"| ./glCommand.py > BufferCommands.h
#./generareAllFunction.sh | grep "Barrier" | ./glCommand.py > BarrierCommands.h
#./generareAllFunction.sh | grep "Program" | grep -v "Uniform\|Pipeline" | ./glCommand.py > ProgramCommands.h
#./generareAllFunction.sh | grep "Uniform" | ./glCommand.py > UniformCommands.h
#./generareAllFunction.sh | grep "Dispatch" | ./glCommand.py > DispatchCommands.h
#./generareAllFunction.sh | grep "Draw\|Patch" | grep -v "Buffer" | ./glCommand.py > DrawCommands.h
#./generareAllFunction.sh | grep "VertexArray" | ./glCommand.py > VertexArrayCommands.h
#./generareAllFunction.sh | grep "ScissorArrayv\|ScissorIndexed\|ScissorIndexedv\|Scissor" | ./glCommand.py > ScissorCommands.h
#./generareAllFunction.sh | grep "SampleCoverage\|SampleMaski" | ./glCommand.py > MultisampleCommands.h
#./generareAllFunction.sh | grep "StencilFunc\|StencilFuncSeparate\|StencilOp\|StencilOpSeparate" | ./glCommand.py > StencilCommands.h
#./generareAllFunction.sh | grep "DepthFunc" | ./glCommand.py > DepthCommands.h
#./generareAllFunction.sh | grep "BeginQuery\|EndQuery" | ./glCommand.py > OcclusionQueriesCommands.h
#./generareAllFunction.sh | grep "BlendEquation\|BlendEquationSeparate\|BlendEquationi\|BlendEquationSeparatei\|BlendFunc\|BlendFuncSeparate\|BlendColor" | ./glCommand.py > BlendCommands.h
#./generareAllFunction.sh | grep "LogicOp" | ./glCommand.py > LogicCommands.h
#./generareAllFunction.sh | grep "DrawBuffer\|NamedFramebufferDrawBuffer\|DrawBuffers\|NamedFramebufferDrawBuffers\|ColorMask\|ColorMaski\|DepthMask\|StencilMask\|StencilMaskSeparate\|Clear,\|ClearColor\|ClearDepth\|ClearDepthf\|ClearStencil\|ClearBufferiv\|ClearBufferfv\|ClearBufferuiv\|ClearNamedFramebufferiv\|ClearNamedFramebufferfv\|ClearNamedFramebufferuiv\|ClearBufferfi\|ClearNamedFramebufferfi\|InvalidateSubFramebuffer\|InvalidateNamedFramebufferSubData\|InvalidateFramebuffer\|InvalidateNamedFramebufferData" | ./glCommand.py > WholeFramebufferCommands.h

#cp BufferCommands.h            /home/dormon/git/gpuengine-code/include/geGL/
#cp BarrierCommands.h           /home/dormon/git/gpuengine-code/include/geGL/
#cp ProgramCommands.h           /home/dormon/git/gpuengine-code/include/geGL/
#cp UniformCommands.h           /home/dormon/git/gpuengine-code/include/geGL/
#cp DispatchCommands.h          /home/dormon/git/gpuengine-code/include/geGL/
#cp DrawCommands.h              /home/dormon/git/gpuengine-code/include/geGL/
#cp VertexArrayCommands.h       /home/dormon/git/gpuengine-code/include/geGL/
#cp ScissorCommands.h           /home/dormon/git/gpuengine-code/include/geGL/
#cp MultisampleCommands.h       /home/dormon/git/gpuengine-code/include/geGL/
#cp StencilCommands.h           /home/dormon/git/gpuengine-code/include/geGL/
#cp DepthCommands.h             /home/dormon/git/gpuengine-code/include/geGL/
#cp OcclusionQueriesCommands.h  /home/dormon/git/gpuengine-code/include/geGL/
#cp BlendCommands.h             /home/dormon/git/gpuengine-code/include/geGL/
#cp LogicCommands.h             /home/dormon/git/gpuengine-code/include/geGL/
#cp WholeFramebufferCommands.h  /home/dormon/git/gpuengine-code/include/geGL/

#./generareAllFunction.sh  | ./glCommand.py > OpenGLCommands.h
#cp OpenGLCommands.h /home/dormon/git/gpuengine-code/include/geGL/

./generareCoreFunction.py | ./glCommand.py > OpenGLCommands.h
cp OpenGLCommands.h /home/dormon/git/gpuengine-code/include/geGL/

#echo -e "#define GL_GLEXT_PROTOTYPES\n" | cat - /usr/include/GL/gl.h /usr/include/GL/glext.h | g++ -E - | grep "default" | sed "s/[^ ]* \(.*\)/\1/g" | grep -v "AMD\|NV\|ATI\|IBM\|HP\|EXT\|ARB\|OES\|SUN\|SGI\|MESA\|INTEL\|APPLE\|3DFX\|GREMEDY\|OVR\|PGI\|INGR\|KHR"
