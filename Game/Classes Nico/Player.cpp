#include "Player.h"
#include "Input.h"

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
	if(Input::Hold_Key(sf::Keyboard::D) && pos.x+1 < 1024 - 100)
	{
		pos.x += 0.5f;
		std::cout<< "D \n";
	}

	if(Input::Hold_Key(sf::Keyboard::A) && pos.x-1 > 0)
	{
		pos.x -= 0.5f;
		std::cout<< "A \n";
	}
	if(Input::Hold_Key(sf::Keyboard::S) && pos.y+1 < 576 - 200)
	{
		pos.y += 0.5f;
		std::cout<< "S \n";
	}
	if(Input::Hold_Key(sf::Keyboard::W) && pos.y-1 > 0)
	{
		pos.y -= 0.5f;
		std::cout<< "W \n";
	}

}
