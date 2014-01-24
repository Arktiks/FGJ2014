#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

#include "ReactionGame.h"

RenderWindow window; // Window that serves as a target for OpenGL rendering.
Event event; // Event processing.

int main()
{
	window.create(VideoMode(1024, 576), "My window"); 

	while (window.isOpen()) 
	{
	   while (window.pollEvent(event)) 
			{
			   if (event.type == Event::Closed) 
				   window.close();
			}
	   window.clear(Color::Blue); 
	   window.display(); 
	}

	//system("PAUSE");
    return 0;
}