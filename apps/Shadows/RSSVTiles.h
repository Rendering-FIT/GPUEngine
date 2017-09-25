#pragma once

#include<vector>
#include<memory>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_access.hpp>

class RSSVTilingImpl;
class RSSVTiling{
  public:
    RSSVTiling(size_t windowWidth,size_t windowHeight,size_t threadsPerTile);
    size_t                 getNofLevels                     ()const;
    glm::uvec2             getWindowSize                    ()const;
    glm::uvec2             getWindowExponent                ()const;
    std::vector<glm::uvec2>getLevelDivisibility             ()const;
    std::vector<glm::uvec2>getLevelDivisibilityIntoFullTiles()const;
    std::vector<glm::uvec2>getFullTileSizeInTiles           ()const;
    std::vector<glm::uvec2>getFullTileSizeInPixels          ()const;
    std::vector<glm::uvec2>getBorderTileSizeInTiles         ()const;
    std::vector<glm::uvec2>getBorderTileSizeInPixels        ()const;
  protected:
    friend class RSSVTilingImpl;
    std::unique_ptr<RSSVTilingImpl>_impl;
};


/**
 * @brief This function finds out the best distribution of tileDivisibilities among tiles
 *
 * @param tileDivisibility output tile divisibilities
 * @param windowSize windows size
 * @param threadsPerTile absolute work-group size = tileDivisibility[i].x*tileDivisibility[i].y
 */
void rssvChooseTileSizes(std::vector<glm::uvec2>&tileDivisibility,glm::uvec2 const&windowSize,size_t threadsPerTile);

size_t rssvGetNofLevels(
    glm::uvec2 const&windowSize    ,
    size_t     const&threadsPerTile);

std::vector<glm::uvec2>rssvGetMaxUpperTileDivisibility(
    glm::uvec2 const&windowSize    ,
    size_t     const&threadsPerTile);

template<typename T>
T setMasterBit(){
  return ~((~static_cast<T>(0))>>1);
}

template<typename T>
T log2RoundUp(T const&v){
  if(v >= setMasterBit<T>())return 0;
  T result = 1;
  T counter = 0;
  while(result < v){
    result <<= 1;
    counter++;
  }
  return counter;
}

template<typename T>
T divRoundUp(T const&dividend,T const&divisor){
  if(dividend%divisor != 0)
    return (dividend/divisor)+1;
  return dividend/divisor;
}
