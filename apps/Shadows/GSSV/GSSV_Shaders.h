#pragma once

#include <string>

std::string const gsSilVs = R".(


/////////////////////////////////////////////////////////////////////
// Options:
// if you define something, it will be applied.
// if you don't define something, opposite will be applied.
// Some defines has value that has to be set properly.
// Version number has to be chosen by user, preprocessor
// cannot do it (nothing useful can precede #version N P).
/////////////////////////////////////////////////////////////////////

//generate universal shader - define/don't define
//#define UNIVERSAL
//use arrays for transfer - define/don't define
//#define USE_ARRAY_TRANSFER
//use vertex array - define/don't define
//#define USE_VERTEX_ARRAY
//use layouts - define/don't define
//#define USE_LAYOUTS
//set input vertex attrib name - set value
//#define VERTEX_ATTRIB_NAME Position
//maximal number of opposite vertices - set value
//#define MAX_MULTIPLICITY 2

// DO NOT CHANGE ANYTHING BELOW THIS COMMENT!!!
// UNLESS, OF COURSE, YOU KNOW WHAT YOU ARE DOING.





/////////////////////////////////////////////////////////////////////
// TODO extensions and checks
/////////////////////////////////////////////////////////////////////

#if MAX_MULTIPLICITY > 16
  #error Max Multiplicity cannot exceed 16
#endif

#if MAX_MULTIPLICITY < 1
  #error Max Multiplicity cannont be 0 or less
#endif

#define PASTER(x,y) x##y




/////////////////////////////////////////////////////////////////////
// Inputs
/////////////////////////////////////////////////////////////////////

//compute number of imput vertex attribs
#ifdef UNIVERSAL
  #define NUMBER_OF_INPUTS (MAX_MULTIPLICITY+2+1)
#else//UNIVERSAL
  #define NUMBER_OF_INPUTS (MAX_MULTIPLICITY+2)
#endif//UNIVERSAL

//declare inputs
#ifdef USE_VERTEX_ARRAY
  #ifdef USE_LAYOUTS
    layout(location=0)in vec4 VERTEX_ATTRIB_NAME[NUMBER_OF_INPUTS];
  #else
    in vec4 VERTEX_ATTRIB_NAME[NUMBER_OF_INPUTS];
  #endif
#else//USE_VERTEX_ARRAY
  #ifdef USE_LAYOUTS
    #define DEF_INPUT(x,y) layout(location=y)in vec4 PASTER(x,y);
  #else//USE_LAYOUTS
    #define DEF_INPUT(x,y) in vec4 PASTER(x,y);
  #endif//USE_LAYOUTS
    //vertex A of an edge
DEF_INPUT(VERTEX_ATTRIB_NAME,0)
    //vertex B of an edge
DEF_INPUT(VERTEX_ATTRIB_NAME,1)
  #ifdef UNIVERSAL
    //number of opposite vertices
DEF_INPUT(VERTEX_ATTRIB_NAME,2)
    #if MAX_MULTIPLICITY>0
DEF_INPUT(VERTEX_ATTRIB_NAME,3)
    #endif
    #if MAX_MULTIPLICITY>1
DEF_INPUT(VERTEX_ATTRIB_NAME,4)
    #endif
    #if MAX_MULTIPLICITY>2
DEF_INPUT(VERTEX_ATTRIB_NAME,5)
    #endif
    #if MAX_MULTIPLICITY>3
DEF_INPUT(VERTEX_ATTRIB_NAME,6)
    #endif
    #if MAX_MULTIPLICITY>4
DEF_INPUT(VERTEX_ATTRIB_NAME,7)
    #endif
    #if MAX_MULTIPLICITY>5
DEF_INPUT(VERTEX_ATTRIB_NAME,8)
    #endif
    #if MAX_MULTIPLICITY>6
DEF_INPUT(VERTEX_ATTRIB_NAME,9)
    #endif
    #if MAX_MULTIPLICITY>7
DEF_INPUT(VERTEX_ATTRIB_NAME,10)
    #endif
    #if MAX_MULTIPLICITY>8
DEF_INPUT(VERTEX_ATTRIB_NAME,11)
    #endif
    #if MAX_MULTIPLICITY>9
DEF_INPUT(VERTEX_ATTRIB_NAME,12)
    #endif
    #if MAX_MULTIPLICITY>10
DEF_INPUT(VERTEX_ATTRIB_NAME,13)
    #endif
    #if MAX_MULTIPLICITY>11
DEF_INPUT(VERTEX_ATTRIB_NAME,14)
    #endif
    #if MAX_MULTIPLICITY>12
DEF_INPUT(VERTEX_ATTRIB_NAME,15)
    #endif
    #if MAX_MULTIPLICITY>13
DEF_INPUT(VERTEX_ATTRIB_NAME,16)
    #endif
    #if MAX_MULTIPLICITY>14
DEF_INPUT(VERTEX_ATTRIB_NAME,17)
    #endif
    #if MAX_MULTIPLICITY>15
DEF_INPUT(VERTEX_ATTRIB_NAME,18)
    #endif
  #else//UNIVERSAL
    #if MAX_MULTIPLICITY>0
DEF_INPUT(VERTEX_ATTRIB_NAME,2)
    #endif
    #if MAX_MULTIPLICITY>1
DEF_INPUT(VERTEX_ATTRIB_NAME,3)
    #endif
    #if MAX_MULTIPLICITY>2
DEF_INPUT(VERTEX_ATTRIB_NAME,4)
    #endif
    #if MAX_MULTIPLICITY>3
DEF_INPUT(VERTEX_ATTRIB_NAME,5)
    #endif
    #if MAX_MULTIPLICITY>4
DEF_INPUT(VERTEX_ATTRIB_NAME,6)
    #endif
    #if MAX_MULTIPLICITY>5
DEF_INPUT(VERTEX_ATTRIB_NAME,7)
    #endif
    #if MAX_MULTIPLICITY>6
DEF_INPUT(VERTEX_ATTRIB_NAME,8)
    #endif
    #if MAX_MULTIPLICITY>7
DEF_INPUT(VERTEX_ATTRIB_NAME,9)
    #endif
    #if MAX_MULTIPLICITY>8
DEF_INPUT(VERTEX_ATTRIB_NAME,10)
    #endif
    #if MAX_MULTIPLICITY>9
DEF_INPUT(VERTEX_ATTRIB_NAME,11)
    #endif
    #if MAX_MULTIPLICITY>10
DEF_INPUT(VERTEX_ATTRIB_NAME,12)
    #endif
    #if MAX_MULTIPLICITY>11
DEF_INPUT(VERTEX_ATTRIB_NAME,13)
    #endif
    #if MAX_MULTIPLICITY>12
DEF_INPUT(VERTEX_ATTRIB_NAME,14)
    #endif
    #if MAX_MULTIPLICITY>13
