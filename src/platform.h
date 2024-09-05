#pragma once

#include <cstdarg>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// using namespace sf in all project
using namespace sf;

// platform definition
#if _WIN32 || _WIN64
#define	PLATFORM_WINDOWS
#endif
#if __GNUC__
#define	PLATFORM_LINUX
#endif

template<class T>
constexpr inline T ABS(const T& val)
{
    return ((val > (T)0) ? val : -val);
}

template<typename T>
constexpr inline T MIN(const T& one, const T& two)
{
    return one < two ? one : two;
}

template<typename T>
constexpr inline T MAX(const T& one, const T& two)
{
    return one > two ? one : two;
}

template<class T>
void inline SWAP(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

// own types
// millisecond time
typedef sf::Int32    timeMs_t;
// microsecond time
typedef sf::Int64    timeUs_t;
// seconds since Jan 1 1970
typedef sf::Uint64   timeUnix_t;

timeMs_t	millis(void);
timeUs_t	micros(void);
timeUnix_t  secs(void);

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

namespace Math
{

constexpr float PI = 3.141592653589793116f;

float rad2Deg(float rad);
float deg2Rad(float deg);

}