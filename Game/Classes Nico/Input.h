#pragma once
#include <SFML\Window\Keyboard.hpp>
class Input
{
public:
	Input(void);
	~Input(void);

	//Static syntacs == Input::Hold_Key NOT Input.Hold_Key
	static bool Hold_Key(sf::Keyboard::Key _key);//Hold key down
	bool Release_Key(sf::Keyboard::Key _key);
	bool Press_Key(sf::Keyboard::Key _key);
private:
	bool pressed[256], released[256];
};

