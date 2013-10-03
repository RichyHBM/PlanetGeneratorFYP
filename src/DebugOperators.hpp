#ifndef DEBUG_OPERATORS_HPP
#define DEBUG_OPERATORS_HPP

#ifndef __linux__
#include <cstddef>

enum MemoryType {
    Normal,
    Graphics,
    Assets,
    Unknown
};

namespace MemoryUse
{
    extern unsigned long long TotalBytesUsed;
    extern unsigned long long AssetsBytesUsed;
    extern unsigned long long GraphicsBytesUsed;
    extern unsigned long long NormalBytesUsed;
    extern unsigned long long UnknownBytesUsed;
}

void *operator new ( const std::size_t size );
void *operator new ( const std::size_t size, const MemoryType type );
void *operator new[] ( const std::size_t size );
void *operator new[] ( const std::size_t size, const MemoryType type );

void operator delete ( void *p );
void operator delete[] ( void *p );

#endif
#endif //DEBUG_OPERATORS_HPP