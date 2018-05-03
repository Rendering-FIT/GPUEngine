#pragma once

#include<vector>
#include<set>

namespace ge{
  namespace core{
    template<typename TYPE>
      class DisjointSet:public std::vector<std::set<TYPE>>{
        public:
          void makeSet(TYPE const&a){
            if(this->find(a)!=this->end())return;
            this->push_back(std::set<TYPE>(a));
          }
          void add(TYPE const&a,TYPE const&b){
            typename std::vector<std::set<TYPE>>::iterator fa=this->find(a);
            typename std::vector<std::set<TYPE>>::iterator fb=this->find(b);
            if(fa==fb){
              if(fa==this->end()){
                std::set<TYPE>newSet;
                newSet.insert(a);
                newSet.insert(b);
                this->push_back(newSet);
              }
            }else{
              if(fa==this->end()){
                fb->insert(a);
              }else if(fb==this->end()){
                fa->insert(b);
              }else{
                std::set<TYPE>newSet;
                for(auto x:*fa)
                  newSet.insert(x);
                for(auto x:*fb)
                  newSet.insert(x);
                this->erase(fa);
                this->erase(fb);
                this->push_back(newSet);
              }
            }
          }

          bool eq(TYPE const&a,TYPE const&b){
            for(auto x:*this)
              if(x.find(a)!=x.end()){
                if(x.find(b)!=x.end())return true;
                else return false;
              }
            return false;
          }

          typename std::vector<std::set<TYPE>>::iterator find(TYPE const &a){
            for(auto x=this->begin();x!=this->end();++x)
              if(x->find(a)!=x->end())return x;
            return this->end();
          }
      };
  }
}

