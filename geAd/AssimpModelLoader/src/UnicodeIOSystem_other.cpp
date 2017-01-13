#include <UnicodeIOSystem.h>

#include <UnicodeIOStream.h>

using namespace Assimp;

bool UnicodeIOSystem::Exists(const char* pFile) const
{
   FILE* file = ::fopen(pFile, "rb");
   if(!file)
      return false;

   ::fclose(file);
   return true;
}

// ------------------------------------------------------------------------------------------------
// Open a new file with a given path.
IOStream* UnicodeIOSystem::Open(const char* strFile, const char* strMode)
{
   FILE* file = ::fopen(strFile, strMode);
   if(NULL == file)
      return NULL;

   return new UnicodeIOStream(file, (std::string) strFile);
}

// ------------------------------------------------------------------------------------------------
// Closes the given file and releases all resources associated with it.
void UnicodeIOSystem::Close(IOStream* pFile)
{
   delete pFile;
}

// ------------------------------------------------------------------------------------------------
// Returns the operation specific directory separator
char UnicodeIOSystem::getOsSeparator() const
{
   return '/';
}