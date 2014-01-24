#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

map<string, Sprite> SpriteLib; // Spritet
vector<Texture> TextureLib(10); // Tekstuurit
default_random_engine generator((unsigned int)time(0)); // Random generattoori <random>

int textureIndex=0; // K‰ytet‰‰n CreateSpritess‰
Clock kello;
float boxW=32, boxH=32;
//Time spawnTimer = kello.getElapsedTime(); // Est‰‰ boxin spawnausta liian nopeasti
//float spawnTimer = kello.getElapsedTime();

uniform_real_distribution<float> width(boxW, 1024); // Leveys randomisaatio
uniform_real_distribution<float> height(boxH, 576); // Korkeus randomisaatio


void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "My window");
	Initialize();

	Time testiaika;

	// RNGtestaus
	//for (int i=0;i<3;i++) 
	//{
	//	cout<<" leveys: "<<width(generator);
	//	cout<<" korkeus: "<< height(generator);
	//}


	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();
			}
	   ReactionWindow.clear(Color::Blue);

	   if (kello.getElapsedTime().asSeconds() > 0.5)
	   {
		   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH);
		   kello.restart();
	   }

	   //cout<<kello.getElapsedTime().asSeconds();
	   //system("PAUSE");

	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.display(); 
	}

}


//vector<float> RandomVector()
//{
//	vector<float> location(float a, float b);
//	float a = width(generator);
//	float b = height(generator);
//	return location;
//}


// Siirt‰‰ Spritej‰ SpriteLibbiin - voi hakea nimell‰. S‰ilytt‰‰ niiden tekstuurit vectorissa.
void CreateSprite(string name, string path)
{
	Texture texture;
	Sprite sprite;
	cout<<textureIndex<<": "<<path<<" "; // Testausta

	texture.loadFromFile(path);
	TextureLib[textureIndex] = texture;
	sprite.setTexture(TextureLib[textureIndex]);
	textureIndex++;
	SpriteLib.insert(make_pair(name,sprite));
}


// Alustaa game assetit.
void Initialize()
{
	CreateSprite("testi","Resources/reactionbox.png");
	CreateSprite("title","Resources/reactionbox2.png");

	cout<<"Sprites: " <<SpriteLib.size();
	cout<<" Textures: " <<TextureLib.size();
	cout<<" TextureIndex: "<<textureIndex;
}