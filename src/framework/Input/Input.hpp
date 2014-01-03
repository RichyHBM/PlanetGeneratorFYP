#ifndef INPUT_HPP
#define INPUT_HPP

#include "./Keyboard.hpp"
#include "./Gamepad.hpp"
#include "./Network.hpp"

class Input
{
public:
	enum Type {
        KEYBOARD,
        GAMEPAD,
        NETWORK
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
    NetworkInput mNetworked;
};

#endif //INPUT_HPP