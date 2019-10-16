#include<geGL/GLSLNoise.h>

std::string ge::gl::getNoiseSource(){
  return R".(
#line 5
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

//#define VECXI(x,m,i) JOIN(x,JOIN(VECI,m(i)))
//#define VECI1(i) 
//#define VECI2(i) [i]
//#define VECI3(i) [i]
//#define VECI4(i) [i]

uint  getElem(uint  x,uint i){return x   ;}
uint  getElem(uvec2 x,uint i){return x[i];}
uint  getElem(uvec3 x,uint i){return x[i];}
uint  getElem(uvec4 x,uint i){return x[i];}
float getElem(float x,uint i){return x   ;}
float getElem(vec2  x,uint i){return x[i];}
float getElem(vec3  x,uint i){return x[i];}
float getElem(vec4  x,uint i){return x[i];}
#define VECXI(x,m,i) getElem(x,i)

float convert(uint  x){return float(float(x  )                                 );}
vec2  convert(uvec2 x){return vec2 (float(x.x),float(x.y)                      );}
vec3  convert(uvec3 x){return vec3 (float(x.x),float(x.y),float(x.z)           );}
vec4  convert(uvec4 x){return vec4 (float(x.x),float(x.y),float(x.z),float(x.w));}



const uint UINT_0       = 0u         ;
const uint UINT_1       = 1u         ;
const uint UINT_2       = 2u         ;
const uint UINT_MAXDIV2 = 0x7fffffffu;
const uint UINT_MAX     = 0xffffffffu;

uint poly(in uint x,in uint c){
  //return x;
  //return x*(x+c);
  return x*(x*(x+c)+c);
  //return x*(x*(x*(x+c)+c)+c);
  //return x*(x*(x*(x*(x+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c)+c);
  //return x*(x*(x*(x*(x*(x*(x*(x+c)+c)+c)+c)+c)+c)+c);
}

#define BASE(DIMENSION)                                     \
float baseIntegerNoise(in JOIN(UVEC,DIMENSION) x){          \
  uint last = 10u;                                          \
  for(uint i = 0u; i < uint(DIMENSION); ++i)                \
    last = poly( VECXI(x,DIMENSION,i) + (20024u << i),last);\
  return -1. + float(last)/float(UINT_MAXDIV2);             \
}                                                           \
uint baseIntegerNoiseU(in JOIN(UVEC,DIMENSION) x){          \
  uint last = 10u;                                          \
  for(uint i = 0u; i < uint(DIMENSION); ++i)                \
    last = poly( VECXI(x,DIMENSION,i) + (20024u << i),last);\
  return last;                                              \
}


#define SMOOTH(DIMENSION)                                                          \
float smoothNoise(in uint d,in JOIN(UVEC,DIMENSION) x){                            \
  if(d == 0u)return baseIntegerNoise(x);                                           \
  uint dd = 1u << d;                                                               \
  JOIN(UVEC,DIMENSION) xx = x >> d;                                                \
  JOIN(VEC,DIMENSION) t = convert(x&uint(dd-1u)) / convert(dd);                    \
  float ret = 0.f;                                                                 \
  for(uint i = 0u; i < (1u << DIMENSION); ++i){                                    \
    float coef = 1.f;                                                              \
    JOIN(UVEC,DIMENSION) o = JOIN(UVEC,DIMENSION)(0);                              \
    for(uint j = 0u; j < uint(DIMENSION); ++j){                                    \
      VECXI(o,DIMENSION,j) = (i >> j) & 1u;                                        \
      coef *= smoothStep(0.f,1.f,float(1u - (uint(i >> j)&1u))*(1.f - 2.f*VECXI(t,DIMENSION,j)) + VECXI(t,DIMENSION,j));\
    }                                                                              \
    ret += baseIntegerNoise(xx + o) * coef;                   \
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

//BASE(1)
//BASE(2)
//BASE(3)
//BASE(4)

//SMOOTH(1)
//SMOOTH(2)
//SMOOTH(3)
//SMOOTH(4)

uint baseIntegerNoiseU(in uint x){          
  uint last = 10u;                                          
  last = poly( x + (20024u    ),last);
  return last;                                              
}
float baseIntegerNoise(in uint x){          
  return -1. + float(baseIntegerNoiseU(x))/float(UINT_MAXDIV2);             
}                                                           

uint baseIntegerNoiseU(in uvec2 x){          
  uint last = 103232u;                                          
  last = poly( x[0] + (20024u    ),last);
  last = poly( x[1] + (2330024u<<1u),last);
  return last;                                              
}
float baseIntegerNoise(in uvec2 x){          
  return -1. + float(baseIntegerNoiseU(x))/float(UINT_MAXDIV2);             
}                                                           

uint baseIntegerNoiseU(in uvec3 x){          
  uint last = 10u;                                          
  last = poly( x[0] + (20024u    ),last);
  last = poly( x[1] + (20024u<<1u),last);
  last = poly( x[2] + (20024u<<2u),last);
  return last;                                              
}
float baseIntegerNoise(in uvec3 x){          
  return -1. + float(baseIntegerNoiseU(x))/float(UINT_MAXDIV2);             
}                                                           

uint baseIntegerNoiseU(in uvec4 x){          
  uint last = 10u;                                          
  last = poly( x[0] + (20024u    ),last);
  last = poly( x[1] + (20024u<<1u),last);
  last = poly( x[2] + (20024u<<2u),last);
  last = poly( x[3] + (20024u<<3u),last);
  return last;                                              
}
float baseIntegerNoise(in uvec4 x){          
  return -1. + float(baseIntegerNoiseU(x))/float(UINT_MAXDIV2);             
}                                                           

float smoothNoise(in uint d,in uint x){
  if(d == 0u)return baseIntegerNoise(x);
  uint dd = 1u << d;
  uint xx = x >> d;
  float t = float(x&uint(dd-1u)) / float(dd);
  t = smoothstep(0,1,t);
  float ret = 0.f;
  ret += baseIntegerNoise(xx+0u) * (1.f-t);
  ret += baseIntegerNoise(xx+1u) * (    t);
  return ret;
}

float smoothNoise(in uint d,in uvec2 x){
  if(d == 0u)return baseIntegerNoise(x);
  uint dd = 1u << d;
  uvec2 xx = x >> d;
  vec2 t = vec2(x&uvec2(dd-1u)) / vec2(dd);
  t.x = smoothstep(0,1,t.x);
  t.y = smoothstep(0,1,t.y);
  float ret = 0.f;
  ret += baseIntegerNoise(xx+uvec2(0u,0u)) * (1.f-t[0u])*(1.f-t[1u]);
  ret += baseIntegerNoise(xx+uvec2(1u,0u)) * (    t[0u])*(1.f-t[1u]);
  ret += baseIntegerNoise(xx+uvec2(0u,1u)) * (1.f-t[0u])*(    t[1u]);
  ret += baseIntegerNoise(xx+uvec2(1u,1u)) * (    t[0u])*(    t[1u]);
  return ret;
}

float smoothNoise(in uint d,in uvec3 x){
  if(d == 0u)return baseIntegerNoise(x);
  uint dd = 1u << d;
  uvec3 xx = x >> d;
  vec3 t = vec3(x&uvec3(dd-1u)) / vec3(dd);
  t.x = smoothstep(0,1,t.x);
  t.y = smoothstep(0,1,t.y);
  t.z = smoothstep(0,1,t.z);
  float ret = 0.f;
  ret += baseIntegerNoise(xx+uvec3(0u,0u,0u)) * (1.f-t[0u])*(1.f-t[1u])*(1.f-t[2u]);
  ret += baseIntegerNoise(xx+uvec3(1u,0u,0u)) * (    t[0u])*(1.f-t[1u])*(1.f-t[2u]);
  ret += baseIntegerNoise(xx+uvec3(0u,1u,0u)) * (1.f-t[0u])*(    t[1u])*(1.f-t[2u]);
  ret += baseIntegerNoise(xx+uvec3(1u,1u,0u)) * (    t[0u])*(    t[1u])*(1.f-t[2u]);
  ret += baseIntegerNoise(xx+uvec3(0u,0u,1u)) * (1.f-t[0u])*(1.f-t[1u])*(    t[2u]);
  ret += baseIntegerNoise(xx+uvec3(1u,0u,1u)) * (    t[0u])*(1.f-t[1u])*(    t[2u]);
  ret += baseIntegerNoise(xx+uvec3(0u,1u,1u)) * (1.f-t[0u])*(    t[1u])*(    t[2u]);
  ret += baseIntegerNoise(xx+uvec3(1u,1u,1u)) * (    t[0u])*(    t[1u])*(    t[2u]);
  return ret;
}

float smoothNoise(in uint d,in uvec4 x){
  if(d == 0u)return baseIntegerNoise(x);
  uint dd = 1u << d;
  uvec4 xx = x >> d;
  vec4 t = vec4(x&uvec4(dd-1u)) / vec4(dd);
  t.x = smoothstep(0,1,t.x);
  t.y = smoothstep(0,1,t.y);
  t.z = smoothstep(0,1,t.z);
  t.w = smoothstep(0,1,t.w);
  float ret = 0.f;
  ret += baseIntegerNoise(xx+uvec4(0u,0u,0u,0u)) * (1.f-t[0u])*(1.f-t[1u])*(1.f-t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,0u,0u,0u)) * (    t[0u])*(1.f-t[1u])*(1.f-t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,1u,0u,0u)) * (1.f-t[0u])*(    t[1u])*(1.f-t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,1u,0u,0u)) * (    t[0u])*(    t[1u])*(1.f-t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,0u,1u,0u)) * (1.f-t[0u])*(1.f-t[1u])*(    t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,0u,1u,0u)) * (    t[0u])*(1.f-t[1u])*(    t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,1u,1u,0u)) * (1.f-t[0u])*(    t[1u])*(    t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,1u,1u,0u)) * (    t[0u])*(    t[1u])*(    t[2u])*(1.f-t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,0u,0u,1u)) * (1.f-t[0u])*(1.f-t[1u])*(1.f-t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,0u,0u,1u)) * (    t[0u])*(1.f-t[1u])*(1.f-t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,1u,0u,1u)) * (1.f-t[0u])*(    t[1u])*(1.f-t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,1u,0u,1u)) * (    t[0u])*(    t[1u])*(1.f-t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,0u,1u,1u)) * (1.f-t[0u])*(1.f-t[1u])*(    t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,0u,1u,1u)) * (    t[0u])*(1.f-t[1u])*(    t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(0u,1u,1u,1u)) * (1.f-t[0u])*(    t[1u])*(    t[2u])*(    t[3u]);
  ret += baseIntegerNoise(xx+uvec4(1u,1u,1u,1u)) * (    t[0u])*(    t[1u])*(    t[2u])*(    t[3u]);
  return ret;
}

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
  vec2  delta       = vec2(x&uint(controlPointDistance-1u)) / vec2(controlPointDistance);
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
  result += baseIntegerNoise((smallestControlPoint+uvec2(0          ,0        )<<controlPointDistanceExponent)&uint(0xffffffff>>controlPointDistanceExponent)) * (1-delta.y*simplexId-delta.x*(1-simplexId));
  result += baseIntegerNoise((smallestControlPoint+uvec2(1          ,1        )<<controlPointDistanceExponent)&uint(0xffffffff>>controlPointDistanceExponent)) * (delta.x*simplexId + delta.y*(1-simplexId));
  result += baseIntegerNoise((smallestControlPoint+uvec2(1-simplexId,simplexId)<<controlPointDistanceExponent)&uint(0xffffffff>>controlPointDistanceExponent)) * abs(delta.y-delta.x);//*(-1+2*simplexId);
  return result;
}

