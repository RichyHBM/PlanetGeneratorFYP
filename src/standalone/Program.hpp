#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "framework/Debugs/DrawDebugInfo.hpp"
#include "framework/Window/Window.hpp"

#include "framework/GLHelp/GLHelp.hpp"

#include "framework/Geometry/RoundedCube.hpp"
#include "framework/Physics/Frustrum.hpp"

#include <AntTweakBar.h>

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

    //Callbacks for the GUI controls
    static void TW_CALL QuitButton( void *clientData );
    static void TW_CALL RebuildButton( void *clientData );
    static void TW_CALL GetSeed( void *value, void *clientData );
    static void TW_CALL SetSeed( const void *value, void *clientData );
    static void TW_CALL GetDistortions( void *value, void *clientData );
    static void TW_CALL SetDistortions( const void *value, void *clientData );
    static void TW_CALL GetLightDirection( void *value, void *clientData );
    static void TW_CALL SetLightDirection( const void *value, void *clientData );

    DrawDebugInfo *GetDebugInfo();
    RoundedCube *GetRoundedCube();
    Window *GetWindow();


protected:
    Frustrum mFrustrum;
    Window *mWindow;
    DrawDebugInfo mDebugInfo;
    RoundedCube mRoundedCube;
private:
};

#endif // PROGRAM_HPP
