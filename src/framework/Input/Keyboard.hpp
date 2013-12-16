#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

class Keyboard
{
    double mHorizontalAngle;
    double mVerticalAngle;
public:
    Keyboard();
    ~Keyboard();

    void Update();
};

#endif //KEYBOARD_HPP