#include"SintornTiles.h"
#include<cassert>

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
 */
void tileSizeChoises(
    std::vector<glm::uvec2>&choices,
    size_t warpSize){
  for(size_t x=1;x<=warpSize;++x)//loop over all choices
    if((warpSize%x)==0)//is this choice of x possible?
      choices.push_back(glm::uvec2(x,warpSize/x));
}

size_t computeNofLevels(glm::uvec2 const&windowSize,size_t wavefrontSize){
  return glm::ceil(glm::log(windowSize[0]*windowSize[1])/glm::log(wavefrontSize));
}

#if 0

void generateSolutions(std::vector<TileDivisibility>&solutions,glm::uvec2 const&windowSize,size_t wavefrontSize){
  std::vector<glm::uvec2>choices;
  tileSizeChoises(choices,wavefrontSize);
  size_t II=0;//index into index
  std::vector<size_t>index;
  index.resize()
  size_t*Index=new size_t[NumLevels];//N-dimensional index
  for(size_t i=0;i<NumLevels;++i)Index[i]=0;//cleat index

  size_t Index1D=0;//1D version of index

  do{//loop over all solutions
    for(size_t l=0;l<NumLevels;++l)//loop over levels
      SolutionIndex[Index1D*NumLevels+l]=Index[l];//write solution index

    //test size requirement
    size_t Size[2]={1,1};
    for(size_t l=0;l<NumLevels;++l)//loop over levels
      for(int k=0;k<2;++k)//loop over dimension of size
        Size[k]*=TileChoices[Index[l]*2+k];//compute size
    if(Size[0]>=WindowSize[0]&&Size[1]>=WindowSize[1]){//resolution is ok
      size_t Active;
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


}



size_t computeIdleInvocation(
    size_t*Active,
    size_t NumLevels,
    size_t*TileChoices,
    size_t*SolutionIndex,
    size_t*WindowSize){
  size_t*TileSize=new size_t[NumLevels*2];
  for(int l=NumLevels-1;l>=0;--l){
    TileSize[l*2+0]=1;//TileChoices[SolutionIndex[NumLevels-1]*2+0];
    TileSize[l*2+1]=1;//TileChoices[SolutionIndex[NumLevels-1]*2+1];
  }
  for(size_t k=1;k<NumLevels;++k)
    for(size_t l=0;l<k;++l){
      TileSize[l*2+0]*=TileChoices[SolutionIndex[k]*2+0];
      TileSize[l*2+1]*=TileChoices[SolutionIndex[k]*2+1];
    }

  size_t NumInvocations=0;
  size_t BrachingFactor=TileChoices[SolutionIndex[0]*2+0]*TileChoices[SolutionIndex[0]*2+1];
  //BF+BF*BF+BF*BF*BF+BF*BF*BF*BF;
  for(size_t l=0;l<NumLevels;++l){
    NumInvocations+=1;
    NumInvocations*=BrachingFactor;
  }
  size_t Idle=0;
  *Active=0;

  for(size_t l=0;l<NumLevels;++l){
    size_t PrevTileSize[2];
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

  //for(size_t l=0;l<NumLevels;++l)
  //	std::cerr<<" "<<TileSize[l*2+0]<<"x"<<TileSize[l*2+1];
  //std::cerr<<" idle:    "<<Idle<<" active: "<<*Active;
  //std::cerr<<std::endl;
  delete[]TileSize;
  return Idle;
}

size_t*SortPtr;

int SortByIdleInvocation(const void*A,const void*B){
  size_t*APtr=(size_t*)A;
  size_t*BPtr=(size_t*)B;
  if(SortPtr[*APtr]<SortPtr[*BPtr])return-1;
  else if(SortPtr[*APtr]>SortPtr[*BPtr])return 1;
  return 0;
}


size_t chooseTileSizes(
    std::vector<glm::uvec2>&tileSize,
    glm::uvec2 const&windowSize,
    size_t wavefrontSize){
  std::vector<glm::uvec2>tileChoices;
  size_t NumTileChoices=tileSizeChoises(tileChoices,wavefrontSize);//determine
  size_t NumLevels=glm::ceil(glm::log(windowSize[0]*windowSize[1])/glm::log(wavefrontSize));

  size_t NumSolutions=glm::pow(NumTileChoices,NumLevels);//total number of sol.

  size_t*SolutionIndex=new size_t[NumSolutions*NumLevels];//ind. to choices
  size_t*SolutionSizeReq=new size_t[NumSolutions];//pass size requirement
  size_t*SolutionIdleInvocations=new size_t[NumSolutions];//num of idle inv.
  size_t*SolutionActiveInvocations=new size_t[NumSolutions];//active inv.
  size_t NumSolutionSizeReq=0;

  size_t II=0;//index into index
  size_t*Index=new size_t[NumLevels];//N-dimensional index
  for(size_t i=0;i<NumLevels;++i)Index[i]=0;//cleat index

  size_t Index1D=0;//1D version of index

  do{//loop over all solutions
    for(size_t l=0;l<NumLevels;++l)//loop over levels
      SolutionIndex[Index1D*NumLevels+l]=Index[l];//write solution index

    //test size requirement
    size_t Size[2]={1,1};
    for(size_t l=0;l<NumLevels;++l)//loop over levels
      for(int k=0;k<2;++k)//loop over dimension of size
        Size[k]*=TileChoices[Index[l]*2+k];//compute size
    if(Size[0]>=WindowSize[0]&&Size[1]>=WindowSize[1]){//resolution is ok
      size_t Active;
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
  size_t*IndexToSolution=new size_t	[NumSolutionSizeReq];
  for(size_t i=0;i<NumSolutionSizeReq;++i)IndexToSolution[i]=i;
  SortPtr=SolutionIdleInvocations;
  qsort(IndexToSolution,NumSolutionSizeReq,sizeof(size_t),SortByIdleInvocation);

  //compute the count of fewest idle solutions
  size_t MinIdle=SolutionIdleInvocations[IndexToSolution[0]];
  size_t NumFewestIdle=0;
  for(size_t i=0;i<NumSolutionSizeReq;++i)
    if(MinIdle!=SolutionIdleInvocations[IndexToSolution[i]])break;
    else NumFewestIdle++;

  size_t*FewestIdle=new size_t[NumFewestIdle];
  for(size_t i=0;i<NumFewestIdle;++i)
    FewestIdle[i]=SolutionSizeReq[IndexToSolution[i]];

  size_t*Squareness=new size_t[NumFewestIdle];
  for(size_t i=0;i<NumFewestIdle;++i){
    Squareness[i]=0;
    size_t ActX=1;
    size_t ActY=1;
    for(int l=NumLevels-1;l>=0;--l){
      size_t SolIndex=SolutionIndex[FewestIdle[i]*NumLevels+l];
      ActX*=TileChoices[SolIndex*2+0];//width of tile
      ActY*=TileChoices[SolIndex*2+1];//height of tile
      Squareness[i]*=2;
      if(ActX<ActY)Squareness[i]+=ActY/ActX;
      else Squareness[i]+=ActX/ActY;//squareness of a level
    }
  }

  size_t*IndexToFewestIdle=new size_t[NumFewestIdle];
  for(size_t i=0;i<NumFewestIdle;++i)
    IndexToFewestIdle[i]=i;
  SortPtr=Squareness;
  qsort(IndexToFewestIdle,NumFewestIdle,sizeof(size_t),SortByIdleInvocation);

  for(size_t l=0;l<NumLevels;++l){
    size_t SolIndex=SolutionIndex[FewestIdle[IndexToFewestIdle[0]]*NumLevels+l];
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
