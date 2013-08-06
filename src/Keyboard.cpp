

#include "Keyboard.hpp"


KeyBoard::Keyboard::Keyboard()
{
    for( int i = 0; i < GLFW_KEY_LAST; i++ ) {
        mKeys[i] = false;
        mPrevK[i] = false;
    }
}

KeyBoard::Keyboard::~Keyboard()
{
    //dtor
}

/*void KeyBoard::SetCallBack(int key, int state)
{
    if(key >= GLFW_KEY_LAST) return;
    if(state == GLFW_PRESS)
        KeyBoard::keyboard.keys[key] = true;
    else if(state == GLFW_RELEASE)
        KeyBoard::keyboard.keys[key] = false;
}*/

bool KeyBoard::Keyboard::IsKeyPressed( int pKey )
{
    return mKeys[pKey];
}

KeyBoard::KeyChange KeyBoard::Keyboard::HasKeyChanged( int pKey )
{
    if( ( mPrevK[pKey] == false ) && ( mKeys[pKey] == true ) ) {
        return Pressed;
    }

    if( ( mPrevK[pKey] == true ) && ( mKeys[pKey] == false ) ) {
        return Released;
    }

    return Nothing;
}

bool KeyBoard::Keyboard::HasKeyBeenPressed( int pKey )
{
    if( ( mPrevK[pKey] == false ) && ( mKeys[pKey] == true ) ) {
        return true;
    }

    return false;
}

void KeyBoard::Keyboard::Update( GLFWwindow *window )
{
    for( int i = 0; i < GLFW_KEY_LAST; i++ ) {
        mPrevK[i] = mKeys[i];

        if( glfwGetKey( window, i ) == GLFW_PRESS ) {
            mKeys[i] = true;

        } else {
            mKeys[i] = false;
        }
    }
}
