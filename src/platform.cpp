#include "platform.h"


namespace Log
{

static void*            g_hLogFile = nullptr;
static timeMs_t         g_startTimeMs = 0;
static sf::Mutex        g_logMutex;
static sf::Clock        g_logClock;

void write(const char* szFmt, ...)
{
    g_logMutex.lock();
    unsigned int iTicks = g_logClock.getElapsedTime().asMilliseconds(); - g_startTimeMs;
    unsigned int iSecs = iTicks / 1000;
    unsigned int iMSecs = iTicks % 1000;
    unsigned int iMins = iSecs / 60;
    unsigned int iHrs = iMins / 60;
    iSecs %= 60;
    iMins %= 60;
    printf("%02i:%02i:%02i,%03i ", iHrs, iMins, iSecs, iMSecs);

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
        snprintf( szTmp, sizeof( szTmp ), "%i:%02i:%02i,%03i\t", iHrs, iMins, iSecs, iMSecs );
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
    g_startTimeMs = g_logClock.getElapsedTime().asMilliseconds();
    g_hLogFile = File::open(szFilename, "w+");
    g_logMutex.unlock();
}

}

namespace File
{


void* open(const char* szName, const char* szMode)
{
    if (szName)
        return fopen(szName, szMode);
    else
        return nullptr;
}

void close(void* hFile)
{
    fclose((FILE*)hFile);
}

bool seek(void* hFile, int iOffset, int iFrom)
{
    return !fseek((FILE*)hFile, (long)iOffset, iFrom);
}

size_t size(void* hFile)
{
    long iCurrentPos = ftell((FILE*)hFile);
    seek(hFile, 0, SEEK_END);
    long iSize = ftell((FILE*)hFile);
    seek(hFile, iCurrentPos, SEEK_SET);
    return iSize;
}

bool write(void* hFile, const void* pBuffer, size_t iSize)
{
    size_t iWritten = fwrite( pBuffer, 1, iSize, ( FILE* )hFile );
    return iWritten == iSize;
}

bool read(void* hFile, void* pBuffer, size_t iSize)
{
    size_t iRead = fread( pBuffer, 1, iSize, (FILE*)hFile );
    return iRead == iSize;
}

void flush(void* hFile)
{
    fflush((FILE*)hFile);
}

bool remove(const char* szFile)
{
    return !::remove( szFile );
}

const char* getNameExt(const char* szFullName)
{
    if( !szFullName )
        return nullptr;

    intptr_t iLen = (intptr_t)strlen( szFullName );
    while( iLen >= 0 && szFullName[ iLen ] != '\\' && szFullName[ iLen ] != '/' )
        iLen--;

    return ( iLen >= 0 ) ? &szFullName[ iLen + 1 ] : szFullName;
}

const char* getExt(const char* szFullName)
{
    intptr_t iLen = ( intptr_t )strlen( szFullName );
    while( iLen >= 0 && szFullName[ iLen ] != '\\' && szFullName[ iLen ] != '/' && szFullName[ iLen ] != '.' )
        iLen--;

    return ( iLen >= 0 ) ? &szFullName[ iLen + 1 ] : "";
}

bool getName(const char* szFullName, char* szName, size_t iSize)
{
    if( !szFullName || !iSize )
    {
        szName[ 0 ] = 0;
        return false;
    }

    const char* szNameExt = getNameExt(szFullName);
    size_t i = 0;
    while( szNameExt[ i ] && szNameExt[ i ] != '.' )
        i++;

    if( i >= iSize )
    {
        szName[ 0 ]	= 0;
        return false;
    }

    memcpy( szName, szNameExt, i );
    szName[ i ]	= 0;
    return true;
}

bool getPath(const char* szFullName, char* szPath, size_t iSize)
{
    const char* szNameExt = getNameExt( szFullName );
    size_t iPathSize = szNameExt - szFullName;

    if( iPathSize >= iSize )
    {
        szPath[ 0 ]	= 0;
        return false;
    }

    memcpy( szPath, szFullName, iPathSize );
    szPath[ iPathSize ] = 0;
    return true;
}

bool isFullPath( const char* szPath )
{
#ifdef	PLATFORM_WIN
    return szPath && szPath[ 1 ] == ':';
#else	// PLATFORM_WIN
    return szPath && szPath[ 0 ] == '/';
#endif	// PLATFORM_WIN
}

void appendExt(char* szFullName, const char* szExt)
{
    size_t iExt = strlen( szExt );
    if( szExt[ 0 ] == '.' )
    {
        szExt++;
        iExt--;
    }
    if( !iExt )
        return;

    size_t iFile = strlen( szFullName );
    if( iFile && szFullName[ iFile - 1 ] == '.' )
        szFullName[ --iFile ] = 0;

    if( iFile > iExt )
    {
        char S[ 256 ];
        char S2[ 64 ];
        S2[ 0 ] = '.';
        if( !strcmp( S, S2 ) )
            return;
    }
    strcat( szFullName, "." );
    strcat( szFullName, szExt );
}

}
