#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Cannonball
{
public:
	Cannonball(sf::Vector2f cannon_pos);
	~Cannonball(void);

	void Update();
	sf::Vector2f pos;
	sf::FloatRect collison_pox;

};

