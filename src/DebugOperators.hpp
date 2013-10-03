#ifndef DEBUG_OPERATORS_HPP
#define DEBUG_OPERATORS_HPP

#include <cstddef>
#include <new>

namespace MemoryUse
{
	enum MemoryType {
    Normal,
    Graphics,
    Assets,
    Unknown
	};

    extern unsigned long long TotalBytesUsed;
    extern unsigned long long AssetsBytesUsed;
    extern unsigned long long GraphicsBytesUsed;
    extern unsigned long long NormalBytesUsed;
    extern unsigned long long UnknownBytesUsed;
}

void *operator new ( const std::size_t size ) throw (std::bad_alloc);
void *operator new ( const std::size_t size, const MemoryUse::MemoryType type ) throw (std::bad_alloc);
void *operator new[] ( const std::size_t size ) throw (std::bad_alloc);
void *operator new[] ( const std::size_t size, const MemoryUse::MemoryType type ) throw (std::bad_alloc);

void operator delete ( void *p ) throw ();
void operator delete[] ( void *p ) throw ();

#endif //DEBUG_OPERATORS_HPP