#include"RSSVTiles.h"


class RSSVLevel{
  public:
    RSSVLevel(
        size_t           l,
        glm::uvec2 const&d,
        glm::uvec2 const&s):level(l),divisibility(d),size(s){}
    size_t     level       ;//level number: 0 - the topmost level
    glm::uvec2 divisibility;//number of element that are grouped together forming tile - one element in higher level
    glm::uvec2 size        ;//number of elements in this level
    glm::uvec2 overlap     ;//number of elements that are shared between two neighbor elements
};

/*
class RSSVTilesSolution{
  public:
    std::vector<RSSVLevel>levels;
    size_t idle = 0;
    size_t squareness = 0;
    void computeSquareness(){
      assert(this!=nullptr);
      size_t wgs = this->divisibility.front().x*this->divisibility.front().y;
      this->squareness = 0;
      glm::uvec2 curSize = glm::uvec2(1u,1u);
      auto ii=this->divisibility.rbegin();
      curSize*=*ii;
      this->squareness*=2;
      this->squareness+=wgs/curSize.x;
      ii++;
      for(;ii!=this->divisibility.rend();ii++){
        curSize*=*ii;
        this->squareness*=2;
        if(curSize.x<curSize.y)this->squareness+=curSize.y/curSize.x;
        else this->squareness+=curSize.x/curSize.y;
      }
    }
};
*/
/*
class RSSVTileDivisibility{
  public:
    std::vector<glm::uvec2>divisibility;
    size_t idle = 0;//number of idle threads
    size_t squareness = 0;//number is smaller if tiles are closer to squares
    void computeSquareness(){
      assert(this!=nullptr);
      size_t wgs = this->divisibility.front().x*this->divisibility.front().y;
      this->squareness = 0;
      glm::uvec2 curSize = glm::uvec2(1u,1u);
      auto ii=this->divisibility.rbegin();
      curSize*=*ii;
      this->squareness*=2;
      this->squareness+=wgs/curSize.x;
      ii++;
      for(;ii!=this->divisibility.rend();ii++){
        curSize*=*ii;
        this->squareness*=2;
        if(curSize.x<curSize.y)this->squareness+=curSize.y/curSize.x;
        else this->squareness+=curSize.x/curSize.y;
      }
    }
    void computeIdle(glm::uvec2 const&windowSize){
      size_t branchingFactor = divisibility.at(0).x*divisibility.at(0).y;
      std::vector<glm::uvec2>tileSize;
      tileSize.resize(this->divisibility.size(),glm::uvec2(1u,1u));
      for(size_t k=1;k<this->divisibility.size();++k)
        for(size_t l=0;l<k;++l)
          tileSize[l]*=divisibility[k];

      this->idle=0;

      for(size_t l=0;l<divisibility.size();++l){
        glm::uvec2 prevTileSize;
        if(l>0)prevTileSize = tileSize[l-1];
        else prevTileSize = windowSize;

        this->idle+=ge::core::divRoundUp(windowSize[0],prevTileSize[0])*ge::core::divRoundUp(windowSize[1],prevTileSize[1])*branchingFactor-
          ge::core::divRoundUp(windowSize[0],tileSize[l].x)*ge::core::divRoundUp(windowSize[1],tileSize[l].y);
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



void rssvChooseTileSizes(
    std::vector<glm::uvec2>&tileDivisibility,
    glm::uvec2 const&windowSize,
    size_t wgs){

}
*/
