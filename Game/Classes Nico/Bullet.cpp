#include "bullet.h"


bullet::bullet(sf::Vector2f player_pos)
{
	pos = player_pos;
	collison_pox.left = pos.x, collison_pox.top = pos.y;
	collison_pox.height = 50, collison_pox.width = 15;
	hit = false;
}


bullet::~bullet(void)
{
}

void bullet::Update()
{
	pos.y -= 0.1f;
	collison_pox.left = pos.x;
	collison_pox.top = pos.y;
}

void bullet::setHit()
{
	hit = true;
}