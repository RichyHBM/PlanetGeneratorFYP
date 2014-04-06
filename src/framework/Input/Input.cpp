#include "Input.hpp"
#include "../Managers/LogManager.hpp"

Input Input::Manager;

//Set the keyboard to be the default input type
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

//Update the input accordingly
void Input::Update()
{
    switch( mType ) {
        case KEYBOARD:
            mKeyboard.Update();
            break;
        case GAMEPAD:
            mGamepad.Update();
            break;
        default:
            Log.Warning( "No Input Selected" );
    }
}