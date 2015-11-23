GPUEngine is gpu-optimized library for 3D graphics scene processing and rendering.


===============================================================================
Compile
-------------------------------------------------------------------------------

Prerequisities:
- Windows: Microsoft Visual C++ 2013 (Update 4, previous not tested), 2015 or newer
- Linux: gcc 4.8 (<=4.7 not tested)
- cmake 3.0.0 or newer
- glm 0.9.7.0 or newer
- glew

Optional:
- glfw
- SDL 2.0.0 or newer
- AntTweakBar
- Assimp
- FreeImage
- FreeImagePlus
- OpenSceneGraph


===============================================================================
Tools and External Library Info
-------------------------------------------------------------------------------

gcc:
- Ubuntu 15.04: distribution provided version is 4.9.2 (main)
- CentOS 7.1: distribution provided version is 4.8.3 (repository: ?)

Cmake:
- Ubuntu 15.04: distribution provided version is 3.0.2 (main)
- CentOS 7.1: distribution provided version is 2.8.11 (repository: ?)

glm:
- import targets are supported since version 0.9.7.0 (released 2015-08-02)
- Ubuntu 15.04: version 0.9.5.4 (main)
- CentOS: no rpm (seems that no rpm is available for Fedora)

glew:
- Ubuntu 15.04: version 1.10.0 (main)
- CentOS 7.1: version 1.9.0 (base repository)

glfw3:
- Ubuntu 15.04: version 3.0.4 (universe)
- CentOS: no rpm (Fedora: seems yes)

SDL2:
- Ubuntu 15.04: version 2.0.2 (universe)
- CentOS 7.1: no (only version 1.2.15 is available, Fedora: seems yes)

AntTweakBar:
- Ubuntu 15.04: no package available
- CentOS 7.1: yes (epel repository), version 1.16, Fedora: seems yes

Assimp:
- Ubuntu 15.04: version 3.0 (universe)
- CentOS 7.1: yes (epel repository), version 3.1.1, Fedora: seems yes

FreeImage and FreeImagePlus:
- Ubuntu 15.04: version 3.15.4 (universe)
- CentOS 7.1: yes (epel repository), version 3.10.0, Fedora: seems yes

OpenSceneGraph:
- Ubuntu 15.04: version 3.2.1 (universe)
- CentOS: no, Fedora: seems yes