DEF_INPUT(VERTEX_ATTRIB_NAME,15)
    #endif
    #if MAX_MULTIPLICITY>14
DEF_INPUT(VERTEX_ATTRIB_NAME,16)
    #endif
    #if MAX_MULTIPLICITY>15
DEF_INPUT(VERTEX_ATTRIB_NAME,17)
    #endif
  #endif//UNIVERSAL
#endif//USE_VERTEX_ARRAY





/////////////////////////////////////////////////////////////////////
// Outputs
/////////////////////////////////////////////////////////////////////

#ifdef USE_ARRAY_TRANSFER
out Opposite{vec4 Vertex[MAX_MULTIPLICITY];}O;
#else
  #define DEF_OUTPUT(x) out vec4 vOpposite##x;
  #if MAX_MULTIPLICITY>0
DEF_OUTPUT(0)
  #endif
  #if MAX_MULTIPLICITY>1
DEF_OUTPUT(1)
  #endif
  #if MAX_MULTIPLICITY>2
DEF_OUTPUT(2)
  #endif
  #if MAX_MULTIPLICITY>3
DEF_OUTPUT(3)
  #endif
  #if MAX_MULTIPLICITY>4
DEF_OUTPUT(4)
  #endif
  #if MAX_MULTIPLICITY>5
DEF_OUTPUT(5)
  #endif
  #if MAX_MULTIPLICITY>6
DEF_OUTPUT(6)
  #endif
  #if MAX_MULTIPLICITY>7
DEF_OUTPUT(7)
  #endif
  #if MAX_MULTIPLICITY>8
DEF_OUTPUT(8)
  #endif
  #if MAX_MULTIPLICITY>9
DEF_OUTPUT(9)
  #endif
  #if MAX_MULTIPLICITY>10
DEF_OUTPUT(10)
  #endif
  #if MAX_MULTIPLICITY>11
DEF_OUTPUT(11)
  #endif
  #if MAX_MULTIPLICITY>12
DEF_OUTPUT(12)
  #endif
  #if MAX_MULTIPLICITY>13
DEF_OUTPUT(13)
  #endif
  #if MAX_MULTIPLICITY>14
DEF_OUTPUT(14)
  #endif
  #if MAX_MULTIPLICITY>15
DEF_OUTPUT(15)
  #endif
#endif//USE_ARRAY_TRANSFER

out vec4 vVertexB;

#ifdef UNIVERSAL
out vec4 vNumberOfOppositeVertices;
#endif





/////////////////////////////////////////////////////////////////////
// Main function
/////////////////////////////////////////////////////////////////////

void main(){

#ifdef USE_VERTEX_ARRAY
  #define DEF_FILLA(x) gl_Position=x[0];
  #define DEF_FILLB(x) vVertexB=x[1];
  #define DEF_FILLN(x) vNumberOfOppositeVertices=x[2];
#else//USE_VERTEX_ARRAY
  #define DEF_FILLA(x) gl_Position=PASTER(x,0);
  #define DEF_FILLB(x) vVertexB=PASTER(x,1);
  #define DEF_FILLN(x) vNumberOfOppositeVertices=PASTER(x,2);
#endif//USE_VERTEX_ARRAY

  //set vertex A
  DEF_FILLA(VERTEX_ATTRIB_NAME)
  //set vertex B
  DEF_FILLB(VERTEX_ATTRIB_NAME)

#ifdef UNIVERSAL
  //set number of opposite vertices
  DEF_FILLN(VERTEX_ATTRIB_NAME)
#endif//UNIVERSAL

//cycle can be used only when USE_VERTEX_ARRAY and
//USE_ARRAY_TRANSFER
//otherwise it has to be assign manually
#if defined(USE_VERTEX_ARRAY) && defined(USE_ARRAY_TRANSFER)
  #ifdef UNIVERSAL
    #define DEF_FILL_RIGHT(x) x[3+o]
  #else//UNIVERSAL
    #define DEF_FILL_RIGHT(x) x[2+o]
  #endif//UNIVERSAL
  for(int o=0;o<MAX_MULTIPLICITY;++o)
    O.Vertex[o]=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME);
#else//defined(USE_VERTEX_ARRAY) && defined(USE_ARRAY_TRANSFER)
  #ifdef USE_VERTEX_ARRAY
    #ifdef USE_ARRAY_TRANSFER
      #error this is Dormons fault
    #else//USE_ARRAY_TRANSFER
      #define DEF_FILL_LEFT(x)    vOpposite##x
      #ifdef UNIVERSAL
        #define DEF_FILL_RIGHT(x,y) x[y]
      #else//UNIVERSAL
        #define DEF_FILL_RIGHT(x,y) PASTER(x,[y])
      #endif
    #endif//USE_ARRAY_TRANSFER
  #else//USE_VERTEX_ARRAY
    #ifdef USE_ARRAY_TRANSFER
      #define DEF_FILL_LEFT(x)    O.Vertex[x]
      #define DEF_FILL_RIGHT(x,y) PASTER(x,y)
    #else//USE_ARRAY_TRANSFER
      #define DEF_FILL_LEFT(x)    vOpposite##x
      #define DEF_FILL_RIGHT(x,y) PASTER(x,y)
    #endif//USE_ARRAY_TRANSFER
  #endif//USE_VERTEX_ARRAY

  //assign all attribs
  #ifdef UNIVERSAL
    #if MAX_MULTIPLICITY>0
  DEF_FILL_LEFT(0)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,3);
    #endif
    #if MAX_MULTIPLICITY>1
  DEF_FILL_LEFT(1)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,4);
    #endif
    #if MAX_MULTIPLICITY>2
  DEF_FILL_LEFT(2)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,5);
    #endif
    #if MAX_MULTIPLICITY>3
  DEF_FILL_LEFT(3)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,6);
    #endif
    #if MAX_MULTIPLICITY>4
  DEF_FILL_LEFT(4)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,7);
    #endif
    #if MAX_MULTIPLICITY>5
  DEF_FILL_LEFT(5)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,8);
    #endif
    #if MAX_MULTIPLICITY>6
  DEF_FILL_LEFT(6)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,9);
    #endif
    #if MAX_MULTIPLICITY>7
  DEF_FILL_LEFT(7)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,10);
    #endif
    #if MAX_MULTIPLICITY>8
  DEF_FILL_LEFT(8)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,11);
    #endif
    #if MAX_MULTIPLICITY>9
  DEF_FILL_LEFT(9)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,12);
    #endif
    #if MAX_MULTIPLICITY>10
  DEF_FILL_LEFT(10)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,13);
    #endif
    #if MAX_MULTIPLICITY>11
  DEF_FILL_LEFT(11)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,14);
    #endif
    #if MAX_MULTIPLICITY>12
  DEF_FILL_LEFT(12)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,15);
    #endif
    #if MAX_MULTIPLICITY>13
  DEF_FILL_LEFT(13)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,16);
    #endif
    #if MAX_MULTIPLICITY>14
  DEF_FILL_LEFT(14)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,17);
    #endif
    #if MAX_MULTIPLICITY>15
  DEF_FILL_LEFT(15)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,18);
    #endif
  #else//UNIVERSAL
    #if MAX_MULTIPLICITY>0
  DEF_FILL_LEFT(0)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,2);
    #endif
    #if MAX_MULTIPLICITY>1
  DEF_FILL_LEFT(1)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,3);
    #endif
    #if MAX_MULTIPLICITY>2
  DEF_FILL_LEFT(2)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,4);
    #endif
    #if MAX_MULTIPLICITY>3
  DEF_FILL_LEFT(3)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,5);
    #endif
    #if MAX_MULTIPLICITY>4
  DEF_FILL_LEFT(4)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,6);
    #endif
    #if MAX_MULTIPLICITY>5
  DEF_FILL_LEFT(5)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,7);
    #endif
    #if MAX_MULTIPLICITY>6
  DEF_FILL_LEFT(6)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,8);
    #endif
    #if MAX_MULTIPLICITY>7
  DEF_FILL_LEFT(7)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,9);
    #endif
    #if MAX_MULTIPLICITY>8
  DEF_FILL_LEFT(8)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,10);
    #endif
    #if MAX_MULTIPLICITY>9
   DEF_FILL_LEFT(9)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,11);
    #endif
    #if MAX_MULTIPLICITY>10
  DEF_FILL_LEFT(10)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,12);
    #endif
    #if MAX_MULTIPLICITY>11
  DEF_FILL_LEFT(11)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,13);
    #endif
    #if MAX_MULTIPLICITY>12
  DEF_FILL_LEFT(12)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,14);
    #endif
    #if MAX_MULTIPLICITY>13
  DEF_FILL_LEFT(13)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,15);
    #endif
    #if MAX_MULTIPLICITY>14
  DEF_FILL_LEFT(14)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,16);
    #endif
    #if MAX_MULTIPLICITY>15
  DEF_FILL_LEFT(15)=DEF_FILL_RIGHT(VERTEX_ATTRIB_NAME,17);
    #endif
  #endif//UNIVERSAL
