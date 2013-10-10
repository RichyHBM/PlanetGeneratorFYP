#include "./DebugOperators.hpp"
#ifndef NO_CUSTON_NEW_DELETE

#include <cstddef>
#include <cstdlib>
#include <new>
#include <iostream>

unsigned long long MemoryUse::TotalBytesUsed = 0;
unsigned long long MemoryUse::AssetsBytesUsed = 0;
unsigned long long MemoryUse::GraphicsBytesUsed = 0;
unsigned long long MemoryUse::NormalBytesUsed = 0;
unsigned long long MemoryUse::UnknownBytesUsed = 0;
static int magicNumber = 5551234;

struct MemoryChunk {
    int myCreation;
    std::size_t size;
    MemoryUse::MemoryType type;
};



//Overrides the new operator and adds the size of the variable to bytesUsed
void *operator new ( const std::size_t size, MemoryUse::MemoryType type ) throw ( std::bad_alloc )
{
    //create memory for the new object and the information header
    void *const p = std::malloc( sizeof( MemoryChunk ) + size );

    if( !p ) {
        throw std::bad_alloc();
    }

    //add the amount of memory to use to the bytesUsed
    MemoryUse::TotalBytesUsed += size;

    switch ( type ) {
        case MemoryUse::Normal:
            MemoryUse::NormalBytesUsed += size;
            break;

        case MemoryUse::Graphics:
            MemoryUse::GraphicsBytesUsed += size;
            break;

        case MemoryUse::Assets:
            MemoryUse::AssetsBytesUsed += size;
            break;

        case MemoryUse::Unknown:
        default:
            MemoryUse::UnknownBytesUsed += size;
            break;
    }

    //populate the header
    MemoryChunk *mc = ( MemoryChunk * )p;
    mc->myCreation = magicNumber;
    mc->size	  = size;
    mc->type = type;
    //return the location + the size of the header to not overwrite the header
    return mc + 1;
}

void *operator new[] ( const std::size_t size, MemoryUse::MemoryType type ) throw ( std::bad_alloc )
{
    return operator new( size, type );
}

void *operator new ( const std::size_t size ) throw ( std::bad_alloc )
{
    return operator new( size, MemoryUse::Unknown );
}

void *operator new[] ( const std::size_t size ) throw ( std::bad_alloc )
{
    return operator new( size, MemoryUse::Unknown );
}

void operator delete ( void *p ) throw ()
{
    if( !p ) {
        return;
    }

    MemoryChunk *mc = ( MemoryChunk * )p - 1;

    if( mc->myCreation == magicNumber ) {
        MemoryUse::TotalBytesUsed -= mc->size;

        switch ( mc->type ) {
            case MemoryUse::Normal:
                MemoryUse::NormalBytesUsed -= mc->size;
                break;

            case MemoryUse::Graphics:
                MemoryUse::GraphicsBytesUsed -= mc->size;
                break;

            case MemoryUse::Assets:
                MemoryUse::AssetsBytesUsed -= mc->size;
                break;

            case MemoryUse::Unknown:
            default:
                MemoryUse::UnknownBytesUsed -= mc->size;
                break;
        }

        std::free( mc );

    } else {
        //doesnt seem to have been created by me so just free it
        std::free( p );
    }

    p = NULL;
}

void operator delete[] ( void *const p ) throw ()
{
    delete( reinterpret_cast<char *const>( p ) );
}

#endif