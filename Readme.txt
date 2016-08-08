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
Tools and External Libraries Info
-------------------------------------------------------------------------------

gcc:
- Ubuntu 16.04: version 5.3.1 (section: devel)
- Ubuntu 15.04: version 4.9.2 (main)
- Ubuntu 14.04: version 4.8.4 (main)
- CentOS 7.1: version 4.8.3 (repository: ?)

CMake:
- Ubuntu 16.04: version 3.5.1 (section devel)
- Ubuntu 15.04: distribution provided version is 3.0.2 (main)
- Ubuntu 14.04: distribution provided version is 2.8.12.2 (main), even on 14.04.3
- CentOS 7.1: distribution provided version is 2.8.11 (repository: ?)

GLM:
- import targets are supported since version 0.9.7.0 (released 2015-08-02),
  target name: "glm"
- GLM_FORCE_RADIANS define was required in version 0.9.5.x (otherwise warning appeared),
  version 0.9.6.0 (released 2014-11-30) use radians by default and ignores the define
- Ubuntu 16.04: version 0.9.7.2 (pkgName: libglm-dev, section: libdevel)
- Ubuntu 15.04: version 0.9.5.4 (main)
- Ubuntu 14.04: version 0.9.5.1 (main)
- CentOS: no rpm (seems that no rpm is available for Fedora)

GLEW:
- version 1.9.0 was seen to generate GL_INVALID_ENUM after glewInit()
- it is recommended to update to the latest version otherwise you may encounter compilation problems
- Windows: publicly available precompiled libs works fine since version 1.11.0,
  previous versions do not contain the latest OpenGL functions; moreover, MSVC 2015 seems to have
  troubles to link with binaries built with previous versions of MSVC - you might need to
  build them by yourself from the sources
- Ubuntu 16.04: version 1.13.0 (section: libs)
- Ubuntu 15.04: version 1.10.0 (main)
- Ubuntu 14.04: version 1.10.0 (main)
- CentOS 7.1: version 1.9.0 (base repository)

glfw3:
- import targets: in version 3.1.2, config file is provided but no targets are created
- Ubuntu 15.04: version 3.0.4 (universe)
- Ubuntu 14.04: glfw2 version 2.7.2 (universe)
- CentOS: no rpm (Fedora: seems yes)

SDL2:
- Ubuntu 16.04: version 2.0.4 (section: universe/libs)
- Ubuntu 15.04: version 2.0.2 (universe)
- Ubuntu 14.04: version 2.0.2 (universe)
- CentOS 7.1: no (only version 1.2.15 is available, Fedora: seems yes)

AntTweakBar:
- Ubuntu 16.04: no package available
- Ubuntu 15.04: no package available
- Ubuntu 14.04: no package available
- CentOS 7.1: yes (epel repository), version 1.16, Fedora: seems yes

Assimp:
- import targets: version 3.1.1 has config file but it does not create import target
- Ubuntu 16.04: version 3.2 (section: universe/libdevel)
- Ubuntu 15.04: version 3.0 (universe)
- Ubuntu 14.04: version 3.0 (universe)
- CentOS 7.1: yes (epel repository), version 3.1.1, Fedora: seems yes

FreeImage and FreeImagePlus:
- Ubuntu 16.04: version 3.17.0 (section: universe/libs)
- Ubuntu 15.04: version 3.15.4 (universe)
- Ubuntu 14.04: version 3.15.4 (universe)
- CentOS 7.1: yes (epel repository), version 3.10.0, Fedora: seems yes

OpenSceneGraph:
- Ubuntu 15.04: version 3.2.1 (universe)
- Ubuntu 14.04: version 3.2.0 (universe)
- CentOS: no, Fedora: seems yes
