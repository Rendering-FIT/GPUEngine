#include <UnicodeIOStream.h>

#include <sys/types.h> 
#include <sys/stat.h> 

using namespace Assimp;
#ifdef _WIN32
inline UnicodeIOStream::UnicodeIOStream() :
mFile(NULL),
mFilename(L""),
cachedSize(SIZE_MAX)
{
   // empty
}


// ----------------------------------------------------------------------------------
UnicodeIOStream::UnicodeIOStream(FILE* pFile,
   const std::wstring &strFilename) :
   mFile(pFile),
   mFilename(strFilename),
   cachedSize(SIZE_MAX)
{
   // empty
}
#else
inline UnicodeIOStream::UnicodeIOStream() :
mFile(NULL),
mFilename(""),
cachedSize(SIZE_MAX)
{
   // empty
}


// ----------------------------------------------------------------------------------
UnicodeIOStream::UnicodeIOStream(FILE* pFile,
   const std::string &strFilename) :
   mFile(pFile),
   mFilename(strFilename),
   cachedSize(SIZE_MAX)
{
   // empty
}
#endif

UnicodeIOStream::~UnicodeIOStream()
{
   if(mFile) {
      ::fclose(mFile);
   }
}

size_t UnicodeIOStream::Read(void* pvBuffer,
   size_t pSize,
   size_t pCount)
{
   return (mFile ? ::fread(pvBuffer, pSize, pCount, mFile) : 0);
}

// ----------------------------------------------------------------------------------
size_t UnicodeIOStream::Write(const void* pvBuffer,
   size_t pSize,
   size_t pCount)
{
   return (mFile ? ::fwrite(pvBuffer, pSize, pCount, mFile) : 0);
}

// ----------------------------------------------------------------------------------
aiReturn UnicodeIOStream::Seek(size_t pOffset,
   aiOrigin pOrigin)
{
   if(!mFile) {
      return AI_FAILURE;
   }

   // do the seek
   return (0 == ::fseek(mFile, (long)pOffset, (int)pOrigin) ? AI_SUCCESS : AI_FAILURE);
}

// ----------------------------------------------------------------------------------
size_t UnicodeIOStream::Tell() const
{
   if(!mFile) {
      return 0;
   }
   return ::ftell(mFile);
}

// ----------------------------------------------------------------------------------
size_t UnicodeIOStream::FileSize() const
{
   if(!mFile || mFilename.empty()) {
      return 0;
   }

   if(SIZE_MAX == cachedSize) {

      // Although fseek/ftell would allow us to reuse the exising file handle here,
      // it is generally unsafe because:
      //  - For binary streams, it is not technically well-defined
      //  - For text files the results are meaningless
      // That's why we use the safer variant fstat here.
      //
      // See here for details:
      // https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+regular+file
#if defined _WIN32 && !defined __GNUC__
      struct __stat64 fileStat;
      int err = _wstat64(mFilename.c_str(), &fileStat);
      if(0 != err)
         return 0;
      cachedSize = (size_t)(fileStat.st_size);
#else
      struct stat fileStat;
      int err = stat(mFilename.c_str(), &fileStat);
      if(0 != err)
         return 0;
      cachedSize = (size_t)(fileStat.st_size);
#endif
   }
   return cachedSize;
}

// ----------------------------------------------------------------------------------
void UnicodeIOStream::Flush()
{
   if(mFile) {
      ::fflush(mFile);
   }
}
