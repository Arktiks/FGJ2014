#pragma once
#include <SFML\System.hpp>
#include "Input.h"
#include "bullet.h"
#include <deque>
#include <SFML\System\Time.hpp>

class Player
{
public:
	Player(void);
	~Player(void);
	
	sf::Vector2f pos;

	void Update();
	Input input;
	std::deque<bullet> Bullets;
	sf::Clock clock;
	sf::Time time;
};

