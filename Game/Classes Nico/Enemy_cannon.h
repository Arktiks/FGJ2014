#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <deque>
#include "Cannonball.h"

class Enemy_cannon
{
public:
	Enemy_cannon(float pos_x, float pos_y);
	~Enemy_cannon(void);

	sf::Vector2f pos;
	sf::FloatRect collison_pox;

	void Update();
	bool hit, shoot;
	sf::Clock clock;
	sf::Time time;

	std::deque<Cannonball> cannonballs;
	
};

