#include <UnicodeIOSystem.h>

#include <UnicodeIOStream.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace Assimp;

bool UnicodeIOSystem::Exists(const char* pFile) const
{
   int size = (int)strlen(pFile);
   int destLen = MultiByteToWideChar(CP_UTF8, 0, pFile, size, 0, 0);
   std::wstring wFilename(destLen, L'\0');
   destLen = MultiByteToWideChar(CP_UTF8, 0, pFile, size, &wFilename[0], destLen);
   FILE* file;
   errno_t err;
   err = ::_wfopen_s(&file, wFilename.c_str(), L"rb");
   if(err !=0 )
      return false;

   ::fclose(file);
   return true;
}

IOStream* UnicodeIOSystem::Open(const char* strFile, const char* strMode)
{

   int size = (int)strlen(strFile);
   int destLen = MultiByteToWideChar(CP_UTF8, 0, strFile, size, 0, 0);
   std::wstring wFilename(destLen, L'\0');
   destLen = MultiByteToWideChar(CP_UTF8, 0, strFile, size, &wFilename[0], destLen);
   FILE* file;
   errno_t err;
   err = ::_wfopen_s(&file, wFilename.c_str(), L"rb");
   if(err != 0)
      return NULL;

   return new UnicodeIOStream(file, (std::wstring) wFilename);
}

char UnicodeIOSystem::getOsSeparator() const
{
   return '\\';
}

void UnicodeIOSystem::Close(IOStream* pFile)
{
   delete pFile;
}