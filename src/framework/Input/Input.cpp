#include "Input.hpp"
#include "../LogManager.hpp"

Input Input::Manager;

Input::Input() : mType(KEYBOARD)
{
}
Input::~Input()
{
}

void Input::SetType( Type t )
{
	if(t == GAMEPAD && !Gamepad::IsAnyGamepadConnected())
	{
		return;
	}
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