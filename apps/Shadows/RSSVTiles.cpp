#include"RSSVTiles.h"
#include<algorithm>
#include<geCore/Dtemplates.h>

size_t rssvGetNofLevels(
    glm::uvec2 const&windowSize    ,
    size_t     const&threadsPerTile){
  auto const widthExponent = log2RoundUp(windowSize.x);
  auto const heightExpornt = log2RoundUp(windowSize.y);
  return divRoundUp<size_t>(widthExponent + heightExpornt,threadsPerTile);
}

/*
std::vector<glm::uvec2>rssvGetLevelDivisibility(
    glm::uvec2 const&windowSize    ,
    size_t     const&threadsPerTile){
  size_t const nofLevels = rssvGetNofLevels(windowSize,threadsPerTile);
  auto const threadsExponent = log2RoundUp(threadsPerTile);
  std::vector<glm::uvec2>result;
  result.resize(nofLevels);

  size_t const threadsExponentPart[2] = {
                      log2RoundUp<size_t>(threadsExponent,2lu),
    threadsExponent - log2RoundUp<size_t>(threadsExponent,2lu),
  };


  return result;
}
*/

class RSSVTilesSolution{
  public:
    std::vector<glm::uvec2>levels;
    size_t idle = 0;
    size_t squareness = 0;
    void computeSquareness(){
      assert(this!=nullptr);
      size_t wgs = this->levels.front().x*this->levels.front().y;
      auto ii=this->levels.rbegin();
      glm::uvec2 curSize = *ii;
      this->squareness=wgs/curSize.x;
      ii++;
      curSize = curSize**ii-glm::uvec2(ii->x,0);
      this->squareness*=2;
      if(curSize.x<curSize.y)this->squareness+=curSize.y/curSize.x;
      else this->squareness+=curSize.x/curSize.y;
      ii++;
      for(;ii!=this->levels.rend();ii++){
        curSize*=*ii;
        this->squareness*=2;
        if(curSize.x<curSize.y)this->squareness+=curSize.y/curSize.x;
        else this->squareness+=curSize.x/curSize.y;
      }
    }
    void computeIdle(glm::uvec2 const&windowSize){
      assert(this!=nullptr);
      this->idle = 0;
      glm::uvec2 prevSize = windowSize;
      int i=int(this->levels.size()-1);
      this->idle += 
        ge::core::divRoundUp(prevSize.x,this->levels.at(i).x-1)*(this->levels.at(i).x-1)*
        ge::core::divRoundUp(prevSize.y,this->levels.at(i).y  )*(this->levels.at(i).y  )-
        prevSize.x*prevSize.y;
      prevSize.x = uint32_t(ge::core::divRoundUp(prevSize.x,this->levels.at(i).x-1));
      prevSize.y = uint32_t(ge::core::divRoundUp(prevSize.y,this->levels.at(i).y  ));
      i--;
      for(;i>=0;--i){
        this->idle += 
          ge::core::divRoundUp(prevSize.x,this->levels.at(i).x)*(this->levels.at(i).x)*
          ge::core::divRoundUp(prevSize.y,this->levels.at(i).y)*(this->levels.at(i).y)-
          prevSize.x*prevSize.y;
        prevSize.x = uint32_t(ge::core::divRoundUp(prevSize.x,this->levels.at(i).x));
        prevSize.y = uint32_t(ge::core::divRoundUp(prevSize.y,this->levels.at(i).y));
      }
    }
    glm::uvec2 getSize()const{
      assert(this!=nullptr);
      if(this->levels.size()==0)return glm::uvec2(0);
      auto ii=this->levels.rbegin();
      glm::uvec2 curSize = *ii;
      ii++;
      bool joiningLevelHapped = false;
      for(;ii!=this->levels.rend();ii++){
        if(joiningLevelHapped){
          curSize*=*ii;
        }else{
          if(ii->x==1){
            curSize*=*ii;
          }else{
            curSize = curSize**ii-glm::uvec2(ii->x,0);
            joiningLevelHapped = true;
          }
        }
      }
      return curSize;
    }
    bool operator<(RSSVTilesSolution const&other)const{
      assert(this!=nullptr);
      if(this->levels.size()<other.levels.size())return true;
      if(this->levels.size()>other.levels.size())return false;
      if(this->levels.back().x>other.levels.back().x)return true;
      if(this->levels.back().x<other.levels.back().x)return false;
      if(this->idle<other.idle)return true;
      if(this->idle>other.idle)return false;
      return this->squareness<other.squareness;
    }
};

void rssvTileSizeChoises(
    std::vector<glm::uvec2>&choices,
    size_t threadsPerTile){
  for(size_t x=1;x<=threadsPerTile;++x)//loop over all choices
    if((threadsPerTile%x)==0)//is this choice of x possible?
      choices.push_back(glm::uvec2(x,threadsPerTile/x));
}

size_t rssvComputeNofLevels(glm::uvec2 const&windowSize,size_t threadsPerTile){
  return (size_t)glm::ceil(glm::log(windowSize[0]*windowSize[1])/glm::log(threadsPerTile))+1;
}

void rssvGenerateSolutions(
    std::vector<RSSVTilesSolution>&solutions,
    glm::uvec2 const&windowSize,
    size_t threadsPerTile){
  std::vector<glm::uvec2>choices;
  rssvTileSizeChoises(choices,threadsPerTile);
  size_t nofLevels = rssvComputeNofLevels(windowSize,threadsPerTile);
  size_t II=0;//index into index
  std::vector<size_t>index;
  index.resize(nofLevels,0);

  size_t index1D=0;//1D version of index
  do{//loop over all solutions
    RSSVTilesSolution sol;
    for(size_t i=0;i<nofLevels;++i){
      if( sol.getSize().x>=windowSize.x &&
          sol.getSize().y>=windowSize.y)break;
      sol.levels.push_back(choices[index[i]]);
    }
    if(sol.levels.back().x>1){
      sol.computeIdle(windowSize);
      sol.computeSquareness();
      if( sol.getSize().x>=windowSize.x &&
          sol.getSize().y>=windowSize.y)
        solutions.push_back(sol);
    }
    ++index1D;//increment 1D version of index
    //increment index to solutions
    II=0;
    do{//loop over levels
      ++index[II];//increment index in II level
      if(index[II]>=choices.size()){//index at II level overflows
        index[II]=0;//clear index in II level
        ++II;//increment level
      }else break;//we are done incrementing
    }while(II<nofLevels);
  }while(II<nofLevels);
}

void rssvChooseTileSizes(
    std::vector<glm::uvec2>&tileDivisibility,
    glm::uvec2 const&windowSize,
    size_t threadsPerTile){
  std::vector<RSSVTilesSolution>solutions;
  rssvGenerateSolutions(solutions,windowSize,threadsPerTile);
  std::sort(solutions.begin(),solutions.end());
  for(auto const&x:solutions.front().levels)
    tileDivisibility.push_back(x);
}
