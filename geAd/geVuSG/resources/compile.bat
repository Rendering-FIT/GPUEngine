for %%f in (*.frag) do glslangValidator -V %%f -o %%f.spv
for %%f in (*.vert) do glslangValidator -V %%f -o %%f.spv