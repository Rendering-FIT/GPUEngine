#pragma once

#include <assimp/IOSystem.hpp>

class UnicodeIOSystem : public Assimp::IOSystem
{
public:
   bool Exists(const char* pFile) const override;
   Assimp::IOStream* Open(const char* pFile, const char* pMode = "rb") override;
   virtual char getOsSeparator() const override;
   virtual void Close(Assimp::IOStream* pFile) override;
};