#endif//defined(USE_VERTEX_ARRAY) && defined(USE_ARRAY_TRANSFER)
}

).";


std::string const gsSilGs = R".(


/////////////////////////////////////////////////////////////////////
// Options:
// if you define something, it will be applied.
// if you don't define something, opposite will be applied.
// Some defines has value that has to be set properly.
// Version number has to be chosen by user, preprocessor
// cannot do it (nothing useful can precede #version N P).
/////////////////////////////////////////////////////////////////////

//toggle determinism - define/don't define
//#define DETERMINISTIC
//toggle usage of reference edge - define/don't define
//#define REFERENCE_EDGE
//generate universal shader - define/don't define
//#define UNIVERSAL
//use arrays for transfer - define/don't define
//#define USE_ARRAY_TRANSFER
//use extension: GL_AMD_shader_stencil_value_export
//define/not define 
//#define USE_STENCIL_VALUE_EXPORT
//front faces are CCW - define/don't define
//#define CCW_IS_FRONT_FACE
//front faces are inside Shadow volume - define/don't define
//#define FRONT_FACE_INSIDE
//toggle usage of culling of shadow volume sides if 
//they are invisible
//#define CULL_SIDES
//shift front cap to infinity - define/don't define
//#define FRONT_CAP_TO_INFINITY
//shader will generate sides - define/don't define
//#define GENERATE_SIDES
//shader will generate caps - define/don't define
//#define GENERATE_CAPS
//name of matrix - define/don't define (will use fixed mvp)
//#define MATRIX mvp
//maximal number of opposite vertices - set value
//#define MAX_MULTIPLICITY 3
//name of light - set value
//#define LIGHT LightPosition

// DO NOT CHANGE ANYTHING BELOW THIS COMMENT!!!
// UNLESS, OF COURSE, YOU KNOW WHAT YOU ARE DOING.





/////////////////////////////////////////////////////////////////////
// TODO extensions and checks
/////////////////////////////////////////////////////////////////////

#if __VERSION__ < 330
  #extension GL_EXT_geometry_shader4:enable
#endif

#if MATRIX == gl_ModelViewProjectionMatrix && __VERSION__ >= 150
  #if GL_compatibility_profile != 1
    #error gl_ModelViewProjectionMatrix requiers\
    compatibility after version 140
  #endif
#endif

#if MAX_MULTIPLICITY > 16
  #error Max Multiplicity cannot exceed 16
#endif

#if MAX_MULTIPLICITY < 1
  #error Max Multiplicity cannont be 0 or less
#endif

#ifdef FRONT_CAP_TO_INFINITY
  #define SWIZZLE xyww
#else
  #define SWIZZLE xyzw
#endif

//TODO Vertex Attrib Array



/////////////////////////////////////////////////////////////////////
// compute indices of vertices of side and caps
// multiplicity is computed using CCW no matter what

// header of next table
// FRONT_FACE_INSIDE
// CCW_IS_FRONT_FACE
// Multiplicity possitive indices
// Multiplicity negative indices
// Stencil Value Export indices
//
// SIDES:
// FFI CCW | PS   NS    SVE
//   0   0 | 0123 1032  0123
//   0   1 | 1032 0123  1032
//   1   0 | 1032 0123  1032
//   1   1 | 0123 1023  0123
//
// CAPS:
// FFI CCW | PFC PBC NFC NBC  SVE
//   0   0 | 10i 23i 01i 32i  10i 23i
//   0   1 | 01i 32i 10i 23i  01i 32i
//   1   0 | 01i 32i 10i 23i  01i 32i
//   1   1 | 10i 23i 01i 32i  10i 23i
/////////////////////////////////////////////////////////////////////

//SIDES indices
#if defined(FRONT_FACE_INSIDE) ^ defined(CCW_IS_FRONT_FACE)
  //possitive multiplicity - Side index
  #define PS0 1
  #define PS1 0
  #define PS2 3
  #define PS3 2
  //negative multiplicity - Side index
  #define NS0 0
  #define NS1 1
  #define NS2 2
  #define NS3 3
#else
  //possitive multiplicity - Side index
  #define PS0 0
  #define PS1 1
  #define PS2 2
  #define PS3 3
  //negative multiplicity - Side index
  #define NS0 1
  #define NS1 0
  #define NS2 3
  #define NS3 2
#endif//defined(FRONT_FACE_INSIDE) ^ defined(CCW_IS_FRONT_FACE)

