#ifndef INPUT_HPP
#define INPUT_HPP

#include "./Keyboard.hpp"
#include "./Gamepad.hpp"

class Input
{
public:
    enum Type {
        KEYBOARD,
        GAMEPAD
    };

    Input();
    ~Input();

    void SetType( Type t );
    void Update();

    static Input Manager;
protected:
    Type mType;
    Keyboard mKeyboard;
    Gamepad mGamepad;
};

#endif //INPUT_HPP