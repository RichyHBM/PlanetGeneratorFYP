#ifndef INPUT_HPP
#define INPUT_HPP

#include "Keyboard.hpp"

class Input
{
public:
	Input();
	~Input();

	enum Type{
		KEYBOARD,
		GAMEPAD,
		NETWORK
	};

	void SetType(Type t);
	void Update();

	static Input Manager;
protected:
	Type mType;
	Keyboard mKeyboard;
};

#endif //INPUT_HPP