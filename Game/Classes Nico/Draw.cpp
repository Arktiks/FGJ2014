#include "Draw.h"
#include <iostream>


Draw::Draw()
{
	Load_Image("Jamm_text.png");
	Load_Sprites();
	b_max = false;
	wave = 0;
}


Draw::~Draw(void)
{
}

void Draw::Load_Sprites()
{
	player_sprite.setTexture(texture), player_sprite.setTextureRect(sf::IntRect(0,0,98,173)), player_sprite.scale(0.75f,0.75f);
	bullet_sprite.setTexture(texture), bullet_sprite.setTextureRect(sf::IntRect(110,0,11,50));

	bullet_sprite.setPosition(500,500);
	
	//Enemy
	cannon_sprite.setTexture(texture), cannon_sprite.setTextureRect(sf::IntRect(156,0,154,140));
	cannonball_sprite.setTexture(texture), cannonball_sprite.setTextureRect(sf::IntRect(320,0,23,24));
	
	//Background
	b_loc.x = 512-25, b_loc.y = -30, b_size.x = 50, b_size.y = 650;

	baground_shape.setPosition(b_loc.x,b_loc.y);
	baground_shape.setSize(b_size);
	baground_shape.setFillColor(sf::Color(100,100,100));

	house_sprite.setTexture(texture), house_sprite.setTextureRect(sf::IntRect(350,0,200,400));
	house_sprite.setPosition(0,-100);

	house_sprite2.setTexture(texture), house_sprite2.setTextureRect(sf::IntRect(350,0,200,400));
	house_sprite2.setPosition(900,-100);

	house_sprite3.setTexture(texture), house_sprite3.setTextureRect(sf::IntRect(350,0,200,400));
	house_sprite3.setPosition(0,-100);

	house_sprite4.setTexture(texture), house_sprite4.setTextureRect(sf::IntRect(350,0,200,400));
	house_sprite4.setPosition(900,-100);

	//Text
	Game_Over.setTexture(texture), Game_Over.setTextureRect(sf::IntRect(300,400,275,760)), Game_Over.setPosition(sf::Vector2f(360,250));
}

void Draw::Update(sf::RenderWindow& _window, sf::Vector2f player_pos, Player& player)
{
	if(player.Alive)
	{

	_window.clear(sf::Color(150,150,150));//Clears the window for drawing
	
		time2 = enemy_timer.getElapsedTime();
		time.asMilliseconds();

		//Background
		Draw_Baground(_window);

		player.Update();
	
		//Shoot
		if(!player.Bullets.empty())
		{
			for(int i = 0; i < player.Bullets.size(); i++)
			{
				if(player.Bullets[i].hit == false)
				{
					_window.draw(bullet_sprite);
					bullet_sprite.setPosition(player.Bullets[i].pos);
				}
			}
		}

		//Player
		player_sprite.setPosition(player_pos.x,player_pos.y);
		_window.draw(player_sprite);

		Draw_Enemy_formations();

		for(int i = 0; i < cannons.size(); i++)
		{
			cannons[i].Update();
			cannon_sprite.setPosition(cannons[i].pos);
			_window.draw(cannon_sprite);
	
			if(player.collison_pox.intersects(cannons[i].collison_pox))
			{
				player.Alive = false;
			}

			for(int z = 0; z < cannons[i].cannonballs.size(); z++)
			{
				cannons[i].cannonballs[z].Update();
				cannonball_sprite.setPosition(cannons[i].cannonballs[z].pos);
				_window.draw(cannonball_sprite);

				if(player.collison_pox.intersects(cannons[i].cannonballs[z].collison_pox))
				{
					player.Alive = false;
				}
			}

			for(int x = 0; x < player.Bullets.size(); x++)
			{
				if(player.Bullets[x].collison_pox.intersects(cannons[i].collison_pox))
				{
					
					std::cout<<"boing\n";
					cannons[i].hit = true;
					player.erase_bullet(x);
					//x--;
				}		
			}
		}
		for(int i = 0; i < cannons.size(); i++)
		{
			if(cannons[i].hit == true)
			{
				cannons.erase(cannons.begin() + i);
				std::cout<<"hit \n";
			}
		}
		for(int i = 0; i < cannons.size(); i++)
		{
			if(cannons[i].pos.y > 576)
			{
				cannons.erase(cannons.begin() +i);
			}
		}
	}
	if(player.Alive == false)
	{
		_window.clear(sf::Color::Red);
		_window.draw(Game_Over);
		if(player.input.Press_Key(sf::Keyboard::Space))
		{
			std::cout << "Press";
		}
	}

	_window.display();//Draws object to screen

}

int Draw::Load_Image(char _fname[20])
{
		if(!texture.loadFromFile(_fname))//Try to load set image, return -1 upon failure 
		return -1;
}

void Draw::Draw_Baground(sf::RenderWindow& _window)
{
	if(clock.getElapsedTime() > sf::seconds(22 + 15))
	{
		house_sprite.setPosition(0,-100);
		house_sprite2.setPosition(900,-100);
		house_sprite3.setPosition(0,-100);
		house_sprite4.setPosition(900,-100);
		clock.restart();
	}
	time = clock.getElapsedTime();

	_window.draw(baground_shape);

	if(b_size.x < 300)
	{
		b_max = false;
	}
	if(b_max == false && b_pause == false)
	{
		b_size.x += 0.01f;
		b_loc.x -= 0.005f;
	}

	if(b_size.x > 700)
	{
		b_max = true;
	}

	if(b_max == true && b_pause == false)
	{
		b_size.x -= 0.01f;
		b_loc.x += 0.005f;
	}

	baground_shape.setSize(b_size);
	baground_shape.setPosition(b_loc);

	if(time >= sf::seconds(5) && time <= sf::seconds(5+20))//1
	{
		house_sprite.move(0,0.01f);
		house_sprite.setScale(0.001f * b_size.x, 0.001f * b_size.x);
		_window.draw(house_sprite);
	}

	if(time >= sf::seconds(12) && time <= sf::seconds(12+20))//2
	{
		house_sprite2.move(0,0.01f);
		house_sprite2.setScale(0.001f * b_size.x, 0.001f * b_size.x);
		_window.draw(house_sprite2);
	}

	if(time >= sf::seconds(22) && time <= sf::seconds(22+15))//2
	{
		house_sprite3.move(0,0.01f);
		house_sprite3.setScale(0.001f * b_size.x, 0.001f * b_size.x);
		
		house_sprite4.move(0,0.01f);
		house_sprite4.setScale(0.001f * b_size.x, 0.001f * b_size.x);
		_window.draw(house_sprite3);
		_window.draw(house_sprite4);

	}


}

void Draw::Draw_Enemy_formations()
{
	
	if(time2 > sf::milliseconds(4*1000) && wave == 0)
	{
		Enemy_cannon temp(500,-50);
		cannons.push_back(temp);
		

		Enemy_cannon temp2(60,0);
		cannons.push_back(temp2);

		wave++;
	}


	if(time2 == sf::milliseconds(60*1000))
	{
		
	}
}