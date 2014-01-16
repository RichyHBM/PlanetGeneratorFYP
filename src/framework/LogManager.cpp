#include "LogManager.hpp"

#include "./Utilities.hpp"
#include <string>
#include "rlutil.h"

LogManager::LogManager()
{
    std::string filename = Util::GetLocalDateTime( "PlanetGen_log_%Y-%m-%d_%H-%M-%S.txt" );
    mFileStream.open( filename.c_str() );
    mTagWidth = 12;
}

LogManager::~LogManager()
{
    mFileStream.close();
}

void LogManager::ChangeColor( int color )
{
    //Dont change color for now
    //rlutil::setColor( color );
}
