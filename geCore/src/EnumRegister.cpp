#include <GPUEngine/geCore/EnumRegister.h>

using namespace std;

ge::core::EnumRegister::EnumRegister()
   : _next(0)
{

}

unsigned ge::core::EnumRegister::registerConstant(const char * name)
{
   string sname(name);
   return registerConstant(sname);
}

unsigned ge::core::EnumRegister::registerConstant(const std::string& name)
{
   //maximum value reached
   if(_next == notRegistered) return notRegistered;

   auto it = _byName.find(name);
   if(it != _byName.end())
   {
      return it->second;
   }
   else
   {
      _byName[name] = _next;
      _byValue[_next] = name;
      return _next++;
   }
}

unsigned ge::core::EnumRegister::getValue(const char* name) const
{
   string sname(name);
   return getValue(sname);
}

unsigned ge::core::EnumRegister::getValue(const std::string& name) const
{
   auto it = _byName.find(name);
   if(it == _byName.end()) return notRegistered;
   return it->second;
}

std::string ge::core::EnumRegister::getName(unsigned value) const
{
   auto it = _byValue.find(value);
   if(it == _byValue.end()) return string();
   return it->second;
}
