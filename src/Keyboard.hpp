#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <GL/glfw.h>

namespace KeyBoard {

enum KeyChange {
    Pressed,
    Released,
    Nothing
};

class Keyboard
{
public:
    ///
    ///Default constructor
    ///
    Keyboard();
    ///
    ///Default destructor
    ///
    ~Keyboard();

    ///
    ///Update the keyboard class variables
    ///
    void Update();
    ///
    ///Check if a key is pressed
    ///
    bool IsKeyPressed(int pKey);
    ///
    ///Check if the current state of a key has changed
    ///
    KeyChange HasKeyChanged(int pKey);

    ///
    ///Check if the key has changed state since last check
    ///
    bool HasKeyBeenPressed(int pKey);
private:
    bool mKeys[GLFW_KEY_LAST];
    bool mPrevK[GLFW_KEY_LAST];
};

static Keyboard keyboard;

}

#endif // KEYBOARD_HPP
