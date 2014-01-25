// ### SFML ###
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// ### C++ ###
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <random>
#include <sstream>
using namespace std;
using namespace sf;


//Funktioiden selitykset <cpp> tiedostossa.
void ReactionGame();
void Initialize();
void CreateSprite(string name, string path);
void CreateSound(string name, string path);
bool MouseClickArea(Sprite sprite, Event &event, RenderWindow &window);
Sprite InstantSprite(string path);
string ConvertInt(int number);

//Työn alla olevat funktiot.
//void CreateText(string name, string texts, Font font, int size);