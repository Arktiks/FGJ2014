#include "Cannonball.h"


Cannonball::Cannonball(sf::Vector2f cannon_pos)
{
	pos = cannon_pos;
	collison_pox.left = pos.x, collison_pox.top = pos.y;
	collison_pox.height = 50, collison_pox.width = 15; 
}


Cannonball::~Cannonball(void)
{
}

void Cannonball::Update()
{
	pos.y += 0.18f;
	collison_pox.left = pos.x;
	collison_pox.top = pos.y;
}
