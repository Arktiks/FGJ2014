#include "Player.h"

#include <iostream>


Player::Player(void)
{
	pos.x = 0, pos.y = 0;
	
}


Player::~Player(void)
{
}



void Player::Update()
{
	
	if(Input::Hold_Key(sf::Keyboard::D) && pos.x+1 < 1024 - 75)
	{
		pos.x += 0.2f;
	}

	if(Input::Hold_Key(sf::Keyboard::A) && pos.x-1 > 0)
	{
		pos.x -= 0.2f;
	}
	if(Input::Hold_Key(sf::Keyboard::S) && pos.y+1 < 576 - 150)
	{
		pos.y += 0.2f;
	}
	if(Input::Hold_Key(sf::Keyboard::W) && pos.y-1 > -20)
	{
		pos.y -= 0.2f;
	}
	
	//Shooting
	if(Input::Hold_Key(sf::Keyboard::Space) && clock.getElapsedTime() > sf::milliseconds(75))
	{
		Bullets.push_back(bullet(pos));
		clock.restart();
	}

	if(!Bullets.empty())
	{
		for(int i = 0; i < Bullets.size(); i++)
		{
			Bullets[i].Update();
			if(Bullets[i].pos.y < -50)
			{
				Bullets.erase(Bullets.begin() +i);
				std::cout<<"out of bounds \n";
			}
		}
	}
	
}
