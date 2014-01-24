#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "framework/DrawDebugInfo.hpp"
#include "framework/Window.hpp"

#include "framework/GLHelp/GLHelp.hpp"

#include "framework/Geometry/RoundedCube.hpp"
#include "framework/Physics/Frustrum.hpp"

class Program
{
public:


    ///
    ///Default constructor
    ///
    Program( Window *pWindow );

    ///
    ///Default destructor
    ///
    ~Program();

    ///
    ///Do certain input stuff here
    ///
    void HandleEvents();
    ///
    ///Handle game logic
    ///
    void Update();
    ///
    ///Draw stuff
    ///
    void Draw();

    ///
    ///Run method, does input handling, update and draw
    ///
    void Run();

    ///
    ///Get the delta amount in seconds, for 60fps this would be around 0.016
    ///
    const double GetDelta();

protected:
    Frustrum mFrustrum;
    Window *mWindow;
    DrawDebugInfo mDebugInfo;
    RoundedCube mRoundedCube;
private:
};

#endif // PROGRAM_HPP
