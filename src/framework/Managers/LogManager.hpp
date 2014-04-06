#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

//Use template functions to allow logging anything
class LogManager
{
public:
    template <class T>
    void Info( const T &t ) {
        LogToBoth( t, LIGHTCYAN, "[INFO]" );
    }

    template <class T>
    void Success( const T &t ) {
        ChangeColor( LIGHTGREEN );
        std::cout << std::left << std::setw( mTagWidth ) << "[SUCCESS]" << t << std::endl;
        ChangeColor( WHITE );
    }

    template <class T>
    void Warning( const T &t ) {
        LogToBoth( t, YELLOW, "[WARNING]" );
    }

    template <class T>
    void Error( const T &t ) {
        LogToBoth( t, LIGHTRED, "[ERROR]" );
    }

    LogManager();
    ~LogManager();

protected:
    //std::ofstream mFileStream;
    void ChangeColor( int color );
    int mTagWidth;

    template <class T>
    void LogToBoth( const T &t, int color, const std::string &s ) {
        //Set the custom colour, print to console and set colour back
        ChangeColor( color );
        std::cout << std::left << std::setw( mTagWidth ) << s << t << std::endl;
        ChangeColor( WHITE );
        //If the file is open, print to file
        //if( mFileStream.is_open() ) {
        //    mFileStream << std::left << std::setw( mTagWidth ) << s << t << std::endl;
        //}
    }

    enum Color {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        GREY,
        DARKGREY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE
    };
};

static LogManager Log;

#endif