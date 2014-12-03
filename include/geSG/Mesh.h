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

      /** Mesh class represents a scene geometry that can be drawn by a single draw call
       *  on OpenGL 4.3+ graphics hardware.
       *
       *  Mesh class may contain vertex attribute data. The data are uploaded to AttribStorage
       *  that manages vertex attributes in gpu memory. _attribReference member holds reference
       *  to the uploaded data.
       * */
      class Mesh : public Node
      {
      public:

         enum class ArrayContent : uint8_t { UNKNOWN=0,COORDINATES=1,NORMALS=2,COLORS=3,TEXCOORDS=4,USER=5,OTHER = 0xff };

      protected:

         bool _cpuAttribDataAvailable : 1;
         bool _gpuAttribDataAvailable : 1;
         bool _releaseCpuAttribDataAfterGpuUpload : 1;

         int _glMode;
         std::vector<Array> _attribArrays;
         std::vector<ArrayContent> _contents;
         Array _indexArray;
         std::vector<int8_t> _content2attribIndex;

         AttribReference _attribReference;

      public:

         META_Node(ge::sg,Mesh);

         inline Mesh();
         virtual ~Mesh();

         static inline std::shared_ptr<Mesh> create();
         static inline std::shared_ptr<Mesh> create(const std::vector<Array> attribs,
                                                    const std::vector<ArrayContent> contents);

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

         inline int getNumAttribArrays() const;
         inline bool hasIndices() const;

         inline const std::vector<Array>& getAttribArrays();
         inline Array& getAttribArray(int index);
         inline Array& getAttribArray(ArrayContent content);
         inline Array& getIndexArray();

         inline const AttribReference& getAttribReference() const;
         virtual AttribConfig getAttribConfig() const;

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
      inline std::shared_ptr<Mesh> Mesh::create(const std::vector<Array> attribs, const std::vector<ArrayContent> contents)
      {
         std::shared_ptr<Mesh> m(_factory->create());
         m->setAttribArrays(attribs,contents);
         return m;
      }
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
      inline int Mesh::getNumAttribArrays() const  { return _attribArrays.size(); }
      inline bool Mesh::hasIndices() const  { return _indexArray.getType() != AttribType::Empty; }
      inline const std::vector<Array>& Mesh::getAttribArrays()  { return _attribArrays; }
      inline Array& Mesh::getAttribArray(int index)  { return _attribArrays[index]; }
      inline Array& Mesh::getAttribArray(ArrayContent content)  { return _attribArrays[_content2attribIndex[uint8_t(content)]]; }
      inline Array& Mesh::getIndexArray()  { return _indexArray; }
      inline const AttribReference& Mesh::getAttribReference() const  { return _attribReference; }
   }
}

#endif // GE_SG_MESH_H
