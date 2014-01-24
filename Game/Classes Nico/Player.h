#pragma once
#include <SFML\System.hpp>
class Player
{
public:
	Player(void);
	~Player(void);
	
	sf::Vector2f pos;

	void Update();
};

