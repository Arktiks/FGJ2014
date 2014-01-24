#include "bullet.h"


bullet::bullet(sf::Vector2f player_pos)
{
	pos = player_pos;
}


bullet::~bullet(void)
{
}

void bullet::Update()
{
	pos.y -= 0.1f;
}