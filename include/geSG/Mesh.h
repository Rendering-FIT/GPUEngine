#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <vector>
#include <geSG/Array.h>
#include <geSG/AttribReference.h>
#include <geSG/Node.h>

namespace ge
{
   namespace sg
   {

      /** Mesh class represents a scene geometry and associated draw commands data
       *  that are used for rendering of mesh.
       *
       *  Mesh class contains vertex attribute data, indices and draw commands data.
       *  All these data are uploaded to AttribStorage that efficiently manages
       *  their storage in gpu memory. _attribReference member holds the reference
       *  to the uploaded data.
       */
      class Mesh : public Node
      {
      public:

         enum class ArrayContent : uint8_t { UNKNOWN=0,COORDINATES=1,NORMALS=2,COLORS=3,TEXCOORDS=4,USER=5,OTHER=0xff };

      protected:

         bool _cpuAttribDataAvailable : 1;
         bool _gpuAttribDataAvailable : 1;
         bool _releaseCpuAttribDataAfterGpuUpload : 1;

         int _glMode;
         std::vector<Array> _attribArrays;
         std::vector<ArrayContent> _contents;
         std::vector<int8_t> _content2attribIndex;
         Array _indexArray;
         std::vector<DrawCommandData> _drawCommands;

         AttribReference _attribReference;

      public:

         META_Node(ge::sg,Mesh);

         inline Mesh();
         virtual ~Mesh();

         static inline std::shared_ptr<Mesh> create();

         virtual void resetCpuGeometryData();
         virtual void gpuUploadGeometryData();
         virtual void gpuDownloadGeometryData();

         void setAttribArrays(const std::vector<Array> attribs, const std::vector<ArrayContent> contents);
         inline void setAttribArray(unsigned attribIndex,ArrayContent content,const Array &array);
         template<typename T>
         inline void setAttribArray(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                    const std::shared_ptr<std::vector<T>> &ptr);
         virtual void setAttribArray(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                     const std::shared_ptr<ArrayDecorator>& arrayDecorator);

         void setIndexArray(const Array &array);
         inline void setIndexArray(const std::shared_ptr<std::vector<unsigned>> &ptr);
         virtual void setIndexArray(const std::shared_ptr<ArrayDecoratorTemplate<unsigned>>& arrayDecorator);

         inline void setDrawCommands(const std::vector<DrawCommandData>& drawCommands);
         virtual void setDrawCommandsBySwap(std::vector<DrawCommandData>& drawCommands);

         inline int getNumAttribArrays() const;
         inline bool hasIndices() const;

         inline const std::vector<Array>& getAttribArrays();
         inline Array& getAttribArray(int index);
         inline Array& getAttribArray(ArrayContent content);
         inline Array& getIndexArray();
         inline std::vector<DrawCommandData>& getDrawCommands();

         inline const AttribReference& getAttribReference() const;
         inline AttribStorage* getAttribStorage() const;
         inline const AttribConfigRef& getAttribConfig() const;
         virtual AttribConfigRef computeAttribConfig(AttribManager *manager) const;
         inline AttribConfigRef computeAttribConfig() const;

         class Factory {
         public:
            virtual std::shared_ptr<Mesh> create();
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };


      // inline and template methods
      inline Mesh::Mesh() : _cpuAttribDataAvailable(false), _gpuAttribDataAvailable(false),
                            _releaseCpuAttribDataAfterGpuUpload(true)  {}
      inline std::shared_ptr<Mesh> Mesh::create()  { return _factory->create(); }
      template<typename T>
      inline void Mesh::setAttribArray(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                       const std::shared_ptr<std::vector<T>> &ptr)
      {
         setAttribArray(attribIndex,content,attribType,std::make_shared<ArrayDecoratorTemplate<T>>(ptr));
      }
      inline void Mesh::setAttribArray(unsigned attribIndex,ArrayContent content,const Array &array)
      {
         setAttribArray(attribIndex,content,array.getType(),array.getArrayDecorator());
      }
      inline void Mesh::setIndexArray(const std::shared_ptr<std::vector<unsigned>> &ptr)
      {
         setIndexArray(std::make_shared<ArrayDecoratorTemplate<unsigned>>(ptr));
      }
      inline void Mesh::setDrawCommands(const std::vector<DrawCommandData>& drawCommands)
      { std::vector<DrawCommandData> tmp(drawCommands); setDrawCommandsBySwap(tmp); }
      inline int Mesh::getNumAttribArrays() const  { return _attribArrays.size(); }
      inline bool Mesh::hasIndices() const  { return _indexArray.getType() != AttribType::Empty; }
      inline const std::vector<Array>& Mesh::getAttribArrays()  { return _attribArrays; }
      inline Array& Mesh::getAttribArray(int index)  { return _attribArrays[index]; }
      inline Array& Mesh::getAttribArray(ArrayContent content)  { return _attribArrays[_content2attribIndex[uint8_t(content)]]; }
      inline Array& Mesh::getIndexArray()  { return _indexArray; }
      inline std::vector<DrawCommandData>& Mesh::getDrawCommands()  { return _drawCommands; }
      inline const AttribReference& Mesh::getAttribReference() const  { return _attribReference; }
      inline AttribStorage* Mesh::getAttribStorage() const  { return _attribReference.attribStorage; }
      inline const AttribConfigRef& Mesh::getAttribConfig() const
      { return _attribReference.valid() ? _attribReference.attribStorage->getAttribConfig() : AttribConfigRef::invalid; }
      inline AttribConfigRef Mesh::computeAttribConfig() const  { return computeAttribConfig(AttribManager::instance().get()); }
   }
}

#endif // GE_SG_MESH_H
