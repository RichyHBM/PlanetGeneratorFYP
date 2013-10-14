#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "framework/GLHelp/BitmapText.hpp"
#include "framework/Window.hpp"

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
    Window *mWindow;
    //BitmapText mBT;
private:
};

#endif // PROGRAM_HPP
