#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

class Gamepad
{
    double mHorizontalAngle;
    double mVerticalAngle;
public:
    Gamepad();
    ~Gamepad();

    void Update();
    static bool IsAnyGamepadConnected();
};

#endif //GAMEPAD_HPP