//CAPS indices
#if defined(FRONT_FACE_INSIDE) ^ defined(CCW_IS_FRONT_FACE)
  //possitive multiplicity - Front Cap index
  #define PFC0 0
  #define PFC1 1
  #define PFC2 i
  //possitive multiplicity - Back Cap index
  #define PBC0 3
  #define PBC1 2
  #define PBC2 i
  //negative multiplicity - Front Cap index
  #define NFC0 1
  #define NFC1 0
  #define NFC2 i
  //negative multiplicity - Back Cap index
  #define NBC0 2
  #define NBC1 3
  #define NBC2 i
#else
  //possitive multiplicity - Front Cap index
  #define PFC0 1
  #define PFC1 0
  #define PFC2 i
  //possitive multiplicity - Back Cap index
  #define PBC0 2
  #define PBC1 3
  #define PBC2 i
  //negative multiplicity - Front Cap index
  #define NFC0 0
  #define NFC1 1
  #define NFC2 i
  //negative multiplicity - Back Cap index
  #define NBC0 3
  #define NBC1 2
  #define NBC2 i
#endif//defined(FRONT_FACE_INSIDE) ^ defined(CCW_IS_FRONT_FACE)





/////////////////////////////////////////////////////////////////////
// compute max_vertices
/////////////////////////////////////////////////////////////////////

/*
#!/bin/python

MAX_MULTIPLICITY = 16

def PrintList(l):
  for idx,e in enumerate(l):
    if idx==0:
      print "      #if   MAX_MULTIPLICITY==",idx+1
      print "        #define MAX_VERTICES ",e
    else:
      print "      #elif MAX_MULTIPLICITY==",idx+1
      print "        #define MAX_VERTICES ",e
  print     "      #endif"

print """#ifdef USE_STENCIL_VALUE_EXPORT
  #ifdef GENERATE_SIDES
    #ifdef GENERATE_CAPS
      //sides and caps"""
PrintList([4+i*2*3 for i in range(1,MAX_MULTIPLICITY+1)])
print """    #else
      //sides only
      #define MAX_VERTICES 4
    #endif//GENERATE_CAPS
  #else
    #ifdef GENERATE_CAPS
      //caps only"""
PrintList([i*2*3 for i in range(1,MAX_MULTIPLICITY+1)])
print """    #else
      #error Sides or caps have to be generated!
    #endif//GENERATE_CAPS
  #endif//GENERATE_SIDES
#else
  #ifdef GENERATE_SIDES
    #ifdef GENERATE_CAPS
      //sides and caps"""
PrintList([4*i+i*2*3 for i in range(1,MAX_MULTIPLICITY+1)])
print """    #else
      //sides only"""
PrintList([4*i for i in range(1,MAX_MULTIPLICITY+1)])
print """    #endif//GENERATE_CAPS
  #else
    #ifdef GENERATE_CAPS
      //caps only"""
PrintList([i*2*3 for i in range(1,MAX_MULTIPLICITY+1)])
print """    #else
      #error Sides or caps have to be generated!
    #endif//GENERATE_CAPS
  #endif//GENERATE_SIDES
#endif//USE_STENCIL_VALUE_EXPORT
"""
*/

#ifdef USE_STENCIL_VALUE_EXPORT
  #ifdef GENERATE_SIDES
    #ifdef GENERATE_CAPS
      //sides and caps
      #if   MAX_MULTIPLICITY== 1
        #define MAX_VERTICES  10
      #elif MAX_MULTIPLICITY== 2
        #define MAX_VERTICES  16
      #elif MAX_MULTIPLICITY== 3
        #define MAX_VERTICES  22
      #elif MAX_MULTIPLICITY== 4
        #define MAX_VERTICES  28
      #elif MAX_MULTIPLICITY== 5
        #define MAX_VERTICES  34
      #elif MAX_MULTIPLICITY== 6
        #define MAX_VERTICES  40
      #elif MAX_MULTIPLICITY== 7
        #define MAX_VERTICES  46
      #elif MAX_MULTIPLICITY== 8
        #define MAX_VERTICES  52
      #elif MAX_MULTIPLICITY== 9
        #define MAX_VERTICES  58
      #elif MAX_MULTIPLICITY== 10
        #define MAX_VERTICES  64
      #elif MAX_MULTIPLICITY== 11
        #define MAX_VERTICES  70
      #elif MAX_MULTIPLICITY== 12
        #define MAX_VERTICES  76
      #elif MAX_MULTIPLICITY== 13
        #define MAX_VERTICES  82
      #elif MAX_MULTIPLICITY== 14
        #define MAX_VERTICES  88
      #elif MAX_MULTIPLICITY== 15
        #define MAX_VERTICES  94
      #elif MAX_MULTIPLICITY== 16
        #define MAX_VERTICES  100
      #endif
    #else
      //sides only
      #define MAX_VERTICES 4
    #endif//GENERATE_CAPS
  #else
    #ifdef GENERATE_CAPS
      //caps only
      #if   MAX_MULTIPLICITY== 1
        #define MAX_VERTICES  6
      #elif MAX_MULTIPLICITY== 2
        #define MAX_VERTICES  12
      #elif MAX_MULTIPLICITY== 3
        #define MAX_VERTICES  18
      #elif MAX_MULTIPLICITY== 4
        #define MAX_VERTICES  24
      #elif MAX_MULTIPLICITY== 5
        #define MAX_VERTICES  30
      #elif MAX_MULTIPLICITY== 6
        #define MAX_VERTICES  36
      #elif MAX_MULTIPLICITY== 7
        #define MAX_VERTICES  42
      #elif MAX_MULTIPLICITY== 8
        #define MAX_VERTICES  48
      #elif MAX_MULTIPLICITY== 9
        #define MAX_VERTICES  54
      #elif MAX_MULTIPLICITY== 10
        #define MAX_VERTICES  60
      #elif MAX_MULTIPLICITY== 11
        #define MAX_VERTICES  66
      #elif MAX_MULTIPLICITY== 12
        #define MAX_VERTICES  72
      #elif MAX_MULTIPLICITY== 13
        #define MAX_VERTICES  78
      #elif MAX_MULTIPLICITY== 14
        #define MAX_VERTICES  84
      #elif MAX_MULTIPLICITY== 15
        #define MAX_VERTICES  90
      #elif MAX_MULTIPLICITY== 16
        #define MAX_VERTICES  96
      #endif
    #else
      #error Sides or caps have to be generated!
    #endif//GENERATE_CAPS
  #endif//GENERATE_SIDES