//float smoothSimplexNoise(in uint controlPointDistanceExponent,in uvec3 x){
//  if(controlPointDistanceExponent == 0u)return baseIntegerNoise(x);
//  uint controlPointDistance = 1u << controlPointDistanceExponent;
//  uvec3 smallestControlPoint = x >> controlPointDistanceExponent;
//  vec3  delta       = vec3(x&(controlPointDistance-1u)) / vec3(controlPointDistance);
//  float result = 0.f;
//  uint simplexId = uint(delta.y > delta.x);
//  // dx <= dy
//  // dx <= dz
//  // dy <= dz
//  //
//  //
//  //
//
//}

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

uint umix(uint a,uint b,uint delta,uint dd,uint d){
  return (a>>d)*(dd-delta) + (b>>d)*delta;
}

uint smoothNoiseU(in uint d,in uvec2 x){
  if(d == 0u)return baseIntegerNoiseU(x);

  uint dd = 1u << d;
  uvec2 xx = x >> d;
  uvec2  delta       = uvec2(x&uint(dd-1u));
  uint result0 = 0u;
  uint result1 = 0u;

  result0 = umix(
      baseIntegerNoiseU(xx+uvec2(0,0)<<d),
      baseIntegerNoiseU(xx+uvec2(1,0)<<d),
      delta.x,dd,d);
  result1 = umix(
      baseIntegerNoiseU(xx+uvec2(0,1)<<d),
      baseIntegerNoiseU(xx+uvec2(1,1)<<d),
      delta.x,dd,d);

  return umix(
      result0,
      result1,
      delta.y,dd,d);
}

