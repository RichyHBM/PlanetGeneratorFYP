#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "../Includes.hpp"

class Mouse
{
public:
    static void Set( float x, float y );
    static glm::vec2 GetDisplacement();
};

#endif