#else
  #ifdef GENERATE_SIDES
    #ifdef GENERATE_CAPS
      //sides and caps
      #if   MAX_MULTIPLICITY== 1
        #define MAX_VERTICES  10
      #elif MAX_MULTIPLICITY== 2
        #define MAX_VERTICES  20
      #elif MAX_MULTIPLICITY== 3
        #define MAX_VERTICES  30
      #elif MAX_MULTIPLICITY== 4
        #define MAX_VERTICES  40
      #elif MAX_MULTIPLICITY== 5
        #define MAX_VERTICES  50
      #elif MAX_MULTIPLICITY== 6
        #define MAX_VERTICES  60
      #elif MAX_MULTIPLICITY== 7
        #define MAX_VERTICES  70
      #elif MAX_MULTIPLICITY== 8
        #define MAX_VERTICES  80
      #elif MAX_MULTIPLICITY== 9
        #define MAX_VERTICES  90
      #elif MAX_MULTIPLICITY== 10
        #define MAX_VERTICES  100
      #elif MAX_MULTIPLICITY== 11
        #define MAX_VERTICES  110
      #elif MAX_MULTIPLICITY== 12
        #define MAX_VERTICES  120
      #elif MAX_MULTIPLICITY== 13
        #define MAX_VERTICES  130
      #elif MAX_MULTIPLICITY== 14
        #define MAX_VERTICES  140
      #elif MAX_MULTIPLICITY== 15
        #define MAX_VERTICES  150
      #elif MAX_MULTIPLICITY== 16
        #define MAX_VERTICES  160
      #endif
    #else
      //sides only
      #if   MAX_MULTIPLICITY== 1
        #define MAX_VERTICES  4
      #elif MAX_MULTIPLICITY== 2
        #define MAX_VERTICES  8
      #elif MAX_MULTIPLICITY== 3
        #define MAX_VERTICES  12
      #elif MAX_MULTIPLICITY== 4
        #define MAX_VERTICES  16
      #elif MAX_MULTIPLICITY== 5
        #define MAX_VERTICES  20
      #elif MAX_MULTIPLICITY== 6
        #define MAX_VERTICES  24
      #elif MAX_MULTIPLICITY== 7
        #define MAX_VERTICES  28
      #elif MAX_MULTIPLICITY== 8
        #define MAX_VERTICES  32
      #elif MAX_MULTIPLICITY== 9
        #define MAX_VERTICES  36
      #elif MAX_MULTIPLICITY== 10
        #define MAX_VERTICES  40
      #elif MAX_MULTIPLICITY== 11
        #define MAX_VERTICES  44
      #elif MAX_MULTIPLICITY== 12
        #define MAX_VERTICES  48
      #elif MAX_MULTIPLICITY== 13
        #define MAX_VERTICES  52
      #elif MAX_MULTIPLICITY== 14
        #define MAX_VERTICES  56
      #elif MAX_MULTIPLICITY== 15
        #define MAX_VERTICES  60
      #elif MAX_MULTIPLICITY== 16
        #define MAX_VERTICES  64
      #endif
    #endif//GENERATE_CAPS
  #else
    #ifdef GENERATE_CAPS
      //caps only
      #if   MAX_MULTIPLICITY== 1
        #define MAX_VERTICES  6
      #elif MAX_MULTIPLICITY== 2
        #define MAX_VERTICES  12
      #elif MAX_MULTIPLICITY== 3
        #define MAX_VERTICES  18
      #elif MAX_MULTIPLICITY== 4
        #define MAX_VERTICES  24
      #elif MAX_MULTIPLICITY== 5
        #define MAX_VERTICES  30
      #elif MAX_MULTIPLICITY== 6
        #define MAX_VERTICES  36
      #elif MAX_MULTIPLICITY== 7
        #define MAX_VERTICES  42
      #elif MAX_MULTIPLICITY== 8
        #define MAX_VERTICES  48
      #elif MAX_MULTIPLICITY== 9
        #define MAX_VERTICES  54
      #elif MAX_MULTIPLICITY== 10
        #define MAX_VERTICES  60
      #elif MAX_MULTIPLICITY== 11
        #define MAX_VERTICES  66
      #elif MAX_MULTIPLICITY== 12
        #define MAX_VERTICES  72
      #elif MAX_MULTIPLICITY== 13
        #define MAX_VERTICES  78
      #elif MAX_MULTIPLICITY== 14
        #define MAX_VERTICES  84
      #elif MAX_MULTIPLICITY== 15
        #define MAX_VERTICES  90
      #elif MAX_MULTIPLICITY== 16
        #define MAX_VERTICES  96
      #endif
    #else
      #error Sides or caps have to be generated!
    #endif//GENERATE_CAPS
  #endif//GENERATE_SIDES
#endif//USE_STENCIL_VALUE_EXPORT

layout(points)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;





/////////////////////////////////////////////////////////////////////
// Uniforms
/////////////////////////////////////////////////////////////////////

#ifdef MATRIX
uniform mat4 MATRIX;
#else
  #define MATRIX gl_ModelViewProjectionMatrix
#endif

uniform vec4 LIGHT;


)." + 

