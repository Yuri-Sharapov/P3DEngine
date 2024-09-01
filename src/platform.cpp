#include <cstdio>
#include <cstring>
#include <chrono>

#include "platform.h"

static sf::Clock g_mainClock;

timeMs_t millis(void)
{
    return g_mainClock.getElapsedTime().asMilliseconds();
}

timeUs_t micros(void)
{
    return g_mainClock.getElapsedTime().asMicroseconds();
}

timeUnix_t secs(void)
{
    return g_mainClock.getElapsedTime().asSeconds();
}

namespace Log
{

static void*            g_hLogFile = nullptr;
static sf::Mutex        g_logMutex;

void write(const char* szFmt, ...)
{
    g_logMutex.lock();
    int ticks = millis();
    int milliseconds = ticks % 1000;
    int secs = (ticks / 1000) % 60;
    int mins = (ticks / (1000 * 60)) % 60;
    int hours = (ticks / (1000 * 60 * 60)) % 24;


    printf("%02i:%02i:%02i,%03i ", hours, mins, secs, milliseconds);

    va_list args;
    va_start(args, szFmt);
    vprintf(szFmt, args);
    va_end(args);
    printf("\r\n");

    if (g_hLogFile)
    {
        char szBuf[ 1024 ];
        va_list ptr;
        va_start( ptr, szFmt );
        vsnprintf( szBuf, sizeof( szBuf ), szFmt, ptr );
        va_end( ptr );
        strcat( szBuf, "\n" );
        char szTmp[ 16 ];
        snprintf( szTmp, sizeof( szTmp ), "%02i:%02i:%02i,%03i\t", hours, mins, secs, milliseconds);
        size_t bytes = strlen( szTmp );
        File::write( g_hLogFile, &szTmp, bytes );
        bytes = strlen( szBuf );
        File::write( g_hLogFile, szBuf, bytes );
        File::flush(g_hLogFile);
    }
    g_logMutex.unlock();
}

void file(const char* szFilename)
{
    if (g_hLogFile)
        return;
    g_logMutex.lock();
    g_hLogFile = File::open(szFilename, "w+");
    g_logMutex.unlock();
}

}

namespace File
{

void* open(const char* szName, const char* szMode)
{
    if (szName)
        return std::fopen(szName, szMode);
    else
        return nullptr;
}

void close(void* hFile)
{
    std::fclose((FILE*)hFile);
}

bool seek(void* hFile, int iOffset, int iFrom)
{
    return !std::fseek((FILE*)hFile, (long)iOffset, iFrom);
}

size_t size(void* hFile)
{
    long iCurrentPos = std::ftell((FILE*)hFile);
    seek(hFile, 0, SEEK_END);
    long iSize = std::ftell((FILE*)hFile);
    seek(hFile, iCurrentPos, SEEK_SET);
    return iSize;
}

bool write(void* hFile, const void* pBuffer, size_t iSize)
{
    size_t iWritten = std::fwrite(pBuffer, 1, iSize, (FILE*)hFile);
    return iWritten == iSize;
}

bool read(void* hFile, void* pBuffer, size_t iSize)
{
    size_t iRead = std::fread(pBuffer, 1, iSize, (FILE*)hFile);
    return iRead == iSize;
}

void flush(void* hFile)
{
    std::fflush((FILE*)hFile);
}

bool remove(const char* szFile)
{
    return !std::remove(szFile);
}

const char* getNameExt(const char* szFullName)
{
    if( !szFullName )
        return nullptr;

    intptr_t len = (intptr_t)strlen( szFullName );
    while(len >= 0 && szFullName[len] != '\\' && szFullName[len] != '/' )
        len--;

    return (len >= 0) ? &szFullName[len + 1] : szFullName;
}

const char* getExt(const char* szFullName)
{
    intptr_t len = (intptr_t)strlen(szFullName);
    while(len >= 0 && szFullName[len] != '\\' && szFullName[len] != '/' && szFullName[len] != '.' )
        len--;

    return (len >= 0) ? &szFullName[len + 1] : "";
}

bool getName(const char* szFullName, char* szName, size_t size)
{
    if( !szFullName || !size)
    {
        szName[ 0 ] = 0;
        return false;
    }

    const char* szNameExt = getNameExt(szFullName);
    size_t i = 0;
    while(szNameExt[ i ] && szNameExt[ i ] != '.')
        i++;

    if(i >= size)
    {
        szName[ 0 ]	= 0;
        return false;
    }

    memcpy(szName, szNameExt, i);
    szName[ i ]	= 0;
    return true;
}

bool getPath(const char* szFullName, char* szPath, size_t size)
{
    const char* szNameExt = getNameExt( szFullName );
    size_t pathSize = szNameExt - szFullName;

    if(pathSize >= size)
    {
        szPath[ 0 ]	= 0;
        return false;
    }

    memcpy(szPath, szFullName, pathSize);
    szPath[pathSize] = 0;
    return true;
}

bool isFullPath( const char* szPath )
{
#ifdef	PLATFORM_WIN
    return szPath && szPath[ 1 ] == ':';
#else
    return szPath && szPath[ 0 ] == '/';
#endif
}

void appendExt(char* szFullName, const char* szExt)
{
    size_t extLen = strlen( szExt );
    if(extLen && szExt[0] == '.')
    {
        szExt++;
        extLen--;
    }
    if(extLen == 0)
        return;

    size_t nameLen = strlen(szFullName);
    if(nameLen && szFullName[nameLen - 1] == '.' )
        szFullName[--nameLen] = 0;

    strcat( szFullName, "." );
    strcat( szFullName, szExt );
}

}
