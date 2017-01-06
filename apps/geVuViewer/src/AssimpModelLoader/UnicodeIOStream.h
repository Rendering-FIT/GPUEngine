#pragma once

#include <assimp/IOStream.hpp>

class UnicodeIOStream : public Assimp::IOStream
{
   friend class UnicodeIOSystem;

   UnicodeIOStream();
#ifdef _WIN32
   UnicodeIOStream(FILE* pFile, const std::wstring &strFilename);
#else
   UnicodeIOStream(FILE* pFile, const std::string &strFilename);
#endif
public:
   virtual ~UnicodeIOStream();
   // -------------------------------------------------------------------
   /** @brief Read from the file
   *
   * See fread() for more details
   * This fails for write-only files */
   virtual size_t Read(void* pvBuffer,
      size_t pSize,
      size_t pCount) override;

   // -------------------------------------------------------------------
   /** @brief Write to the file
   *
   * See fwrite() for more details
   * This fails for read-only files */
   virtual size_t Write(const void* pvBuffer,
      size_t pSize,
      size_t pCount) override;

   // -------------------------------------------------------------------
   /** @brief Set the read/write cursor of the file
   *
   * Note that the offset is _negative_ for aiOrigin_END.
   * See fseek() for more details */
   virtual aiReturn Seek(size_t pOffset,
      aiOrigin pOrigin) override;

   // -------------------------------------------------------------------
   /** @brief Get the current position of the read/write cursor
   *
   * See ftell() for more details */
   virtual size_t Tell() const override;

   // -------------------------------------------------------------------
   /**	@brief Returns filesize
   *	Returns the filesize. */
   virtual size_t FileSize() const override;

   // -------------------------------------------------------------------
   /**	@brief Flush the contents of the file buffer (for writers)
   *	See fflush() for more details.
   */
   virtual void Flush() override;

private:
   //!	File data structure, using climb
   FILE* mFile;
   //!	Filename
#ifdef _WIN32
   std::wstring	mFilename;
#else
   std::string	mFilename;
#endif

   //! Cached file size
   mutable size_t cachedSize;
};