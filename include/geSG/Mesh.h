#ifndef GE_SG_MESH_H
#define GE_SG_MESH_H

#include <vector>
#include <geSG/Array.h>
#include <geSG/AttribsReference.h>
#include <geSG/Node.h>

namespace ge
{
   namespace sg
   {

      /** Mesh class represents a scene geometry that can be drawn by a single draw call
       *  on OpenGL 4.3+ graphics hardware.
       *
       *  Mesh class may contain vertex attribute data. The data are uploaded to AttribsStorage
       *  that manages vertex attributes in gpu memory. _attribsReference member holds reference
       *  to the uploaded data.
       * */
      class Mesh : public Node
      {
      public:

         enum class ArrayContent : uint8_t { UNKNOWN=0,COORDINATES=1,NORMALS=2,COLORS=3,TEXCOORDS=4,USER=5,OTHER = 0xff };

      protected:

         bool _cpuGeometryDataAvailable : 1;
         bool _gpuGeometryDataAvailable : 1;
         bool _releaseCpuGeometryDataAfterGpuUpload : 1;

         int _glMode;
         std::vector<Array> _attribs;
         std::vector<ArrayContent> _contents;
         Array _indices;
         std::vector<int8_t> _attribIndex;

         AttribsReference _attribsReference;

      public:

         META_Node(ge::sg,Mesh);

         inline Mesh();
         virtual ~Mesh();

         static inline std::shared_ptr<Mesh> create();
         static inline std::shared_ptr<Mesh> create(const std::vector<Array> attribs,
                                                    const std::vector<ArrayContent> contents);

         template<typename T>
         inline void setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                   const std::shared_ptr<std::vector<T>> &ptr);
         virtual void setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                    const std::shared_ptr<ArrayDecorator>& arrayDecorator);
         inline void setAttribData(unsigned attribIndex,ArrayContent content,const Array &array);
         void setAttribData(const std::vector<Array> attribs, const std::vector<ArrayContent> contents);

         virtual AttribsConfig getAttribsConfig() const;

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
      inline Mesh::Mesh() : _cpuGeometryDataAvailable(false), _gpuGeometryDataAvailable(false),
                            _releaseCpuGeometryDataAfterGpuUpload(true)  {}
      inline std::shared_ptr<Mesh> Mesh::create()  { return _factory->create(); }
      inline std::shared_ptr<Mesh> Mesh::create(const std::vector<Array> attribs, const std::vector<ArrayContent> contents)
      {
         std::shared_ptr<Mesh> m(_factory->create());
         m->setAttribData(attribs,contents);
         return m;
      }
      template<typename T>
      inline void Mesh::setAttribData(unsigned attribIndex,ArrayContent content,AttribType attribType,
                                      const std::shared_ptr<std::vector<T>> &ptr)
      {
         setAttribData(attribIndex,content,attribType,std::make_shared<ArrayDecoratorTemplate<T>>(ptr));
      }
      inline void Mesh::setAttribData(unsigned attribIndex,ArrayContent content,const Array &array)
      {
         setAttribData(attribIndex,content,array.getType(),array.getArrayDecorator());
      }
      std::shared_ptr<Mesh> Mesh::Factory::create() { return std::make_shared<Mesh>(); }
   }
}

#endif // GE_SG_MESH_H
