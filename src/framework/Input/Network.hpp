#ifndef NETWORK_HPP
#define NETWORK_HPP

class NetworkInput
{
    double mHorizontalAngle;
    double mVerticalAngle;
public:
    NetworkInput();
    ~NetworkInput();

    void Update();
};

#endif //NETWORK_HPP