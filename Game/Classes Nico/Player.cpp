#include "Player.h"

#include <iostream>


Player::Player(void)
{
	pos.x = 465, pos.y = 576 -173;
	collison_pox.left = pos.x + 40, collison_pox.top = pos.y+60;
	collison_pox.height = 173-40, collison_pox.width = 98-20;
	Alive = true;
}


Player::~Player(void)
{
}



void Player::Update()
{
	
	if(Input::Hold_Key(sf::Keyboard::D) && pos.x+1 < 1024 - 75)
	{
		pos.x += 0.1f;
	}

	if(Input::Hold_Key(sf::Keyboard::A) && pos.x-1 > 0)
	{
		pos.x -= 0.1f;
	}
	if(Input::Hold_Key(sf::Keyboard::S) && pos.y+1 < 576 - 128)
	{
		pos.y += 0.1f;
	}
	if(Input::Hold_Key(sf::Keyboard::W) && pos.y-1 > 0)
	{
		pos.y -= 0.1f;
	}
	collison_pox.left = pos.x;
	collison_pox.top = pos.y;

	//Shooting
	if(Input::Hold_Key(sf::Keyboard::Space) && clock.getElapsedTime() > sf::milliseconds(200))
	{
		Bullets.push_back(bullet(pos));
		clock.restart();
	}

	if(!Bullets.empty())
	{
		for(int i = 0; i < Bullets.size(); i++)
		{
			if(Bullets[i].hit == false)
			{
				Bullets[i].Update();
			}
			if(Bullets[i].pos.y < -100 || Bullets[i].hit == true)
			{
				Bullets.erase(Bullets.begin() +i);
				std::cout<<"out of bounds \n";
				i--;
			}
		}
	}
	
}

void Player::erase_bullet(int i)
{
	Bullets[i].setHit();
}
