#pragma once

#include<geCore/Export.h>

#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<memory>
#include<cassert>

#define ___ std::cerr<<__FILE__<<": "<<__LINE__<<std::endl

namespace ge{
  namespace core{
    template<typename T>struct is_basic                    :std::false_type{};
    template<          >struct is_basic<void              >:std::true_type {};
    template<          >struct is_basic<bool              >:std::true_type {};
    template<          >struct is_basic<char              >:std::true_type {};
    template<          >struct is_basic<signed char       >:std::true_type {};
    template<          >struct is_basic<unsigned char     >:std::true_type {};
    template<          >struct is_basic<short             >:std::true_type {};
    template<          >struct is_basic<unsigned short    >:std::true_type {};
    template<          >struct is_basic<int               >:std::true_type {};
    template<          >struct is_basic<unsigned int      >:std::true_type {};
    template<          >struct is_basic<long              >:std::true_type {};
    template<          >struct is_basic<unsigned long     >:std::true_type {};
    template<          >struct is_basic<long long         >:std::true_type {};
    template<          >struct is_basic<unsigned long long>:std::true_type {};
    template<          >struct is_basic<float             >:std::true_type {};
    template<          >struct is_basic<double            >:std::true_type {};
    template<          >struct is_basic<long double       >:std::true_type {};
    template<          >struct is_basic<wchar_t           >:std::true_type {};

#if !defined(_MSC_VER)
    template<          >struct is_basic<char16_t          >:std::true_type {};
    template<          >struct is_basic<char32_t          >:std::true_type {};
#endif



    template<typename...ARGS>
      std::string argsToStr(ARGS...);

    template<typename F,typename...ARGS>
      std::string argsToStr_help(F const&a,ARGS...args){
        std::stringstream ss;
        ss<<a;
        if(sizeof...(args)>0)
          ss<<","<<argsToStr(args...);
        return ss.str();
      }

    template<typename...ARGS>
      std::string argsToStr(ARGS...args){
        return argsToStr_help(args...);
      }

    template<> inline std::string argsToStr(){
      return "";
    }


    //    GECORE_EXPORT extern int indentCounter;
    //    GECORE_EXPORT extern std::string indent;
    class GECORE_EXPORT PrintCallStack{
      public:
        static int indentCounter;
        static std::string indent;
        template<typename...ARGS>
          PrintCallStack(std::string fceName,ARGS...args){
            std::cout<<indent<<fceName<<"("<<argsToStr(args...)<<"){"<<std::endl;
            indentCounter+=2;
            indent="";
            for(int i=0;i<indentCounter;++i)
              indent+=" ";
          }
        ~PrintCallStack(){
          indentCounter-=2;
          if(indentCounter<0)
            indentCounter=0;
          indent="";
          for(int i=0;i<indentCounter;++i)
            indent+=" ";
          std::cout<<indent<<"}"<<std::endl;
        }
    };
  }
}

#if 0
#define PRINT_CALL_STACK(...)ge::core::PrintCallStack superduperhiddenvar(__VA_ARGS__)
#else
#define PRINT_CALL_STACK(...)
#endif



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

    template<typename...ARGS,typename = std::enable_if<sizeof...(ARGS)==0>>
      void printArgs2(ARGS...){
      }

    template<typename HEAD,typename...TAIL>
      void printArgs2(HEAD head,TAIL...tail){
        std::cerr<<","<<head;
        printArgs2(tail...);
      }

    template<typename...ARGS,typename = std::enable_if<sizeof...(ARGS)==0>>
      void printArgs(){
      }

    template<typename HEAD,typename...TAIL>
      void printArgs(HEAD head,TAIL...tail){
        std::cerr<<head;
        printArgs2(tail...);
      }

    template<typename...ARGS,typename = std::enable_if<sizeof...(ARGS)!=0>>
      void printError(std::string fceName,std::string message,ARGS...args){
        std::cerr<<"ERROR: "<<fceName<<"(";
        printArgs(args...);
        std::cerr<<") - "<<message<<std::endl;
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

