#include "Input.hpp"
#include "../Managers/LogManager.hpp"

Input Input::Manager;

Input::Input() : mType( KEYBOARD )
{
}
Input::~Input()
{
}

void Input::SetType( Type t )
{
    mType = t;
}

void Input::Update()
{
    switch( mType ) {
        case KEYBOARD:
            mKeyboard.Update();
            break;
        case GAMEPAD:
            mGamepad.Update();
            break;
        case NETWORK:
            mNetworked.Update();
            break;
        default:
            Log.Warning( "No Input Selected" );
    }
}