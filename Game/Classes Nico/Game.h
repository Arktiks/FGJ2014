#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game(void);
	~Game(void);

	void Main_loop();

private:
	sf::RenderWindow main_window;

	void Greate_window();//Sets the values of the main window
	void Close_window();//Close the main window

	Player *player;
};

