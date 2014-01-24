#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

map<string, Sprite> SpriteLib;
vector<Texture> TextureLib(10);
int textureIndex=0;

void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "My window");
	Initialize();
	SpriteLib["testi"].setPosition(200,200);
	SpriteLib["title"].setPosition(300,300);

	// #### Initialize Graphics ####
	//Texture BOX;
	//Sprite box;

	//BOX.loadFromFile("Resources/reactionbox.png");
	//box.setTexture(BOX);
	// #############################

	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();
			}
	   ReactionWindow.clear(Color::Blue); 
	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.draw(SpriteLib["title"]);
	   ReactionWindow.display(); 
	}
}

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