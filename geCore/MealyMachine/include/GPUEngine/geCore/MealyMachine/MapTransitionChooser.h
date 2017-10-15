#pragma once

#include<GPUEngine/geCore/MealyMachine/TransitionChooser.h>
#include<map>
#include<cstring>

namespace ge{
  namespace core{
    template<size_t N>
      class MapTransitionChooser: public TransitionChooser{
        public:
          MapTransitionChooser():TransitionChooser(N){}
          virtual ~MapTransitionChooser()override{
            for(auto&x:this->_keys)
              delete[]x;
          }
          virtual MealyMachine::TransitionIndex getTransition(
              MealyMachine::TransitionSymbol const&data)const override{
            auto ii=this->_translator.find(data);
            if(ii==this->_translator.end())return MealyMachine::nonexistingTransition;
            return ii->second;
            return 0;
          }
          virtual bool addTransition(
              MealyMachine::TransitionSymbol const&data)override{
            auto key = new MealyMachine::BasicUnit[N];
            std::memcpy(key,data,N*sizeof(MealyMachine::BasicUnit));
            this->_keys.push_back(key);

            auto id = this->_translator.size();
            this->_translator[(MealyMachine::BasicUnit const*)this->_keys.back()] = id;
            return true;
          }
          virtual MealyMachine::TransitionSymbol const&getSymbol(
              MealyMachine::TransitionIndex const&i)const override{
            return this->_keys.at(i);
          }
        protected:
          struct Comparer{
            bool operator()(
                MealyMachine::BasicUnit const*const&a,
                MealyMachine::BasicUnit const*const&b)const{
              for(size_t i=0;i<N;++i){
                if(a[i]<b[i])return true;
                if(a[i]>b[i])return false;
              }
              return false;
            }
          };
          std::vector<MealyMachine::TransitionSymbol>_keys;
          std::map<
            MealyMachine::BasicUnit const*,
            MealyMachine::TransitionIndex,Comparer>_translator;
      };
  }
}

