#include"SintornTiles.h"
#include<cassert>
#include<algorithm>

size_t divRoundUp(size_t X,size_t Y){
  return(X/Y)+(X%Y==0?0:1);
}

size_t divRoundDown(size_t X,size_t Y){
  return(X/Y);
}

class TileDivisibility{
  public:
    std::vector<glm::uvec2>divisibility;
    size_t idle = 0;//number of idle threads
    size_t squareness = 0;//number is smaller if tiles are closer to squares
    void computeSquareness(){
      assert(this!=nullptr);
      this->squareness = 0;
      glm::uvec2 curSize = glm::uvec2(1u,1u);
      for(auto ii=this->divisibility.rbegin();ii!=this->divisibility.rend();ii++){
        curSize*=*ii;
        this->squareness*=2;
        if(curSize.x<curSize.y)this->squareness+=curSize.y/curSize.x;
        else this->squareness+=curSize.x/curSize.y;
      }
    }
    void computeIdle(glm::uvec2 const&windowSize){
      size_t branchingFactor = divisibility.at(0).x*divisibility.at(0).y;
      std::vector<glm::uvec2>tileSize;
      for(auto const&x:this->divisibility){
        (void)x;
        tileSize.push_back(glm::uvec2(1u,1u));
      }
      for(size_t k=1;k<this->divisibility.size();++k)
        for(size_t l=0;l<k;++l)
          tileSize[l]*=divisibility[k];

      this->idle=0;

      for(size_t l=0;l<divisibility.size();++l){
        glm::uvec2 prevTileSize;
        if(l>0)prevTileSize = tileSize[l-1];
        else prevTileSize = windowSize;

        this->idle+=divRoundUp(windowSize[0],prevTileSize[0])*divRoundUp(windowSize[1],prevTileSize[1])*branchingFactor-
          divRoundUp(windowSize[0],tileSize[l].x)*divRoundUp(windowSize[1],tileSize[l].y);
      }
    }
    bool operator<(TileDivisibility const&other)const{
      assert(this!=nullptr);
      assert(this->divisibility.size()==other.divisibility.size());
      if(this->idle<other.idle)return true;
      if(this->idle>other.idle)return false;
      return this->squareness<other.squareness;
    }
};

/**
 * @brief This function finds out possible choices of size of tile
 *
 * @param Choices possible choices, size is NumChoices*2
 * @param WarpSize size of warp (NVIDIA usually 32) (AMD ussually 64)
 */
void tileSizeChoises(
    std::vector<glm::uvec2>&choices,
    size_t warpSize){
  for(size_t x=1;x<=warpSize;++x)//loop over all choices
    if((warpSize%x)==0)//is this choice of x possible?
      choices.push_back(glm::uvec2(x,warpSize/x));
}

size_t computeNofLevels(glm::uvec2 const&windowSize,size_t wgs){
  return (size_t)glm::ceil(glm::log(windowSize[0]*windowSize[1])/glm::log(wgs));
}


void generateSolutions(std::vector<TileDivisibility>&solutions,glm::uvec2 const&windowSize,size_t wgs){
  std::vector<glm::uvec2>choices;
  tileSizeChoises(choices,wgs);
  size_t nofLevels = computeNofLevels(windowSize,wgs);
  size_t II=0;//index into index
  std::vector<size_t>index;
  index.resize(nofLevels,0);

  size_t index1D=0;//1D version of index

  do{//loop over all solutions
    glm::uvec2 size = glm::uvec2(1u,1u);
    for(size_t l=0;l<nofLevels;++l)//loop over levels
      size*=choices[index[l]];

    if(size.x>=windowSize.x && size.y>=windowSize.y){
      solutions.push_back(TileDivisibility());
      for(size_t i=0;i<nofLevels;++i)
        solutions.back().divisibility.push_back(choices[index[i]]);
      solutions.back().computeIdle(windowSize);
      solutions.back().computeSquareness();
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

void chooseTileSizes(std::vector<glm::uvec2>&tileDivisibility,glm::uvec2 const&windowSize,size_t wgs){
  std::vector<TileDivisibility>solutions;
  generateSolutions(solutions,windowSize,wgs);
  std::sort(solutions.begin(),solutions.end());
  for(auto const&x:solutions.front().divisibility)
    tileDivisibility.push_back(x);
}


