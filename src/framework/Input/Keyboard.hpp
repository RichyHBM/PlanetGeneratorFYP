#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

class Keyboard
{
    double mHorizontalAngle;
    double mVerticalAngle;
public:
    Keyboard();
    ~Keyboard();
    //Update the keyboard to check for movement
    void Update();
};

#endif //KEYBOARD_HPP