#pragma once

#include<geCore/Export.h>

#if defined(_MSC_VER) && _MSC_VER<1900
  #pragma warning(disable : 4503)
#endif

#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<memory>

#define ___ std::cerr<<__FILE__<<": "<<__LINE__<<std::endl

namespace ge{
  namespace core{
    class FSA;
    class GECORE_EXPORT ParseEnumArgs{
      protected:
        struct ParserData{
          unsigned      start;
          std::string   key  ;
          ParseEnumArgs*_this;
          unsigned      id   ;
        }_pData;
        static void _begin         (ge::core::FSA*fsa,void*data);
        static void _writeKey      (ge::core::FSA*fsa,void*data);
        static void _storeKey      (ge::core::FSA*fsa,void*data);
        static void _writeStoredKey(ge::core::FSA*fsa,void*data);
        static void _writeValue    (ge::core::FSA*fsa,void*data);
        std::shared_ptr<ge::core::FSA>_f = nullptr;
        std::map<unsigned,std::string>_id2Name;
      public:
        ParseEnumArgs();
        std::map<unsigned,std::string>operator()(const char*args);
    };
  }
}

namespace ge{
  namespace core{
    /*
    template<size_t... _Indexes>
      struct _Index_tuple
      {
        typedef _Index_tuple<_Indexes..., sizeof...(_Indexes)> __next;
      };

    template<size_t _Num>
      struct _Build_index_tuple
      {
        typedef typename _Build_index_tuple<_Num - 1>::__type::__next __type;
      };

    template<>
      struct _Build_index_tuple<0>
      {
        typedef _Index_tuple<> __type;
      };

    /// Class template integer_sequence
    template<typename _Tp, _Tp... _Idx>
      struct integer_sequence
      {
        typedef _Tp value_type;
        static //constexpr
        size_t size() { return sizeof...(_Idx); }
      };

    template<typename _Tp, _Tp _Num,
      typename _ISeq = typename _Build_index_tuple<_Num>::__type>
        struct _Make_integer_sequence;

    template<typename _Tp, _Tp _Num,  size_t... _Idx>
      struct _Make_integer_sequence<_Tp, _Num, _Index_tuple<_Idx...>>
      {
        static_assert( _Num >= 0,
            "Cannot make integer sequence of negative length" );

        typedef integer_sequence<_Tp, static_cast<_Tp>(_Idx)...> __type;
      };

    /// Alias template make_integer_sequence
    template<typename _Tp, _Tp _Num>
      using make_integer_sequence = typename _Make_integer_sequence<_Tp, _Num>::__type;

    /// Alias template index_sequence
    template<size_t... _Idx>
      using index_sequence = integer_sequence<size_t, _Idx...>;

    /// Alias template make_index_sequence
    template<size_t _Num>
      using make_index_sequence = make_integer_sequence<size_t, _Num>;
      
    /// Alias template index_sequence_for
    template<typename... _Types>
      using index_sequence_for = make_index_sequence<sizeof...(_Types)>;
      */

  template <class T, T... I> struct integer_sequence
  {
    template <T N> using append = integer_sequence<T, I..., N>;
    static std::size_t size() { return sizeof...(I); }
    using next = append<sizeof...(I)>;
    using type = T;
  };

  template <class T, T Index, std::size_t N>
    struct sequence_generator
    {
      using type = typename sequence_generator<T, Index - 1, N - 1>::type::next;
    };

  template <class T, T Index>
    struct sequence_generator<T, Index, 0ul> { using type = integer_sequence<T>; };

  template <std::size_t... I>
    using index_sequence = integer_sequence<std::size_t, I...>;

  template <class T, T N>
    struct make_integer_sequence
    {
           typedef typename sequence_generator<T, N, N>::type type;
    };
    //using make_integer_sequence = typename sequence_generator<T, N, N>::type;

  template <std::size_t N>
    using make_index_sequence = make_integer_sequence<std::size_t, N>;

  template<class... T>
    using index_sequence_for = make_index_sequence<sizeof...(T)>;
  }
}


#define VA_ARGS_TO_STRING(...)\
#__VA_ARGS__

#define DEF_ENUM(name,...)\
  enum name{\
    __VA_ARGS__\
  };\
friend std::ostream& operator<<(std::ostream& os,const name&val){\
  static std::map<unsigned,std::string>table = ge::core::ParseEnumArgs()(VA_ARGS_TO_STRING(__VA_ARGS__));\
  auto a=table.find(val);\
  if(a!=table.end())os << a->second;\
  return os;\
}

namespace ge{
  namespace core{
    template<typename T>
      void argsToVector(std::vector<T>&){
      }

    template<typename T>
      void argsToVector(std::vector<T>&vec,T const&v){
        vec.push_back(v);
      }