float noiseU(in uvec2 x){
  uint res = 0;
  uint m = 8;


  for(uint k=0;k<m;++k)
    res += smoothNoiseU(k,x)>>(m-k) ;

  res = 0;
  res += uint((smoothNoiseU(7,x)&0x80000000u)>0)<<31;
  res += uint((smoothNoiseU(6,x)&0xB0000000u)>0)<<30;
  res += uint((smoothNoiseU(5,x)&0xE0000000u)>0)<<29;
  res += uint((smoothNoiseU(4,x)&0xF0000000u)>0)<<28;
  res += uint((smoothNoiseU(3,x)&0xF8000000u)>0)<<27;
  res += uint((smoothNoiseU(2,x)&0xFB000000u)>0)<<26;
  res += uint((smoothNoiseU(1,x)&0xFE000000u)>0)<<25;
  res += uint((smoothNoiseU(0,x)&0xFF000000u)>0)<<24;

  res = (smoothNoiseU(8,x)>>1)+(smoothNoiseU(7,x)>>2)+(smoothNoiseU(6,x)>>3)+(smoothNoiseU(5,x)>>4)+(smoothNoiseU(4,x)>>5)+(smoothNoiseU(3,x)>>6)+(smoothNoiseU(2,x)>>7)+(smoothNoiseU(1,x)>>7);
  res = smoothNoiseU(6,x);
  //return noise(x,6,0,2.f);

  //res = 0;
  //res ^= smoothNoiseU(7,x)>>0;
  //res ^= smoothNoiseU(6,x)>>1;
  //res ^= smoothNoiseU(5,x)>>2;
  //res ^= smoothNoiseU(4,x)>>3;
  //res ^= smoothNoiseU(3,x)>>4;
  //res ^= smoothNoiseU(2,x)>>5;
  //res ^= smoothNoiseU(1,x)>>6;
  //res ^= smoothNoiseU(0,x)>>7;

  //res = 
  //  umix(
  //    umix(
  //      umix(
  //        umix(
  //          umix(
  //            umix(
  //              smoothNoiseU(7,x),
  //              smoothNoiseU(6,x),22,32,5),
  //            smoothNoiseU(5,x),18,32,5),
  //          smoothNoiseU(4,x),14,32,5),
  //        smoothNoiseU(3,x),10,32,5),
  //      smoothNoiseU(2,x),6,32,5),
  //    smoothNoiseU(1,x),2,32,5);

  //res += smoothNoiseU(2,x)&0x00ff0000;
  //res += smoothNoiseU(1,x)&0x0000ff00;
  //res += smoothNoiseU(2,x)&0x000000ff;

  return -1.f + float(res)*(1.f/float(0x7fffffffu));

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
