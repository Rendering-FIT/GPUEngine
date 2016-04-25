#pragma once

#include<iostream>
#include<vector>
#include<geCore/TypeRegister.h>
#include<geUtil/LibraryLoader/ClassMetaData.h>
#include<geUtil/LibraryLoader/RuntimeClassMetaData.h>

namespace ge{
  namespace util{
    class GEUTIL_EXPORT RuntimeClassInterface{
      protected:
        RuntimeClassMetaData*_classMetaData = nullptr;
        std::shared_ptr<ge::core::TypeRegister>_typeRegister = nullptr;
        bool _functionArgsMatch(std::vector<ge::core::Resource>&args,unsigned fce)const;
        bool _constructorArgsMatch(std::vector<ge::core::Resource>&args,unsigned id)const;

        //template<typename,typename...>
        void _argsToResourceVector(std::shared_ptr<ge::core::TypeRegister>const&,std::vector<ge::core::Resource>&)const{}
        template<typename TYPE,typename... ARGS>
          void _argsToResourceVector(std::shared_ptr<ge::core::TypeRegister>const&typeRegister,std::vector<ge::core::Resource>&vec,/*typename std::enable_if<!std::is_same<TYPE,ge::core::Resource>::value,*/TYPE/*>::type*/ const&val,ARGS... args)const{
            ge::core::Resource ac(val,typeRegister);
            vec.push_back(ac);//ge::core::Resource(val,typeRegister));
            this->_argsToResourceVector(typeRegister,vec,args...);
          }
        template<typename... ARGS>
          void _argsToResourceVector(std::shared_ptr<ge::core::TypeRegister>const&typeRegister,std::vector<ge::core::Resource>&vec,ge::core::Resource const&val,ARGS... args)const{
            vec.push_back(val);
            this->_argsToResourceVector(typeRegister,vec,args...);
          }


      public:
        RuntimeClassInterface(
            std::shared_ptr<ge::core::TypeRegister>&typeRegister,
            ClassMetaData const&classMetaData);
        std::string dir()const;
        virtual ~RuntimeClassInterface();
        std::string getClassName()const;
        std::vector<ge::util::RuntimeFceMetaData>::size_type getNofFunctions()const;
        std::string getFunctionName(unsigned id)const;
        ge::core::TypeRegister::TypeID getFunctionReturnTypeID(unsigned id)const;
        std::vector<ge::util::RuntimeArgMetaData>::size_type getNofFunctionArguments(unsigned id)const;
        ge::core::TypeRegister::TypeID getFunctionArgumentTypeID(unsigned id,unsigned arg)const;
        std::string getFunctionArgumentName(unsigned fce,unsigned arg)const;
        virtual void call(void*instance,std::string fce,std::vector<ge::core::Resource>&args);
        template<typename... ARGS>
          void call(void*instance,std::string fce,ARGS...args){
            std::vector<ge::core::Resource>a;
            this->_argsToResourceVector(this->_typeRegister,a,args...);
            this->call(instance,fce,a);
          }
        std::vector<ge::util::RuntimeConstructorMetaData>::size_type getNofConstructors()const;
        std::vector<ge::util::RuntimeArgMetaData>::size_type getNofConstructorArguments(unsigned id)const;
        ge::core::TypeRegister::TypeID getConstructorArgumentTypeID(unsigned id,unsigned arg)const;
        std::string getConstructorArgumentName(unsigned id,unsigned arg)const;
        virtual void*construct(std::vector<ge::core::Resource>&args)const;
        template<typename... ARGS>
          void*construct(ARGS...args)const{
            std::vector<ge::core::Resource>a;
            this->_argsToResourceVector(this->_typeRegister,a,args...);
            return this->construct(a);
          }

        virtual void destroy(void*instance)const;
    };
  }
}
