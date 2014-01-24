#include "Game.h"

#include "Input.h"
#include "Draw.h"


//Temp
#include <iostream>

Input input;
Draw draw;

Game::Game(void)
{
	player = new Player();
}


Game::~Game(void)
{
	delete player;
}

void Game::Greate_window()//Sets the values of the main window
{
	main_window.create(sf::VideoMode(1024,576),"Tree Heroes",sf::Style::Default);
}

void Game::Close_window()//Close the main window
{

}

void Game::Main_loop()
{

	Greate_window();


	while(main_window.isOpen())
	{
		sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
        }
		
		player->Update();
		draw.Update(main_window,player->pos);
	}

	main_window.close();//Close main window
}