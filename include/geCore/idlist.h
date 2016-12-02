#ifndef GE_CORE_IDLIST_H
#define GE_CORE_IDLIST_H

#include <unordered_map>
#include <ostream>
#include <string>

namespace ge {
namespace core {


/** idlist_register_data keeps run-time data for particular idlist.
 *  The template parameter T allows the underlying enum type to vary
 *  (int, unsigned, long long int, etc.). */
template<typename T>
struct idlist_register_data {
   std::unordered_map<std::string,T> str2id;  ///< Map from string to enumeration item (id).
   std::unordered_map<T,std::string> id2str;  ///< Map from enumeration item (id) to string.
   T next_available_id;             ///< Id that will be assigned upon next allocation request.
   idlist_register_data(const char* s);  ///< Constructor. The parameter s must be non-null,
                                         ///< pointing to idlist initialization string
                                         ///< (possibly empty) that will be used to fill
                                         ///< idlist_register_data with initial content.
};


template<typename T>
idlist_register_data<T>::idlist_register_data(const char* s)
   : next_available_id(0)
{
#if 0 // debug
   std::cout<<"idlist_register_data construction string: \""<<s<<'\"'<<std::endl;
#endif
   const char *p=s;
   do {
      while(*p==',' || *p==' ')  p++;
      if(*p==0) break;
      const char *start=p;
      while((*p>='A'&&*p<='Z')||(*p>='a'&&*p<='z')||(*p=='_'))  p++;
      std::string name(start,p-start);
      T value=0;
      bool hasValue=false;
      while(*p==' ')  p++;
      if(*p=='=') {
         while(*(++p)==' ');
         while(*p>='0'&&*p<='9') {
            value*=10;
            value+=(*p)-'0';
            p++;
         }
         hasValue=true;
         next_available_id=value+1;
      }
      T id=hasValue?value:next_available_id++;
#if 0 // debug
      std::cout<<"idlist_register_data processed token: \""<<name<<"\", value: "<<id<<std::endl;
#endif
      str2id.insert(std::pair<std::string,T>(name,id));
      id2str.insert(std::pair<T,std::string>(id,name));
      if(*p==0) break;
      p++;
   } while(true);
}


/** Declares idlist. The first parameter is the name of the list
 *  and the underlying enum. Following parameters can be omitted
 *  or they can be used to declare the list members in the same way
 *  as when using standard enum declaration. */
#define idlist(_name_,...) \
   enum class _name_ {__VA_ARGS__}; \
   \
   struct _name_##_register { \
      typedef _name_ EnumType; \
      typedef std::underlying_type<_name_>::type UnderlyingType; \
      const char* chars = #_name_; \
      static ge::core::idlist_register_data<UnderlyingType>& get() \
      { \
         static ge::core::idlist_register_data<UnderlyingType> r(#__VA_ARGS__); \
         return r; \
      } \
      static EnumType str2id(const std::string& s) \
      { \
         auto& reg=get(); \
         auto it=reg.str2id.find(s); \
         if(it!=reg.str2id.end()) \
            return static_cast<EnumType>(it->second); \
         auto id=reg.next_available_id; \
         reg.next_available_id++; \
         reg.str2id.insert(std::pair<std::string,UnderlyingType>(s,id)); \
         reg.id2str.insert(std::pair<UnderlyingType,std::string>(id,s)); \
         /* debug line bellow */ \
         /* std::cout<<"idlist: Created entry \""<<s<<"\": "<<id<<std::endl; */ \
         return static_cast<EnumType>(id); \
      } \
      static bool str2id(const std::string& s,EnumType &id) \
      { \
         auto& reg=get(); \
         auto it=reg.str2id.find(s); \
         if(it==reg.str2id.end()) \
            return false; \
         id=static_cast<EnumType>(it->second); \
         return true; \
      } \
   }; \
   \
   friend std::ostream& operator<<(std::ostream& os,_name_ value) \
   { \
      auto& m=_name_##_register::get().id2str; \
      auto it=m.find(static_cast<_name_##_register::UnderlyingType>(value)); \
      os<<(it!=m.end()?it->second:"?"); \
      return os; \
   }

// idlist_empty macro is used to declare initially empty idlist.
// Using idlist(name) violates C99 standard and causes g++ emit warning:
// "ISO C99 requires rest arguments to be used".
// You can use idlist(name,) or idlist_empty(name).
#define idlist_empty(_name_) \
   idlist(_name_,)


#if defined(_MSC_VER) && _MSC_VER<1900 // MSVC 2013 workaround (it does not support constexpr
                                       // and passing string as
                                       // struct id_name { const char* chars = #_id_name_; };
                                       // does not seem to work.
                                       // So, we provide alternative solution (little less optimal)
                                       // that allow us to use even this compiler)


#define idof(_enum_type_,_id_name_) \
([]() -> _enum_type_ { \
   static _enum_type_ id = _enum_type_##_register::str2id(#_id_name_); \
   return id; \
}())


#else // full blown optimal solution using all template features


template<unsigned count,template<unsigned...> class meta_functor,unsigned... indices>
struct idof_apply_range
{
   typedef typename idof_apply_range<count-1,meta_functor,count-1,indices...>::result result;
};


template<template<unsigned...> class meta_functor,unsigned... indices>
struct idof_apply_range<0,meta_functor,indices...>
{
   typedef typename meta_functor<indices...>::result result;
};


template<char... str>
struct idof_string
{
   static constexpr const char chars[sizeof...(str)+1] = {str...,'\0'};
};


template<char... str>
constexpr const char idof_string<str...>::chars[sizeof...(str)+1];


template<typename lambda_str_type>
struct idof_string_builder
{
   template<unsigned... indices>
   struct produce
   {
      typedef idof_string<lambda_str_type{}.chars[indices]...> result;
   };
};


template<typename enum_register,typename id_name>
class idof_template {
public:
   typedef typename enum_register::EnumType EnumType;
   typedef typename enum_register::UnderlyingType UnderlyingType;
   static EnumType id;
};


template<typename enum_register,typename id_name>
typename enum_register::EnumType idof_template<enum_register,id_name>::id =
   []() {
#if 0 // debug
      std::cout<<"Init \""<<id_name{}.chars<<"\" on \""<<enum_register{}.chars<<'\"'<<std::endl;
#endif
      return enum_register::str2id(id_name{}.chars);
   }();


/** idof returns id (enum item) given by the second parameter.
 *  The first parameter is the name of idlist created by idlist macro.
 *  idof is very effective as it evaluates in compile time to a variable
 *  holding id value in run-time. */
#define idof(_enum_type_,_id_name_) \
([]() -> _enum_type_ { \
   struct id_name { const char* chars = #_id_name_; }; \
   return ge::core::idof_template< \
      _enum_type_##_register, \
      ge::core::idof_apply_range<sizeof(#_id_name_)-1, \
         ge::core::idof_string_builder<id_name      >::produce>::result \
      >::id; \
}())


#endif // MSVC 2013 workaround and optimal template solution


/** idofstring returns id (enum item) given by the second parameter
 *  that must be std::string.
 *  The first parameter is the name of idlist created by idlist macro.
 *  ifofstring is less effective than idof as it evaluates in run-time
 *  using map lookup. Thus, use of idof is preferred whenever enum item
 *  is not dynamically generated. */
#define idofstring(_enum_type_,id_string) \
(_enum_type_##_register::str2id(id_string))


} /* namespace core */
} /* namespace ge */


#endif /* GE_CORE_IDLIST_H */
