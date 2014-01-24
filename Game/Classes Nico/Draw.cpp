#include "Draw.h"


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
	player_sprite.setTexture(texture), player_sprite.setTextureRect(sf::IntRect(0,0,100,200));
}

void Draw::Update(sf::RenderWindow& _window, sf::Vector2f player_pos)
{
	_window.clear(sf::Color(150,150,150));//Clears the window for drawing

	_window.draw(player_sprite);
	player_sprite.setPosition(player_pos.x,player_pos.y);

	_window.display();//Draws object to screen
}

int Draw::Load_Image(char _fname[20])
{
		if(!texture.loadFromFile(_fname))//Try to load set image, return -1 upon failure 
		return -1;
}