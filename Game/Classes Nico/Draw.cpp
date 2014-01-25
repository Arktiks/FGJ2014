#include "Draw.h"
#include <iostream>

Draw::Draw()
{
	Load_Image("Jamm_text.png");
	Load_Sprites();
}


Draw::~Draw(void)
{
}

void Draw::Load_Sprites()
{
	player_sprite.setTexture(texture), player_sprite.setTextureRect(sf::IntRect(0,0,100,200)), player_sprite.scale(0.75f,0.75f);
	bullet_sprite.setTexture(texture), bullet_sprite.setTextureRect(sf::IntRect(100,0,50,50));

	bullet_sprite.setPosition(500,500);
}

void Draw::Update(sf::RenderWindow& _window, sf::Vector2f player_pos, Player player)
{
	_window.clear(sf::Color(150,150,150));//Clears the window for drawing

	//Player
	_window.draw(player_sprite);
	player_sprite.setPosition(player_pos.x,player_pos.y);
	
	//Shoot
	if(!player.Bullets.empty())
	{
		for(int i = 0; i < player.Bullets.size(); i++)
		{
			_window.draw(bullet_sprite);
			bullet_sprite.setPosition(player.Bullets[i].pos);
		}
	}

	_window.display();//Draws object to screen
}

int Draw::Load_Image(char _fname[20])
{
		if(!texture.loadFromFile(_fname))//Try to load set image, return -1 upon failure 
		return -1;
}