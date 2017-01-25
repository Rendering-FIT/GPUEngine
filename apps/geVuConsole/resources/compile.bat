@echo off
for %%f in (*.frag) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.vert) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.tesc) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.tese) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.geo) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.comp) do glslangValidator -V %%f -o %%f.spv