std::string(R".(
/////////////////////////////////////////////////////////////////////
// Inputs from vertex shader
/////////////////////////////////////////////////////////////////////

#ifdef USE_ARRAY_TRANSFER
in Opposite{vec4 Vertex[MAX_MULTIPLICITY];}O[];
#else
  #define DEF_INPUT(x) in vec4 vOpposite##x[];
  #if MAX_MULTIPLICITY>0
    DEF_INPUT(0)
  #endif
  #if MAX_MULTIPLICITY>1
    DEF_INPUT(1)
  #endif
  #if MAX_MULTIPLICITY>2
    DEF_INPUT(2)
  #endif
  #if MAX_MULTIPLICITY>3
    DEF_INPUT(3)
  #endif
  #if MAX_MULTIPLICITY>4
    DEF_INPUT(4)
  #endif
  #if MAX_MULTIPLICITY>5
    DEF_INPUT(5)
  #endif
  #if MAX_MULTIPLICITY>6
    DEF_INPUT(6)
  #endif
  #if MAX_MULTIPLICITY>7
    DEF_INPUT(7)
  #endif
  #if MAX_MULTIPLICITY>8
    DEF_INPUT(8)
  #endif
  #if MAX_MULTIPLICITY>9
    DEF_INPUT(9)
  #endif
  #if MAX_MULTIPLICITY>10
    DEF_INPUT(10)
  #endif
  #if MAX_MULTIPLICITY>11
    DEF_INPUT(11)
  #endif
  #if MAX_MULTIPLICITY>12
    DEF_INPUT(12)
  #endif
  #if MAX_MULTIPLICITY>13
    DEF_INPUT(13)
  #endif
  #if MAX_MULTIPLICITY>14
    DEF_INPUT(14)
  #endif
  #if MAX_MULTIPLICITY>15
    DEF_INPUT(15)
  #endif
#endif//USE_ARRAY_TRANSFER

in vec4 vVertexB[];

#ifdef UNIVERSAL
in vec4 vNumberOfOppositeVertices[];
#endif





/////////////////////////////////////////////////////////////////////
// Outputs from geometry shader
/////////////////////////////////////////////////////////////////////

#ifdef USE_STENCIL_VALUE_EXPORT
flat out int gMultiplicity;
#endif





/////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////

/**
* @brief Computes greater vector
*
* @param a vertex a
* @param b vertex b
*
* @return 1 if a>b, 0 if a==b, -1 if b<a
*/
int GreaterVec(in vec3 a,in vec3 b){
  return int(dot(sign(a-b),vec3(4,2,1)));
}

#ifdef REFERENCE_EDGE
/**
* @brief Function computes multiplicity for one opposite vertex
*
* @param A smallest vertex of a triangle
* @param B middle vertex of a triangle
* @param C largest vertex of a triangle
* @param L light position
*
* @return 1 ABC (CCW) facing L, -1 ABC (CCW) not-facing L
*/
int ComputeMult(in vec3 A,in vec3 B,in vec3 C,in vec4 L){
  vec3 n=cross(C-A,L.xyz-A*L.w);//normal vector of light plane
  return int(sign(dot(n,B-A)));//multiplicity
}
#endif//REFERENCE_EDGE

#if defined(CULL_SIDES) &&defined(GENERATE_SIDES)

/**
 * @brief Check if edge is visible
 *
 * @param A point A
 * @param B point B
 *
 * @return true -> edge is visible
 */
bool IsEdgeVisible(in vec4 A,in vec4 B){
  vec3 M=+A.xyz+A.www;
  vec3 N=+B.xyz+B.www;
  vec3 O=-A.xyz+A.www;
  vec3 P=-B.xyz+B.www;
  vec3 NM=N-M;
  vec3 PO=P-O;
  float Left=0;
  float Right=1;
  for(int i=0;i<3;++i){
    if(NM[i]==0){
      if(M[i]<0)return false;
    }else{
      if(NM[i]>0)Left=max(Left,-M[i]/NM[i]);
      else Right=min(Right,-M[i]/NM[i]);
    }
                                              
    if(PO[i]==0){
      if(O[i]<0)return false;
    }else{
      if(PO[i]>0)Left=max(Left,-O[i]/PO[i]);
      else Right=min(Right,-O[i]/PO[i]);
    }
  }
  return Left<=Right;
}

/**
 * @brief Checks if side covers fullscreen
 *
 * @param A point A
 * @param B vector B-A
 * @param C vector C-A
 * @param Diag diagonal id
 *
 * @return true -> side is visible
 */
bool IsFullVisible(in vec4 A,in vec4 B,in vec4 C,int Diag){
  vec3 a=A.xyz;
  vec3 b=B.xyz;
  vec3 c=C.xyz;
  if(Diag>=0){
    a[Diag]=-a[Diag];
    b[Diag]=-b[Diag];
    c[Diag]=-c[Diag];
  }
  float m=(a.x-a.y);
  float n=(b.x-b.y);
  float o=(c.x-c.y);
  float p=(a.x-a.z);
  float q=(b.x-b.z);
  float r=(c.x-c.z);
  float d=(q*o-n*r);
  float t=(m*r-p*o)/d;
  float l=-(m*q-p*n)/d;
  vec4 X=A+t*B+l*C;
  return (t>0)&&(t<1)&&(l>0)&&(l<1)&&
      all(greaterThan(X.xyz,-X.www))&&all(lessThan(X.xyz,X.www));
}
).") + 

