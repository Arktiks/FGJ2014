#include "Input.h"



Input::Input(void)
{
}


Input::~Input(void)
{
}

bool Input::Hold_Key(sf::Keyboard::Key _key)
{
	return sf::Keyboard::isKeyPressed(_key);
}

bool Input::Press_Key(sf::Keyboard::Key _key)
{
	bool result = false;
	if(sf::Keyboard::isKeyPressed(_key) == true && pressed[_key] == false)
	{
		pressed[_key] = true;
		result = true;
	}

	if(sf::Keyboard::isKeyPressed(_key) == false && pressed[_key] == true)
	{
		pressed[_key] = false;
	}
	return result;
}

bool Input::Release_Key(sf::Keyboard::Key _key)
{
	bool result = false;

	if(sf::Keyboard::isKeyPressed(_key) == true)
	{
		released[_key] = true;
	}

	if(sf::Keyboard::isKeyPressed(_key) == false && released[_key] == true)
	{
		released[_key] = false;
		result = true;
	}
	return result;
}
