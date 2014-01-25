#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp> // Defines a system event and its parameters. 
#include <SFML/System/Vector2.hpp> // Utility template class for manipulating 2-dimensional vectors. 
#include <SFML/Graphics/Rect.hpp> // Utility class for manipulating 2D axis aligned rectangles. 
#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <random>
using namespace std;
using namespace sf;

void ReactionGame();
void Initialize();
void CreateSprite(string name, string path);
bool MouseClick(Sprite sprite);