set(examples_folder_name "examples")

set(examplesList  EmptyWindow
                  ShaderTest
                  VertexArray
                  HilbertCurve
                  MemoryBandwidth
                  HelloTriangle
                  TriangleRendering
                  ObjLoader
                  HelloGEGL
                  AnimatedSkybox
                  BlitOpenGL
                  TextureTest
                  Simple_QTgeGL
                  Simple_QTgeSG
)

foreach(example IN LISTS examplesList)
   add_subdirectory(${example})
endforeach()

message(STATUS "Examples configured:")

foreach(example IN LISTS examplesList)
   if(TARGET ${example})
      message(STATUS "   ${example}")
   endif()
endforeach()
