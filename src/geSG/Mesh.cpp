#include <geSG/Mesh.h>

using namespace std;
using namespace ge::sg;


void Mesh::setAttribData(unsigned attribIndex, ArrayContent content, ArrayAdapter::ArrayType arrayType,
                         unsigned elementSize, const std::shared_ptr<ArrayDecorator>& arrayDecorator)
{
   if(attribIndex>=_attribs.size())
      _attribs.resize(attribIndex+1);

   _attribs[attribIndex].content=content;
   _attribs[attribIndex].array.set(arrayDecorator,arrayType,elementSize);
}


uint16_t Mesh::getArraysConfigID()
{
   if(!_cpuGeometryDataAvailable)
      return 0;

   uint16_t r=0;
   ArrayAdapter::ArrayType t;

   // coordinates
   //
   // Coordinates have to be specified and they have to use attribute index 0,
   // otherwise we do not provide valid configID (zero is returned).
   // If there is not valid configID, use getArraysFullConfig().
   //
   // Coordinates occupies bits 0 and 1 of the returned integer.
   if(_coordinateAttribIndex!=0)
      return 0;
   t=_attribs[_coordinateAttribIndex].array.getType();
   if(t==ArrayAdapter::ArrayType::Vec3)  r|=0x1;
   else if(t==ArrayAdapter::ArrayType::Vec4)  r|=0x2;
   else if(t==ArrayAdapter::ArrayType::Vec2)  r|=0x3;
   else return 0;

   // normals
   //
   // Normals are not mandatory. If they are specified, they have to use attribute index 1.
   // otherwise this method does not provide valid configID (zero is returned).
   // If there is not valid configID, use getArraysFullConfig().
   //
   // Normals occupies bits 2 and 3 of the returned integer.
   int8_t lastAttribIndex;
   if(_normalAttribIndex!=-1)
   {
      if(_normalAttribIndex!=1)
         return 0;
      t=_attribs[_normalAttribIndex].array.getType();
      if(t==ArrayAdapter::ArrayType::Empty);
      else if(t==ArrayAdapter::ArrayType::Vec3)  r|=0x4;
      else if(t==ArrayAdapter::ArrayType::HVec3)  r|=0x8;
      else return 0;
      lastAttribIndex=1;
   }
   else
      lastAttribIndex=0;

   // color
   //
   // Colors are not mandatory. If they are specified, they have to use attribute index 1 or 2.
   // Index 1 must be used if there are no normals, index 2 must be used when normals are in use.
   // Otherwise, this method does not provide valid configID (zero is returned).
   // If there is not valid configID, use getArraysFullConfig().
   //
   // Color occupies bits 4,5 and 6 of the returned integer.
   if(_colorAttribIndex!=-1)
   {
      lastAttribIndex++;
      if(_colorAttribIndex!=lastAttribIndex)
         return 0;
      t=_attribs[_colorAttribIndex].array.getType();
      if(t==ArrayAdapter::ArrayType::Empty);
      else if(t==ArrayAdapter::ArrayType::Vec3)  r|=0x10;
      else if(t==ArrayAdapter::ArrayType::Vec4)  r|=0x20;
      else if(t==ArrayAdapter::ArrayType::HVec3)  r|=0x30;
      else if(t==ArrayAdapter::ArrayType::HVec4)  r|=0x40;
      else if(t==ArrayAdapter::ArrayType::UBVec3)  r|=0x50;
      else if(t==ArrayAdapter::ArrayType::UBVec4)  r|=0x60;
      //else if(t==ArrayAdapter::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8,1)  r|=0x1c0;
      //else if(t==ArrayAdapter::makeType(ArrayAdapter::GLType::UNSIGNED_INT_8_8_8_8_REV,1)  r|=0x200;
      //else if(t==ArrayAdapter::makeType(ArrayAdapter::GLType::UNSIGNED_BYTE,ArrayAdapter::BGRA)  r|=0x240;
      else return 0;
   }

   // texCoords
   //
   // Texture coordinates are not mandatory. If they are specified, they have to use attribute index 1,2 or 3.
   // Index 1 must be used if there are no normals and no colors.
   // Index 2 must be used if either normals or color are in use (not both).
   // Index 3 must be used if normals and colors are used (both).
   // In other cases, this method does not provide valid configID (zero is returned).
   // If there is not valid configID, use getArraysFullConfig().
   //
   // TexCoords occupies bits 8 and 9 of the returned integer.
   if(_texCoordAttribIndex!=-1)
   {
      lastAttribIndex++;
      if(_texCoordAttribIndex==lastAttribIndex)
         return 0;
      t=_attribs[_texCoordAttribIndex].array.getType();
      if(t==ArrayAdapter::ArrayType::Empty);
      else if(t==ArrayAdapter::ArrayType::Vec2)  r|=0x100;
      else if(t==ArrayAdapter::ArrayType::HVec2)  r|=0x200;
      else return 0;
   }

   // indices
   //
   // Indices are optional. If they are used, they have to use UInt type (UNSIGNED_INT).
   //
   // Indices occupies bit 10 of the returned integer.
   t=_indices.getType();
   if(t==ArrayAdapter::ArrayType::UInt)  r|=0x400;

   return r;
}
