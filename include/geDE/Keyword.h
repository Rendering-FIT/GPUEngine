#pragma once

#include<type_traits>
#include<iostream>
#include<sstream>
#include<geCore/TypeTraits.h>
#include<geCore/Dtemplates.h>

namespace ge{
  namespace de{

    template<typename T,typename std::enable_if<ge::core::is_basic<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_function<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_member_function_pointer<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_array<T>::value && !std::is_const<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_class<T>::value && !std::is_const<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<!std::is_pointer<T>::value &&  std::is_const<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if< std::is_pointer<T>::value &&  std::is_const<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if< std::is_pointer<T>::value && !std::is_const<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_reference<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_enum<T>::value,unsigned>::type = 0>
      std::string keyword();

    template<typename T,typename std::enable_if<std::is_array<T>::value,unsigned>::type = 0>
      std::string extents();

    template<typename T,typename std::enable_if<!std::is_array<T>::value,unsigned>::type = 0>
      inline std::string extents(){
        return "";
      }





    //template<typename...ARGS,typename std::enable_if<sizeof...(ARGS)==0,unsigned>::type = 0>
    inline std::string argPrinter(){
      return"";
    }

    template<typename HEAD>//,typename...ARGS,typename std::enable_if<sizeof...(ARGS)==0,unsigned>::type = 0>
      inline std::string argPrinter(){
        return keyword<HEAD>();
      }

    template<typename HEAD,typename...ARGS>//,typename std::enable_if<(sizeof...(ARGS)!=0),unsigned>::type = 0>
      inline typename std::enable_if<(sizeof...(ARGS)!=0),std::string>::type argPrinter(){
        return keyword<HEAD>()+","+argPrinter<ARGS...>();
      }

    template<typename TTT,std::size_t...I>
      inline std::string printArgs2_help(ge::core::index_sequence<I...>){
        return argPrinter<typename std::tuple_element<I,TTT>::type...>();
      }

    template<typename T,typename std::enable_if<!std::is_same<T,std::tuple<>>::value,unsigned>::type = 0>
      inline std::string printArgs2(){
        return printArgs2_help<T>(typename ge::core::make_index_sequence<std::tuple_size<T>::value>::type{});
      }
    template<typename T,typename std::enable_if<std::is_same<T,std::tuple<>>::value,unsigned>::type = 0>
      inline std::string printArgs2(){
        return"";
      }




    template<typename...ARGS>
      inline std::string printArgs(std::tuple<ARGS...>const&){
        return argPrinter<ARGS...>();
      }

    template<typename T,typename std::enable_if<std::is_function<T>::value,unsigned>::type>
      inline std::string keyword(){
        return "("+
          printArgs2<typename ge::core::FceArgType<T>::type>()
          //printArgs(typename ge::core::FceArgType<T>::type())
          +")->"+keyword<typename ge::core::FceReturnType<T>::type>();
      }



    template<typename T,typename std::enable_if<std::is_member_function_pointer<T>::value,unsigned>::type>
      inline std::string keyword(){
        return keyword<typename ge::core::MemFceClassType<T>::type>()+"::("+
          printArgs2<typename ge::core::MemFceArgType<T>::type>()
          //printArgs(typename ge::core::MemFceArgType<T>::type())
          +")->"+keyword<typename ge::core::MemFceReturnType<T>::type>();
      }




    template<typename T,typename std::enable_if<std::is_array<T>::value,unsigned>::type>
      inline std::string extents(){
        std::stringstream ss;
        ss<<"[";
        ss<<std::extent<T>::value;
        ss<<"]";
        ss<<extents<typename std::remove_extent<T>::type>();
        return ss.str();
      }

    template<typename T,typename std::enable_if<std::is_array<T>::value && !std::is_const<T>::value,unsigned>::type>
      inline std::string keyword(){
        std::stringstream ss;
        ss<<keyword<typename std::remove_all_extents<T>::type>();
        ss<<extents<T>();
        return ss.str();
      }

    template<typename T,typename std::enable_if< std::is_pointer<T>::value && !std::is_const<T>::value,unsigned>::type>
      inline std::string keyword(){return keyword<typename std::remove_pointer<T>::type>()+"*";}

    template<typename T,typename std::enable_if<!std::is_pointer<T>::value &&  std::is_const<T>::value,unsigned>::type>
      inline std::string keyword(){return keyword<typename std::remove_const<T>::type>();}//+" const";}

    template<typename T,typename std::enable_if<std::is_enum<T>::value,unsigned>::type>
      std::string keyword(){
        return keyword<int32_t>();
      }



  template<typename T,typename std::enable_if< std::is_pointer<T>::value &&  std::is_const<T>::value,unsigned>::type>
    inline std::string keyword(){return keyword<typename std::remove_const<T>::type>();}//+"const";}

    template<typename T,typename std::enable_if<std::is_reference<T>::value,unsigned>::type>
    inline std::string keyword(){return keyword<typename std::remove_reference<T>::type>();}//+"&";}

    /*
       template<>inline std::string keyword<void              >(){return "void"              ;}
       template<>inline std::string keyword<bool              >(){return "bool"              ;}
       template<>inline std::string keyword<char              >(){return "char"              ;}
       template<>inline std::string keyword<signed char       >(){return "signed char"       ;}
       template<>inline std::string keyword<unsigned char     >(){return "unsigned char"     ;}
       template<>inline std::string keyword<short             >(){return "short"             ;}
       template<>inline std::string keyword<unsigned short    >(){return "unsigned short"    ;}
       template<>inline std::string keyword<int               >(){return "int"               ;}
       template<>inline std::string keyword<unsigned int      >(){return "unsigned int"      ;}
       template<>inline std::string keyword<long              >(){return "long"              ;}
       template<>inline std::string keyword<unsigned long     >(){return "unsigned long"     ;}
       template<>inline std::string keyword<long long         >(){return "long long"         ;}
       template<>inline std::string keyword<unsigned long long>(){return "unsigned long long";}
       template<>inline std::string keyword<float             >(){return "float"             ;}
       template<>inline std::string keyword<double            >(){return "double"            ;}
       template<>inline std::string keyword<long double       >(){return "long double"       ;}
       template<>inline std::string keyword<wchar_t           >(){return "wchar_t"           ;}
       template<>inline std::string keyword<char16_t          >(){return "char16_t"          ;}
       template<>inline std::string keyword<char32_t          >(){return "char32_t"          ;}
       */
    }
}
