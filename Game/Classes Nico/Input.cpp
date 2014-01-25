#include "Input.h"



Input::Input(void)
{
	for(int i = 0; i < 256; i++)
	{
		pressed[i] = false;
		released[i] = false;
	}
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
	if(sf::Keyboard::isKeyPressed(_key) == true && pressed[_key] == false)//Tarkastaa että nappi on painettu ja ettei se ole aiemmin ollut painettu
	{
		pressed[_key] = true;//Merkitsee näppäimen painetuksi
		result = true;
	}

	if(sf::Keyboard::isKeyPressed(_key) == false && pressed[_key] == true)//Tarkastaa että näppäin on vapautettu
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
