#pragma once

#include<geGL/Export.h>

#include<geGL/OpenGL.h>
#include<geGL/OpenGLCapabilities.h>

namespace ge{
  namespace gl{
    namespace opengl{
      class FunctionTable{
        public:
          FunctionTable(){}
          virtual ~FunctionTable(){}
          bool construct(){return this->m_init();}
          Capabilities capabilities;
          virtual bool m_init(){return true;}
#include<geGL/Generated/FunctionTableCalls.h>
#include<geGL/Generated/OpenGLPFN.h>
#include<geGL/Generated/OpenGLFunctions.h>
#include<geGL/Generated/MemberOpenGLPFN.h>
#include<geGL/Generated/MemberOpenGLFunctions.h>
      };

      /*
      class GEGL_EXPORT FunctionTable{
        public:
          Capabilities capabilities;
#include<geGL/Generated/OpenGLFunctions.h>
      };
      */
    }

    /*
       class OpenGLFunctionTableDecorator{
       public:
       inline std::shared_ptr<OpenGLFunctionTable>decorateTable(
       std::shared_ptr<OpenGLFunctionTable>const&table);
       virtual ~OpenGLFunctionTableDecorator(){}
       protected:
       virtual std::shared_ptr<OpenGLFunctionTable>m_myDecoration(
       std::shared_ptr<OpenGLFunctionTable>const&table) = 0;
       std::shared_ptr<OpenGLFunctionTableDecorator>m_inner = nullptr;
       };

       inline std::shared_ptr<OpenGLFunctionTable>OpenGLFunctionTableDecorator::decorateTable(
       std::shared_ptr<OpenGLFunctionTable>const&table){
       if(this->m_inner)return this->m_myDecoration(this->m_inner->decorateTable(table));
       return this->m_myDecoration(table);
       }



       class Loader: public FunctionTableDecorator{
       public:
       Loader();
       virtual ~Loader(){}
       protected:
       virtual std::shared_ptr<OpenGLFunctionTable>m_myDecoration(
       std::shared_ptr<OpenGLFunctionTable>const&table);
       };

       class DSAImplementer: public FunctionTableDecorator{
       public:
       DSAImplementer(std::shared_ptr<FunctionTableDecorator>const&inner);
       protected:
       virtual std::shared_ptr<FunctionTable>m_myDecoration(
       std::shared_ptr<OpenGLFunctionTable>const&table);
       };

       class OpenGLCapabilityExtractory: public OpenGLFunctionTableDecorator{
       public:
       OpenGLCapabilityExtractory(std::shared_ptr<OpenGLFunctionTableDecorator>const&inner);
       protected:
       virtual std::shared_ptr<OpenGLFunctionTable>m_myDecoration(
       std::shared_ptr<OpenGLFunctionTable>const&table);
       };

       class OpenGLFunctionChecker: public OpenGLFunctionTableDecorator{
       public:
       OpenGLFunctionChecker(std::shared_ptr<OpenGLFunctionTableDecorator>const&inner);
       protected:
       virtual std::shared_ptr<OpenGLFunctionTable>m_myDecoration(
       std::shared_ptr<OpenGLFunctionTable>const&table);
       };
       */
  }
}


