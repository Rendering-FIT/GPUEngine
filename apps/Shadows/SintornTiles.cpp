#include"SintornTiles.h"
#include<cassert>

#if 0

class TileDivisibility{
  public:
    std::vector<glm::uvec2>divisibility;
    uint32_t idle = 0;//number of idle threads
    uint32_t squareness = 0;//number is smaller if tiles are closer to squares
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
    void computeIdle(){

    }
    bool operator<(TileDivisibility const&other){
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
 *
 * @return returns number of possible choices - NumChoices
 */
uint32_t tileSizeChoises(
    std::vector<glm::uvec2>&choices,
    uint32_t WarpSize){
  for(uint32_t x=1;x<=WarpSize;++x)//loop over all choices
    if((WarpSize%x)==0){//is this choice of x possible?
      choices.push_back(glm::uvec2(x,WarpSize/x));
    }
  return choices.size();
}

uint32_t divRoundUp(uint32_t X,uint32_t Y){
  return(X/Y)+(X%Y==0?0:1);
}

uint32_t divRoundDown(uint32_t X,uint32_t Y){
  return(X/Y);
}

uint32_t computeIdleInvocation(
    uint32_t*Active,
    uint32_t NumLevels,
    uint32_t*TileChoices,
    uint32_t*SolutionIndex,
    uint32_t*WindowSize){
  uint32_t*TileSize=new uint32_t[NumLevels*2];
  for(int l=NumLevels-1;l>=0;--l){
    TileSize[l*2+0]=1;//TileChoices[SolutionIndex[NumLevels-1]*2+0];
    TileSize[l*2+1]=1;//TileChoices[SolutionIndex[NumLevels-1]*2+1];
  }
  for(uint32_t k=1;k<NumLevels;++k)
    for(uint32_t l=0;l<k;++l){
      TileSize[l*2+0]*=TileChoices[SolutionIndex[k]*2+0];
      TileSize[l*2+1]*=TileChoices[SolutionIndex[k]*2+1];
    }

  uint32_t NumInvocations=0;
  uint32_t BrachingFactor=TileChoices[SolutionIndex[0]*2+0]*TileChoices[SolutionIndex[0]*2+1];
  //BF+BF*BF+BF*BF*BF+BF*BF*BF*BF;
  for(uint32_t l=0;l<NumLevels;++l){
    NumInvocations+=1;
    NumInvocations*=BrachingFactor;
  }
  uint32_t Idle=0;
  *Active=0;

  for(uint32_t l=0;l<NumLevels;++l){
    uint32_t PrevTileSize[2];
    if(l>0){
      PrevTileSize[0]=TileSize[(l-1)*2+0];
      PrevTileSize[1]=TileSize[(l-1)*2+1];
    }else{
      PrevTileSize[0]=WindowSize[0];
      PrevTileSize[1]=WindowSize[1];
    }
    /*
       std::cerr<<"  G:"<<DivRoundUp(WindowSize[0],PrevTileSize[0])*DivRoundUp(WindowSize[1],PrevTileSize[1])*BrachingFactor-
       DivRoundUp(WindowSize[0],TileSize[l*2+0])*DivRoundUp(WindowSize[1],TileSize[l*2+1])<<" "<<
       DivRoundUp(WindowSize[0],PrevTileSize[0])<<" "<<DivRoundUp(WindowSize[1],PrevTileSize[1])<<" "<<
       DivRoundUp(WindowSize[0],TileSize[l*2+0])<<" "<<DivRoundUp(WindowSize[1],TileSize[l*2+1])
       <<"::: "<<WindowSize[1]<<" -->> "<<TileSize[l*2+1]<<std::endl;
       */
    Idle+=divRoundUp(WindowSize[0],PrevTileSize[0])*divRoundUp(WindowSize[1],PrevTileSize[1])*BrachingFactor-
      divRoundUp(WindowSize[0],TileSize[l*2+0])*divRoundUp(WindowSize[1],TileSize[l*2+1]);

    *Active+=
      (divRoundUp(WindowSize[0],PrevTileSize[0])*divRoundUp(WindowSize[1],PrevTileSize[1])*BrachingFactor-
       divRoundDown(WindowSize[0],PrevTileSize[0])*divRoundDown(WindowSize[1],PrevTileSize[1])*BrachingFactor)
      -(divRoundUp(WindowSize[0],PrevTileSize[0])*divRoundUp(WindowSize[1],PrevTileSize[1])*BrachingFactor-
          divRoundUp(WindowSize[0],TileSize[l*2+0])*divRoundUp(WindowSize[1],TileSize[l*2+1]));

  }

  //for(uint32_t l=0;l<NumLevels;++l)
  //	std::cerr<<" "<<TileSize[l*2+0]<<"x"<<TileSize[l*2+1];
  //std::cerr<<" idle:    "<<Idle<<" active: "<<*Active;
  //std::cerr<<std::endl;
  delete[]TileSize;
  return Idle;
}

uint32_t*SortPtr;

int SortByIdleInvocation(const void*A,const void*B){
  uint32_t*APtr=(uint32_t*)A;
  uint32_t*BPtr=(uint32_t*)B;
  if(SortPtr[*APtr]<SortPtr[*BPtr])return-1;
  else if(SortPtr[*APtr]>SortPtr[*BPtr])return 1;
  return 0;
}


uint32_t chooseTileSizes(
    std::vector<glm::uvec2>&tileSize,
    glm::uvec2 const&windowSize,
    uint32_t wavefrontSize){
  std::vector<glm::uvec2>tileChoices;
  uint32_t NumTileChoices=tileSizeChoises(tileChoices,wavefrontSize);//determine
  uint32_t NumLevels=glm::ceil(glm::log(windowSize[0]*windowSize[1])/glm::log(wavefrontSize));

  uint32_t NumSolutions=glm::pow(NumTileChoices,NumLevels);//total number of sol.

  uint32_t*SolutionIndex=new uint32_t[NumSolutions*NumLevels];//ind. to choices
  uint32_t*SolutionSizeReq=new uint32_t[NumSolutions];//pass size requirement
  uint32_t*SolutionIdleInvocations=new uint32_t[NumSolutions];//num of idle inv.
  uint32_t*SolutionActiveInvocations=new uint32_t[NumSolutions];//active inv.
  uint32_t NumSolutionSizeReq=0;

  uint32_t II=0;//index into index
  uint32_t*Index=new uint32_t[NumLevels];//N-dimensional index
  for(uint32_t i=0;i<NumLevels;++i)Index[i]=0;//cleat index

  uint32_t Index1D=0;//1D version of index

  do{//loop over all solutions
    for(uint32_t l=0;l<NumLevels;++l)//loop over levels
      SolutionIndex[Index1D*NumLevels+l]=Index[l];//write solution index

    //test size requirement
    uint32_t Size[2]={1,1};
    for(uint32_t l=0;l<NumLevels;++l)//loop over levels
      for(int k=0;k<2;++k)//loop over dimension of size
        Size[k]*=TileChoices[Index[l]*2+k];//compute size
    if(Size[0]>=WindowSize[0]&&Size[1]>=WindowSize[1]){//resolution is ok
      uint32_t Active;
      SolutionIdleInvocations[NumSolutionSizeReq]=ComputeIdleInvocation(
          &Active,
          NumLevels,
          TileChoices,
          SolutionIndex+Index1D*NumLevels,
          WindowSize);
      SolutionActiveInvocations[NumSolutionSizeReq]=Active;
      SolutionSizeReq[NumSolutionSizeReq]=Index1D;
      ++NumSolutionSizeReq;
    }

    ++Index1D;//increment 1D version of index
    //increment index to solutions
    II=0;
    do{//loop over levels
      ++Index[II];//increment index in II level
      if(Index[II]>=NumTileChoices){//index at II level overflows
        Index[II]=0;//clear index in II level
        ++II;//increment level
      }else break;//we are done incrementing
    }while(II<NumLevels);
  }while(II<NumLevels);

  //sort solutions by number of idle invocations
  uint32_t*IndexToSolution=new uint32_t	[NumSolutionSizeReq];
  for(uint32_t i=0;i<NumSolutionSizeReq;++i)IndexToSolution[i]=i;
  SortPtr=SolutionIdleInvocations;
  qsort(IndexToSolution,NumSolutionSizeReq,sizeof(uint32_t),SortByIdleInvocation);

  //compute the count of fewest idle solutions
  uint32_t MinIdle=SolutionIdleInvocations[IndexToSolution[0]];
  uint32_t NumFewestIdle=0;
  for(uint32_t i=0;i<NumSolutionSizeReq;++i)
    if(MinIdle!=SolutionIdleInvocations[IndexToSolution[i]])break;
    else NumFewestIdle++;

  uint32_t*FewestIdle=new uint32_t[NumFewestIdle];
  for(uint32_t i=0;i<NumFewestIdle;++i)
    FewestIdle[i]=SolutionSizeReq[IndexToSolution[i]];

  uint32_t*Squareness=new uint32_t[NumFewestIdle];
  for(uint32_t i=0;i<NumFewestIdle;++i){
    Squareness[i]=0;
    uint32_t ActX=1;
    uint32_t ActY=1;
    for(int l=NumLevels-1;l>=0;--l){
      uint32_t SolIndex=SolutionIndex[FewestIdle[i]*NumLevels+l];
      ActX*=TileChoices[SolIndex*2+0];//width of tile
      ActY*=TileChoices[SolIndex*2+1];//height of tile
      Squareness[i]*=2;
      if(ActX<ActY)Squareness[i]+=ActY/ActX;
      else Squareness[i]+=ActX/ActY;//squareness of a level
    }
  }

  uint32_t*IndexToFewestIdle=new uint32_t[NumFewestIdle];
  for(uint32_t i=0;i<NumFewestIdle;++i)
    IndexToFewestIdle[i]=i;
  SortPtr=Squareness;
  qsort(IndexToFewestIdle,NumFewestIdle,sizeof(uint32_t),SortByIdleInvocation);

  for(uint32_t l=0;l<NumLevels;++l){
    uint32_t SolIndex=SolutionIndex[FewestIdle[IndexToFewestIdle[0]]*NumLevels+l];
    (*TileSize)[l*2+0]=TileChoices[SolIndex*2+0];
    (*TileSize)[l*2+1]=TileChoices[SolIndex*2+1];
  }

  delete[]IndexToFewestIdle;
  delete[]Squareness;
  delete[]FewestIdle;
  delete[]SolutionActiveInvocations;
  delete[]SolutionIdleInvocations;
  delete[]IndexToSolution;
  delete[]SolutionSizeReq;
  delete[]Index;
  delete[]SolutionIndex;
  delete[]TileChoices;//free tile size choices
  return NumLevels;//return number of required levels
}

#endif
