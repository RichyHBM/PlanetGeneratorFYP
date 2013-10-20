#ifndef UTILITIES_HPP
#define UTILITIES_HPP

//Macro define to be able to use PrintGLErrors without having to specify line numbers and filenames
#define PrintGLErrors() PrintGLErrorsFromLine( __FILE__, __LINE__)

#include "./Includes.hpp"
#include <ctime>
#include <iomanip>

namespace Util
{
    //Prints all openGL errors since last call
    void PrintGLErrorsFromLine( const char *file, int line );

    //Returns the modification time of a file
    time_t GetModificationTime( const std::string &filename );

    //Returns a string in the desired format representing local date/time
    std::string GetLocalDateTime( const std::string &format = "%Y-%m-%d_%H-%M-%S" );

    namespace Maths
    {
        //Pi in float form
        const static float fPI = 3.14159265358979323846f;

        //Half of Pi in float form
        const static float fPIo2 = 3.14159265358979323846f / 2.0f;

        //Quater of Pi in float form
        const static float fPIo4 = 3.14159265358979323846f / 4.0f;

        //Pi in double form
        const static double dPI = 3.14159265358979323846;

        //Half of Pi in double form
        const static double dPIo2 = 3.14159265358979323846 / 2.0;

        //Quater of Pi in double form
        const static double dPIo4 = 3.14159265358979323846 / 4.0;
    }

    //Returns the largest of 2 values
    template <class T>
    T MaxValue( T pA, T pB )
    {
        if( pA > pB ) {
            return pA;

        } else {
            return pB;
        }
    }

    //Returns the smallest of 2 values
    template <class T>
    T MinValue( T pA, T pB )
    {
        if( pA > pB ) {
            return pB;

        } else {
            return pA;
        }
    }

    //Clamps input to a given value
    template <class T>
    T Clamp( T val, T min, T max )
    {
        if( val > max ) {
            return max;

        } else if( val < min ) {
            return min;

        } else {
            return val;
        }
    }

    //Convert a given variable into a string
    template <class T>
    inline std::string ToString ( const T &t )
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    inline std::string ToString ( float f, int precision )
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision( precision ) << f;
        return ss.str();
    }

}

#endif // UTILITIES_HPP
