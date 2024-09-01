#pragma once

#include <cstdio>
#include <cstdarg>
#include <cstring>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// own types
// millisecond time
typedef sf::Int32    timeMs_t;
// microsecond time
typedef sf::Int64    timeUs_t;
// seconds since Jan 1 1970
typedef sf::Uint64   timeUnix_t;

namespace Log
{
void write(const char* szFmt, ...);
void file(const char* szFilename);
}

namespace File
{
// file io
extern void*   open(const char* szName, const char* szMode);
extern void    close(void* hFile);
extern bool    write(void* hFile, const void* pBuffer, size_t size);
extern bool    read(void* hFile, void* pBuffer, size_t size);
extern bool    seek(void* hFile, int iOffset, int iFrom);
extern size_t  size(void* hFile);
extern void    flush(void* hFile);
extern bool    remove(const char* szPath);
// filename methods
extern const char* getNameExt(const char *szFullName);
extern const char* getExt(const char *szFullName);
extern bool        getPath(const char *szFullName, char *szPath, size_t size);
extern bool        isFullPath(const char *szPath);
extern bool        getName(const char *szFullName, char *szName, size_t size);
extern void        appendExt(char *szFullName, const char *szExt);
}