    template<typename T,typename... Args>
      void argsToVector(std::vector<T>&vec,T const&v,Args... args){
        argsToVector(vec,v);
        argsToVector(vec,args...);
      }


    template<unsigned SIZE,typename TYPE>
      void argsToArray(TYPE data[SIZE],TYPE const&v){
        data[SIZE-1]=v;
      }
    template<unsigned SIZE,typename TYPE,typename... Args>
      inline void argsToArray(TYPE data[SIZE],TYPE const&v, Args... args){
        data[SIZE-1-sizeof...(args)]=v;
        argsToArray<SIZE,TYPE>(data,args...);
      }


    template<typename TPtr>
      void deleteSetNull(TPtr&b){
        if(b)delete b;b=NULL;
      }

    template<typename TPtr,typename...Args>
      void deleteSetNull(TPtr&b,Args... args){
        deleteSetNull(b);
        deleteSetNull(args...);
      }


    template<typename T>
      void filterArgsToVector(std::vector<T>&data,T const& t){
        data.push_back(t);
      }

    template<typename T,typename T2>
      void filterArgsToVector(std::vector<T>&,T2){}

    template<typename T,typename T2,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T2,Args... args);

    template<typename T,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T const& t,Args... args){
        filterArgsToVector(data,t);
        filterArgsToVector(data,args...);
      }

    template<typename T,typename T2,typename... Args>
      void filterArgsToVector(std::vector<T>&data,T2,Args... args){
        filterArgsToVector(data,args...);
      }


    template<unsigned... Is>
      struct seq { };

    template<unsigned N, unsigned... Is>
      struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<unsigned... Is>
      struct gen_seq<0, Is...> : seq<Is...> { };


    template<typename T>
      T notequal(const T ref,const T t){
        return ref!=t;
      }

    template<typename T,typename... Args>
      T notequal(const T ref,const T t,Args... args){
        return ref!=t&&notequal(ref,args...);
      }

    template<typename T,typename... Args>
      T nonof_rec(const T halt,const T t0,const T t1,Args... args){
        //static_assert(halt!=t0,"there is no space for nonof");
        return halt==t0?0:notequal(t0,t1,args...)?t0:nonof_rec(halt,t0+1,t1,args...);
      }

    template<typename T,typename... Args>
      T nonof(const T t0,const T t1,Args... args){
        return nonof_rec(t0,t0+1,t1,args...);
      }



    GECORE_EXPORT unsigned getDispatchSize(unsigned workSize,unsigned workGroupSize);
    GECORE_EXPORT unsigned bitCount(unsigned value);

    template<typename TYPE,bool SET,bool GET>
      class Attrib{
        protected:
          TYPE _value;
        public:
          Attrib(TYPE const&value){this->_value = value;}
          Attrib(){}
          template<typename T = TYPE>
            inline typename std::enable_if<GET,T>::type&get(){return this->_value;}
          template<typename T = TYPE>
            inline void set(typename std::enable_if<SET,T>::type const&value){this->_value = value;}
      };
    template<typename TO,typename FROM>
      TO convertTo(FROM const&d);

    template<typename TO,typename FROM>
      TO convertTo(FROM const&d){
        return d;
      }


    template<typename TYPE>
      inline void convertFrom(std::shared_ptr<TYPE>&output,TYPE const&input){
        *output=input;
      }

    template<typename TYPE>
      inline void convertFrom(TYPE*&output,TYPE const&input){
        *output=input;
      }

    template<typename TYPE>
      inline void convertFrom(TYPE &output,TYPE const&input){
        output = input;
      }

  }

}

#define DEF_NAMED_ATTRIBUTE(newClassName,type,set,get)\
  class newClassName: public ge::core::Attrib<type,set,get>{\
    public:\
           newClassName(type const&val):ge::core::Attrib<type,set,get>(val){}\
  }

#define DEF_ATTRIBUTE(newClassName,type)\
  DEF_NAMED_ATTRIBUTE(newClassName,type,false,false)

#define DEF_ATTRIBUTE_R(newClassName,type)\
  DEF_NAMED_ATTRIBUTE(newClassName,type,false,true)

#define DEF_ATTRIBUTE_W(newClassName,type)\
  DEF_NAMED_ATTRIBUTE(newClassName,type,true,false)

#define DEF_ATTRIBUTE_RW(newClassName,type)\
  DEF_NAMED_ATTRIBUTE(newClassName,type,true,true)


#define DEF_NAMED_TEMPLATE_ATTRIBUTE(newClassName)\
  template<typename TYPE,bool SET=true,bool GET=true>\
class newClassName: public ge::core::Attrib<TYPE,SET,GET>{\
  public:\
         newClassName(TYPE const&val):ge::core::Attrib<TYPE,SET,GET>(val){}\
}

