#pragma once

namespace ge{
  namespace core{
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessorTypeID(TypeID id,ARGS... args)const{
        //std::shared_ptr<ge::core::Accessor>ptr=std::shared_ptr<Accessor>(new Accessor(this->shared_from_this(),this->alloc(id),id),[](Accessor*ac){ac->free();delete ac;});
        auto ptr=std::make_shared<AtomicAccessor>(this->shared_from_this(),this->alloc(id),id);
        ptr->callConstructor<CLASS>(args...);
        return ptr;
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessor(std::string name,ARGS... args)const{
        TypeID id=this->getTypeId(name);
        return this->sharedAccessorTypeID<CLASS>(id,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessor(const char* name,ARGS... args)const{
        TypeID id=this->getTypeId(std::string(name));
        return this->sharedAccessorTypeID<CLASS>(id,args...);
      }

    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessor(ARGS... args)const{
        //return this->sharedAccessor<CLASS>(this->getTypeKeyword<CLASS>(),args...);
        TypeID id=this->getTypeId(this->getTypeKeyword<CLASS>());
        return this->sharedAccessorTypeID<CLASS>(id,args...);
      }

    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessorAddCD(std::string name,ARGS... args){
        this->addClassCD<CLASS>(name);
        return this->sharedAccessor<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessorAddC(std::string name,ARGS... args){
        this->addClassC<CLASS>(name);
        return this->sharedAccessor<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessorAddD(std::string name,ARGS... args){
        this->addClassD<CLASS>(name);
        return this->sharedAccessor<CLASS>(name,args...);
      }
    template<typename CLASS,typename... ARGS>
      inline std::shared_ptr<Accessor>TypeRegister::sharedAccessorAdd(std::string name,ARGS... args){
        this->addClass<CLASS>(name);
        return this->sharedAccessor<CLASS>(name,args...);
      }


  }
}
