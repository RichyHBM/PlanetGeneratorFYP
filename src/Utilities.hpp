#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "./Includes.hpp"

namespace Util{

///
///Prints all openGL errors since last call
///
void PrintGLErrors();

///
///Returns a string in the desired format representing local date/time
///
std::string GetLocalDateTime(const std::string &format = "%Y-%m-%d %H:%M:%S");

namespace Maths {
///
///Pi in float form
///
const static float fPI = 3.14159265358979323846f;
///
///Half of Pi in float form
///
const static float fPIo2 = 3.14159265358979323846f / 2.0f;
///
/// Quater of Pi in float form
///
const static float fPIo4 = 3.14159265358979323846f / 4.0f;

///
///Pi in float form
///
const static double dPI = 3.14159265358979323846;
///
///Half of Pi in float form
///
const static double dPIo2 = 3.14159265358979323846 / 2.0;
///
///Quater of Pi in float form
///
const static double dPIo4 = 3.14159265358979323846 / 4.0;
}

///
///Returns the largest of 2 values
///
template <class T>
T MaxValue(T pA, T pB)
{
    if(pA > pB) return pA;
    else return pB;
}

///
///Convert a given variable into a string
///
template <class T>
inline std::string ToString (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

}

#endif // UTILITIES_HPP