std::string(R".(
/**
 * @brief Check if side is visible
 *
 * @param P[4] points of side
 * @param Diag diagonal id
 *
 * @return true -> side is visible
 */
bool IsVisible(in vec4 P[4],in int Diag){
  if(IsFullVisible(P[0],P[1]-P[0],P[2]-P[0],Diag))return true;
  if(IsEdgeVisible(P[0],P[1]))return true;
  if(IsEdgeVisible(P[0],P[2]))return true;
  if(IsEdgeVisible(P[1],P[3]))return true;
  if(IsEdgeVisible(P[2],P[3]))return true;
  return false;
}

#endif//defined(CULL_SIDES) &&defined(GENERATE_SIDES)





/////////////////////////////////////////////////////////////////////
// Main function
/////////////////////////////////////////////////////////////////////

void main(){
  vec4 P[4];
  P[0]=gl_in[0].gl_Position;
  P[1]=vVertexB[0];
  P[2]=vec4(P[0].xyz*LIGHT.w-LIGHT.xyz,0);
  P[3]=vec4(P[1].xyz*LIGHT.w-LIGHT.xyz,0);

#if defined(CULL_SIDES) && defined(GENERATE_SIDES)
  vec4 ClipP[4];//clip space coords
  for(int i=0;i<4;++i)
    ClipP[i]=MATRIX*P[i];

  vec3 Normal=(MATRIX*vec4(cross(
      P[1].xyz-P[0].xyz,
      LightPosition.xyz-P[0].xyz*LightPosition.w),0)).xyz;
  ivec3 Corner=ivec3(1+sign(Normal))>>1;
  if(Corner.z==1);Corner=ivec3(1)-Corner;
  int Diag=Corner.x+(Corner.y<<1)-1;
#endif//defined(CULL_SIDES) && defined(GENERATE_SIDES)

#if defined(CULL_SIDES) && defined(GENERATE_SIDES)
  #ifdef GENERATE_CAPS
  bool NotCull=IsVisible(ClipP,Diag);
  #else//GENERATE_CAPS
  if(!IsVisible(ClipP,Diag))return;
  #endif//GENERATE_CAPS
#endif

#ifndef USE_ARRAY_TRANSFER
  #define DEF_FILL(x) O[##x##]=vOpposite##x[0];
  vec4 O[MAX_MULTIPLICITY];
   #if MAX_MULTIPLICITY>0
    DEF_FILL(0)
  #endif
  #if MAX_MULTIPLICITY>1
    DEF_FILL(1)
  #endif
  #if MAX_MULTIPLICITY>2
    DEF_FILL(2)
  #endif
  #if MAX_MULTIPLICITY>3
    DEF_FILL(3)
  #endif
  #if MAX_MULTIPLICITY>4
    DEF_FILL(4)
  #endif
  #if MAX_MULTIPLICITY>5
    DEF_FILL(5)
  #endif
  #if MAX_MULTIPLICITY>6
    DEF_FILL(6)
  #endif
  #if MAX_MULTIPLICITY>7
    DEF_FILL(7)
  #endif
  #if MAX_MULTIPLICITY>8
    DEF_FILL(8)
  #endif
  #if MAX_MULTIPLICITY>9
    DEF_FILL(9)
  #endif
  #if MAX_MULTIPLICITY>10
    DEF_FILL(10)
  #endif
  #if MAX_MULTIPLICITY>11
    DEF_FILL(11)
  #endif
  #if MAX_MULTIPLICITY>12
    DEF_FILL(12)
  #endif
  #if MAX_MULTIPLICITY>13
    DEF_FILL(13)
  #endif
  #if MAX_MULTIPLICITY>14
    DEF_FILL(14)
  #endif
  #if MAX_MULTIPLICITY>15
    DEF_FILL(15)
  #endif
#endif//USE_ARRAY_TRANSFER

#ifdef UNIVERSAL
  int Num=int(vNumberOfOppositeVertices[0].x);
#endif

#ifdef GENERATE_SIDES
  int Multiplicity=0;
#endif//GENERATE_SIDES

#ifdef UNIVERSAL
  for(int i=0;i<Num;++i)
#else
  for(int i=0;i<MAX_MULTIPLICITY;++i)
#endif//UNIVERSAL
  {
    int ActMultiplicity=0;//+1 (T0T1T2) CCW frontface L
#define T0 P[0].xyz
#define T1 P[1].xyz
#ifdef USE_ARRAY_TRANSFER
  #define T2 O[0].Vertex[i].xyz
  #define ActOpposite O[0].Vertex[i]
#else//USE_ARRAY_TRANSFER
  #define T2 O[i].xyz
  #define ActOpposite O[i]
#endif//USE_ARRAY_TRANSFER

#ifdef REFERENCE_EDGE
  #ifdef DETERMINISTIC
    if(GreaterVec(T0,T2)>0){//T[2] T[0] T[1]?
      ActMultiplicity=+ComputeMult(T2,T0,T1,LightPosition);
    }else{
      if(GreaterVec(T1,T2)>0){//T[0] T[2] T[1]?
        ActMultiplicity=-ComputeMult(T0,T2,T1,LightPosition);
      }else{//T[0] T[1] T[2]?
        ActMultiplicity=+ComputeMult(T0,T1,T2,LightPosition);
      }
    }
  #else//NONDETERMINISTIC
    ActMultiplicity=-ComputeMult(T0,T2,T1,LightPosition);
  #endif//DETERMINISTIC
#else//GRAPHICON
  #ifdef DETERMINISTIC
    vec3 T[3];
    vec3 D[3];
    vec3 NS[3];
    vec4 PL[3];
    float d[3];

    D[0]=LIGHT.xyz-T0*LIGHT.w;//vector to the lights from T0
    NS[0]=normalize(cross(T1-T0,D[0]));//normal vector of Light plane
    PL[0]=vec4(NS[0],-dot(NS[0],T0));//light plane
    d[0]=dot(PL[0],vec4(T2,1));//-1 if (T0T1T2) CCW is frontfacing L


    D[1]=LIGHT.xyz-T1*LIGHT.w;
    D[2]=LIGHT.xyz-T2*LIGHT.w;

    if(GreaterVec(T2,T0)>0){
      NS[1]=normalize(cross(T2-T0,D[0]));
      PL[1]=vec4(NS[1],-dot(NS[1],T0));
      d[1]=dot(PL[1],vec4(T1,1));
    }else{
      NS[1]=normalize(cross(T0-T2,D[2]));
      PL[1]=vec4(NS[1],-dot(NS[1],T2));
      d[1]=-dot(PL[1],vec4(T1,1));
    }

    if(GreaterVec(T2,T1)>0){
      NS[2]=normalize(cross(T2-T1,D[1]));
      PL[2]=vec4(NS[2],-dot(NS[2],T1));
      d[2]=dot(PL[2],vec4(T0,1));
    }else{
      NS[2]=normalize(cross(T1-T2,D[2]));
      PL[2]=vec4(NS[2],-dot(NS[2],T2));
      d[2]=-dot(PL[2],vec4(T0,1));
    }

    if(d[0]==0||d[1]==0||d[2]==0)continue;
    if(!((d[0]<0&&d[1]>0&&d[2]<0)||(d[0]>0&&d[1]<0&&d[2]>0)))continue;
    ActMultiplicity=-int(sign(d[0]));
  #else//NONDETERMINISTIC
    vec3 D=LIGHT.xyz-T0*LIGHT.w;
    vec3 NS=normalize(cross(T1-T0,D));
    vec4 PL=vec4(NS,-dot(NS,T0));
    float d=dot(PL,vec4(T2,1));//-1 if (T0T1T2) CCW is frontfacing L
    ActMultiplicity=-int(sign(d));
  #endif//DETERMINISTIC
#endif//REFERENCE_EDGE

#ifdef GENERATE_CAPS
  if(ActMultiplicity!=0&&ActOpposite.w==1){
  #ifdef USE_STENCIL_VALUE_EXPORT
    #if defined(CULL_SIDES) && defined(GENERATE_SIDES)
    //front cap
    gMultiplicity=ActMultiplicity;
    gl_Position=ClipP[PFC0].SWIZZLE;EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=ClipP[PFC1].SWIZZLE;EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=(MATRIX*ActOpposite).SWIZZLE;
    EmitVertex();
    EndPrimitive();
    //back cap
    gMultiplicity=ActMultiplicity;gl_Position=ClipP[PBC0];EmitVertex();
    gMultiplicity=ActMultiplicity;gl_Position=ClipP[PBC1];EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
    EmitVertex();
    EndPrimitive();
    #else//defined(CULL_SIDES) && defined(GENERATE_SIDES)
    //front cap
    gMultiplicity=ActMultiplicity;
    gl_Position=(MATRIX*P[PFC0]).SWIZZLE;
    EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=(MATRIX*P[PFC1]).SWIZZLE;
    EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=(MATRIX*ActOpposite).SWIZZLE;
    EmitVertex();
    EndPrimitive();
    //back cap
    gMultiplicity=ActMultiplicity;
    gl_Position=MATRIX*P[PBC0];
    EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=MATRIX*P[PBC1];
    EmitVertex();
    gMultiplicity=ActMultiplicity;
    gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
    EmitVertex();
    EndPrimitive();
    #endif//defined(CULL_SIDES) && defined(GENERATE_SIDES)
  #else//USE_STENCIL_VALUE_EXPORT
    #if defined(CULL_SIDES) && defined(GENERATE_SIDES)
    if(ActMultiplicity>0){
      //front cap
      gl_Position=ClipP[PFC0].SWIZZLE;EmitVertex();
      gl_Position=ClipP[PFC1].SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*ActOpposite).SWIZZLE;
      EmitVertex();
      EndPrimitive();
      //back cap
      gl_Position=ClipP[PBC0];EmitVertex();
      gl_Position=ClipP[PBC1];EmitVertex();
      gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
      EmitVertex();
      EndPrimitive();
    }else{
      //front cap
      gl_Position=ClipP[NFC0].SWIZZLE;EmitVertex();
      gl_Position=ClipP[NFC1].SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*ActOpposite).SWIZZLE;
      EmitVertex();
      EndPrimitive();
      //back cap
      gl_Position=ClipP[NBC0];EmitVertex();
      gl_Position=ClipP[NBC1];EmitVertex();
      gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
      EmitVertex();
      EndPrimitive();
    }
    #else//defined(CULL_SIDES) && defined(GENERATE_SIDES)
    if(ActMultiplicity>0){
      //front cap
      gl_Position=(MATRIX*P[PFC0]).SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*P[PFC1]).SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*ActOpposite).SWIZZLE;
      EmitVertex();
      EndPrimitive();
      //back cap
      gl_Position=MATRIX*P[PBC0];EmitVertex();
      gl_Position=MATRIX*P[PBC1];EmitVertex();
      gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
      EmitVertex();
      EndPrimitive();
    }else{
      //front cap
      gl_Position=(MATRIX*P[NFC0]).SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*P[NFC1]).SWIZZLE;EmitVertex();
      gl_Position=(MATRIX*ActOpposite).SWIZZLE;
      EmitVertex();
      EndPrimitive();
      //back cap
      gl_Position=MATRIX*P[NBC0];EmitVertex();
      gl_Position=MATRIX*P[NBC1];EmitVertex();
      gl_Position=MATRIX*vec4(ActOpposite.xyz*LIGHT.w-LIGHT.xyz,0);
      EmitVertex();
      EndPrimitive();
    }
    #endif//defined(CULL_SIDES) && defined(GENERATE_SIDES)
  #endif//USE_STENCIL_VALUE_EXPORT
  }
