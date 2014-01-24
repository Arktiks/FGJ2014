#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"

class Draw
{
public:
	Draw();
	~Draw(void);

	void Update(sf::RenderWindow& _window, sf::Vector2f player_pos);

private:
	sf::Texture texture;
	int Load_Image(char _fname[20]);
	
	void Load_Sprites();

	sf::Sprite player_sprite;
	Player player;
};