#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Enemy_cannon.h"
#include "Cannonball.h"
#include <deque>

class Draw
{
public:
	Draw();
	~Draw(void);

	void Update(sf::RenderWindow& _window, sf::Vector2f player_pos, Player& player);

private:
	sf::Texture texture;
	int Load_Image(char _fname[20]);
	
	void Load_Sprites();
	
	sf::Sprite player_sprite, bullet_sprite;
	
	//Enemy
	sf::Sprite cannon_sprite, cannonball_sprite;

	//Text
	sf::Sprite Game_Over;

	//Enemy_cannon cannon;
	std::deque<Enemy_cannon> cannons;
	

	//Background
	sf::Sprite house_sprite, house_sprite2, house_sprite3, house_sprite4;

	sf::Clock clock, enemy_timer;
	sf::Time time, time2;

	sf::RectangleShape baground_shape;
	sf::Vector2f b_loc, b_size;
	bool restart_game;

	int wave;
	bool b_max, b_pause;	
	void Draw_Baground(sf::RenderWindow& _window);
	void Draw_Enemy_formations();
};