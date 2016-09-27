#pragma once

#include<iostream>
#include<vector>
#include<geDE/TypeRegister.h>
#include<geAd/LibraryLoader/ClassMetaData.h>
#include<geAd/LibraryLoader/RuntimeClassMetaData.h>

namespace ge{
  namespace ad{
    class GEAD_EXPORT RuntimeClassInterface{
      protected:
        RuntimeClassMetaData*_classMetaData = nullptr;
        std::shared_ptr<de::TypeRegister>_typeRegister = nullptr;
        bool _functionArgsMatch(std::vector<de::Resource>&args,unsigned fce)const;
        bool _constructorArgsMatch(std::vector<de::Resource>&args,unsigned id)const;

        //template<typename,typename...>
        void _argsToResourceVector(std::shared_ptr<de::TypeRegister>const&,std::vector<de::Resource>&)const{}
        template<typename TYPE,typename... ARGS>
          void _argsToResourceVector(std::shared_ptr<de::TypeRegister>const&typeRegister,std::vector<de::Resource>&vec,/*typename std::enable_if<!std::is_same<TYPE,de::Resource>::value,*/TYPE/*>::type*/ const&val,ARGS... args)const{
            de::Resource ac(val,typeRegister);
            vec.push_back(ac);//de::Resource(val,typeRegister));
            this->_argsToResourceVector(typeRegister,vec,args...);
          }
        template<typename... ARGS>
          void _argsToResourceVector(std::shared_ptr<de::TypeRegister>const&typeRegister,std::vector<de::Resource>&vec,de::Resource const&val,ARGS... args)const{
            vec.push_back(val);
            this->_argsToResourceVector(typeRegister,vec,args...);
          }


      public:
        RuntimeClassInterface(
            std::shared_ptr<de::TypeRegister>&typeRegister,
            ClassMetaData const&classMetaData);
        std::string dir()const;
        virtual ~RuntimeClassInterface();
        std::string getClassName()const;
        std::vector<ge::ad::RuntimeFceMetaData>::size_type getNofFunctions()const;
        std::string getFunctionName(unsigned id)const;
        de::TypeId getFunctionReturnTypeId(unsigned id)const;
        std::vector<ge::ad::RuntimeArgMetaData>::size_type getNofFunctionArguments(unsigned id)const;
        de::TypeId getFunctionArgumentTypeId(unsigned id,unsigned arg)const;
        std::string getFunctionArgumentName(unsigned fce,unsigned arg)const;
        virtual void call(void*instance,std::string fce,std::vector<de::Resource>&args);
        template<typename... ARGS>
          void call(void*instance,std::string fce,ARGS...args){
            std::vector<de::Resource>a;
            this->_argsToResourceVector(this->_typeRegister,a,args...);
            this->call(instance,fce,a);
          }
        std::vector<ge::ad::RuntimeConstructorMetaData>::size_type getNofConstructors()const;
        std::vector<ge::ad::RuntimeArgMetaData>::size_type getNofConstructorArguments(unsigned id)const;
        de::TypeId getConstructorArgumentTypeId(unsigned id,unsigned arg)const;
        std::string getConstructorArgumentName(unsigned id,unsigned arg)const;
        virtual void*construct(std::vector<de::Resource>&args)const;
        template<typename... ARGS>
          void*construct(ARGS...args)const{
            std::vector<de::Resource>a;
            this->_argsToResourceVector(this->_typeRegister,a,args...);
            return this->construct(a);
          }

        virtual void destroy(void*instance)const;
    };
  }
}