#endif//GENERATE_CAPS

#ifdef GENERATE_SIDES
  #if defined(CULL_SIDES) && defined(GENERATE_CAPS)
    if(NotCull)
  #endif//defined(CULL_SIDES) && defined(GENERATE_CAPS)
    Multiplicity+=ActMultiplicity;//sum up act multiplicities
#endif//GENERATE_SIDES
  }//for

#ifdef GENERATE_SIDES
  #ifdef USE_STENCIL_VALUE_EXPORT
    if(Multiplicity!=0){
    #ifdef CULL_SIDES
      gMultiplicity=Multiplicity;gl_Position=ClipP[PS0];EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=ClipP[PS1];EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=ClipP[PS2];EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=ClipP[PS3];EmitVertex();
    #else//CULL_SIDES
      gMultiplicity=Multiplicity;gl_Position=MATRIX*P[PS0];
      EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=MATRIX*P[PS1];
      EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=MATRIX*P[PS2];
      EmitVertex();
      gMultiplicity=Multiplicity;gl_Position=MATRIX*P[PS3];
      EmitVertex();
    #endif//CULL_SIDES
      EndPrimitive();
    }
  #else//USE_STENCIL_VALUE_EXPORT
  if(Multiplicity>0){//more caps (CCW) frontface L
    for(int i=0;i<Multiplicity;++i){
    #ifdef CULL_SIDES
      gl_Position=ClipP[PS0];EmitVertex();
      gl_Position=ClipP[PS1];EmitVertex();
      gl_Position=ClipP[PS2];EmitVertex();
      gl_Position=ClipP[PS3];EmitVertex();
    #else//CULL_SIDES
      gl_Position=MATRIX*P[PS0];EmitVertex();
      gl_Position=MATRIX*P[PS1];EmitVertex();
      gl_Position=MATRIX*P[PS2];EmitVertex();
      gl_Position=MATRIX*P[PS3];EmitVertex();
    #endif//CULL_SIDES
      EndPrimitive();
    }
  }
  if(Multiplicity<0){//more caps (CCW) backface L
    Multiplicity=-Multiplicity;
    for(int i=0;i<Multiplicity;++i){
    #ifdef CULL_SIDES
      gl_Position=ClipP[NS0];EmitVertex();
      gl_Position=ClipP[NS1];EmitVertex();
      gl_Position=ClipP[NS2];EmitVertex();
      gl_Position=ClipP[NS3];EmitVertex();
    #else//CULL_SIDES
      gl_Position=MATRIX*P[NS0];EmitVertex();
      gl_Position=MATRIX*P[NS1];EmitVertex();
      gl_Position=MATRIX*P[NS2];EmitVertex();
      gl_Position=MATRIX*P[NS3];EmitVertex();
    #endif//CULL_SIDES
      EndPrimitive();
    }
  }
  #endif//USE_STENCIL_VALUE_EXPORT
#endif//GENERATE_CAPS
}


).");

std::string const gsSilFs = R".(

/////////////////////////////////////////////////////////////////////
// Options:
// if you define something, it will be applied.
// if you don't define something, opposite will be applied.
// Some defines has value that has to be set properly.
// Version number has to be chosen by user, preprocessor
// cannot do it (nothing useful can precede #version N P).
/////////////////////////////////////////////////////////////////////

//use extension: GL_AMD_shader_stencil_value_export
//define/not define 
//#define USE_STENCIL_VALUE_EXPORT
//use layouts - define/don't define
//#define USE_LAYOUTS
//visualize front and back faces with different color
//#define VISUALIZE

// DO NOT CHANGE ANYTHING BELOW THIS COMMENT!!!
//UNLESS, OF COURSE, YOU KNOW WHAT YOU ARE DOING.





/////////////////////////////////////////////////////////////////////
// TODO extensions and checks
/////////////////////////////////////////////////////////////////////

#ifdef USE_STENCIL_VALUE_EXPORT
  #extension GL_ARB_shader_stencil_export:enable
#endif





/////////////////////////////////////////////////////////////////////
// Inputs
/////////////////////////////////////////////////////////////////////

#ifdef USE_STENCIL_VALUE_EXPORT
flat in int gMultiplicity;
#endif//USE_STENCIL_VALUE_EXPORT






/////////////////////////////////////////////////////////////////////
// Outputs from geometry shader
/////////////////////////////////////////////////////////////////////

#ifdef VISUALIZE
  #ifdef USE_LAYOUTS
layout(location=0)out vec4 fColor;
  #else//USE_LAYOUTS
out vec4 fColor;
  #endif//USE_LAYOUTS
#endif//VISUALIZE





/////////////////////////////////////////////////////////////////////
// Main function
/////////////////////////////////////////////////////////////////////

void main(){
#ifdef USE_STENCIL_VALUE_EXPORT
  gl_FragStencilValueAMD=gMultiplicity; 
#endif//USE_STENCIL_VALUE_EXPORT

#ifdef VISUALIZE
  if(gl_FrontFacing)fColor=vec4(0,1,0,1);
  else fColor=vec4(1,0,0,1);
#endif//VISUALIZE
}


).";