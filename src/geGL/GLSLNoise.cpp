#include<geGL/GLSLNoise.h>

std::string ge::gl::getNoiseSource(){
  return R".(
#define JOIN1(x,y) x##y
#define JOIN0(x,y) JOIN1(x,y)
#define JOIN(x,y)  JOIN0(x,y)

#define VEC1 float
#define VEC2 vec2
#define VEC3 vec3
#define VEC4 vec4

#define IVEC1 int
#define IVEC2 ivec2
#define IVEC3 ivec3
#define IVEC4 ivec4

#define UVEC1 uint
#define UVEC2 uvec2
#define UVEC3 uvec3
#define UVEC4 uvec4

#define VECXI(x,m,i) JOIN(x,JOIN(VECI,m(i)))
#define VECI1(i) 
#define VECI2(i) [i]
#define VECI3(i) [i]
#define VECI4(i) [i]

const uint UINT_0       = 0u         ;
const uint UINT_1       = 1u         ;
const uint UINT_2       = 2u         ;
const uint UINT_MAXDIV2 = 0x7fffffffu;
const uint UINT_MAX     = 0xffffffffu;

uint poly(in uint x,in uint c){
  //return x;
  //return x*(x+c);
  //return x*(x*(x+c)+c);
  //return x*(x*(x*(x+c)+c)+c);
  return x*(x*(x*(x*(x+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c)+c)+c);
}

#define BASE(DIMENSION)                                     \
float baseIntegerNoise(in JOIN(UVEC,DIMENSION) x){          \
  uint last = 10u;                                          \
  for(uint i = 0u; i < DIMENSION##u; ++i)                   \
    last = poly( VECXI(x,DIMENSION,i) + (20024u << i),last);\
  return -1. + float(last)/float(UINT_MAXDIV2);             \
}                                                           \
uint baseIntegerNoiseU(in JOIN(UVEC,DIMENSION) x){          \
  uint last = 10u;                                          \
  for(uint i = 0u; i < DIMENSION##u; ++i)                   \
    last = poly( VECXI(x,DIMENSION,i) + (20024u << i),last);\
  return last;                                              \
}


#define SMOOTH(DIMENSION)                                                          \
float smoothNoise(in uint d,in JOIN(UVEC,DIMENSION) x){                            \
  if(d == 0u)return baseIntegerNoise(x);                                           \
  uint dd = 1u << d;                                                               \
  JOIN(UVEC,DIMENSION) xx = x >> d;                                                \
  JOIN(VEC,DIMENSION) t = JOIN(VEC,DIMENSION)(x&(dd-1u)) / JOIN(VEC,DIMENSION)(dd);\
  float ret = 0.f;                                                                 \
  for(uint i = 0u; i < (1u << DIMENSION); ++i){                                    \
    float coef = 1.f;                                                              \
    JOIN(UVEC,DIMENSION) o;                                                        \
    for(uint j = 0u; j < DIMENSION##u; ++j){                                       \
      VECXI(o,DIMENSION,j) = (i >> j) & 1u;                                        \
      coef *= smoothstep(0.f,1.f,float(1u - ((i >> j)&1u))*(1. - 2.*VECXI(t,DIMENSION,j)) + VECXI(t,DIMENSION,j));\
    }                                                                              \
    ret += baseIntegerNoise((xx + o<<d)&(0xffffffff>>d)) * coef;                   \
  }                                                                                \
  return ret;                                                                      \
}


#define OCTAVE(DIMENSION)                                          \
float noise(in JOIN(UVEC,DIMENSION) x,in uint M,in uint N,float p){\
  float ret = 0.f;                                                 \
  float sum = 0.f;                                                 \
  for(uint k = 0u; k <= N; ++k){                                   \
    sum *= p;                                                      \
    sum += 1.f;                                                    \
    ret *= p;                                                      \
    ret += smoothNoise(M-k,x);                                     \
  }                                                                \
  return ret/sum;                                                  \
}

#define OCTAVE_SIMPLIFIED(DIMENSION)             \
float noise(in JOIN(UVEC,DIMENSION) x,in uint M){\
  return noise(x,M,M,2.f);                       \
}

#define FNOISE(DIMENSION)                                       \
float noise(in JOIN(VEC,DIMENSION) x,in uint M){                \
  return noise(JOIN(UVEC,DIMENSION)(JOIN(IVEC,DIMENSION)(x)),M);\
}

#define INOISE(DIMENSION)                                          \
float noise(in JOIN(IVEC,DIMENSION) x,in uint M,in uint N,float p){\
  return noise(JOIN(UVEC,DIMENSION)(x),M,N,p);                     \
}

BASE(1)
BASE(2)
BASE(3)
BASE(4)

SMOOTH(1)
SMOOTH(2)
SMOOTH(3)
SMOOTH(4)

OCTAVE(1)
OCTAVE(2)
OCTAVE(3)
OCTAVE(4)

OCTAVE_SIMPLIFIED(1)
OCTAVE_SIMPLIFIED(2)
OCTAVE_SIMPLIFIED(3)
OCTAVE_SIMPLIFIED(4)

FNOISE(1)
FNOISE(2)
FNOISE(3)
FNOISE(4)

INOISE(1)
INOISE(2)
INOISE(3)
INOISE(4)

float smoothSimplexNoise(in uint controlPointDistanceExponent,in uvec2 x){
  if(controlPointDistanceExponent == 0u)return baseIntegerNoise(x);
  uint controlPointDistance = 1u << controlPointDistanceExponent;
  uvec2 smallestControlPoint = x >> controlPointDistanceExponent;
  vec2  delta       = vec2(x&(controlPointDistance-1u)) / vec2(controlPointDistance);
  float result = 0.f;
  uint simplexId = uint(delta.y > delta.x);
  // dx <= dy
  // 0: 1-x
  // 1: x-y
  // 3: y
  // dy > dx
  // 0: 1-y
  // 2: y-x
  // 3: x
  //
  //
  result += baseIntegerNoise((smallestControlPoint+uvec2(0          ,0        )<<controlPointDistanceExponent)&(0xffffffff>>controlPointDistanceExponent)) * (1-delta.y*simplexId-delta.x*(1-simplexId));
  result += baseIntegerNoise((smallestControlPoint+uvec2(1          ,1        )<<controlPointDistanceExponent)&(0xffffffff>>controlPointDistanceExponent)) * (delta.x*simplexId + delta.y*(1-simplexId));
  result += baseIntegerNoise((smallestControlPoint+uvec2(1-simplexId,simplexId)<<controlPointDistanceExponent)&(0xffffffff>>controlPointDistanceExponent)) * abs(delta.y-delta.x);//*(-1+2*simplexId);
  return result;
}

float simplexNoise(in uvec2 x,in uint M,in uint N,float p){
  float ret = 0.f;
  float sum = 0.f;
  for(uint k = 0u; k <= N; ++k){
    sum *= p;
    sum += 1.f;
    ret *= p;
    ret += smoothSimplexNoise(M-k,x);
  }
  return ret/sum;
}



).";
}

std::string ge::gl::getGradientSource(){
  return R".(
#define BEGINGRADIENT(name)\
vec4 name(float t){        \
  t=clamp(t,0.f,1.f);      \
  const vec4 colors[]={

#define ENDGRADIENT                        \
  };                                       \
  t *= colors.length();                    \
  uint i = uint(floor(t));                 \
  uint j = i + 1u;                         \
  if(j >= colors.length()){                \
    i = colors.length() - 1u;              \
    j = i;                                 \
  }                                        \
  return mix(colors[i],colors[j],fract(t));\
}
).";
}
