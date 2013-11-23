#include "Input.hpp"
#include "../LogManager.hpp"

Input Input::Manager;

Input::Input()
{

}
Input::~Input()
{

}

void Input::SetType(Type t)
{
	mType = t;
}

void Input::Update()
{
	switch(mType)
	{
	case KEYBOARD:
		mKeyboard.Update();
		break;
	case GAMEPAD:
		break;
	case NETWORK:
		break;
	default:
		Log.Warning("No Input Selected");
	}
}