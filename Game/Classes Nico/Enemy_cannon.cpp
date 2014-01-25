#include "Enemy_cannon.h"
#include <random>
#include <time.h>

Enemy_cannon::Enemy_cannon(float pos_x, float pos_y)
{
	pos.x = 0, pos.y = -200;

	collison_pox.left = pos.x+20, collison_pox.top = pos.y;
	collison_pox.height = 100, collison_pox.width = 136; 

	hit = false;
}


Enemy_cannon::~Enemy_cannon(void)
{
}

void Enemy_cannon::Update()
{
	
	time = clock.getElapsedTime();

	if(time > sf::Time(sf::seconds(2)))
	{
		shoot = true;
		cannonballs.push_back(Cannonball(sf::Vector2f(pos.x + 68, pos.y + 100)));
		clock.restart();
	}
	else
	{
		shoot == false;
	}
	for(int i = 0; i < cannonballs.size(); i++)
	{
		if(cannonballs[i].pos.y > 576)
		{
			cannonballs.erase(cannonballs.begin() + i);
		}
	}
	pos.y += 0.01;
	collison_pox.left = pos.x;
	collison_pox.top = pos.y;
}


