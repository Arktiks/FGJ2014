#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

map<string, Sprite> SpriteLib; // Spritet
vector<Texture> TextureLib(10); // Tekstuurit
default_random_engine generator((unsigned int)time(0)); // Random generattoori <random>

int textureIndex=0; // K‰ytet‰‰n CreateSpritess‰
Clock kello;
float boxW=32, boxH=32; // Reactionbox Mitat

uniform_real_distribution<float> width(boxW, 1024); // Leveys randomisaatio
uniform_real_distribution<float> height(boxH, 576); // Korkeus randomisaatio
uniform_real_distribution<float> color(1, 255); // Random v‰ri

Mouse mouse;

void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "My window");
	Initialize();
	//Color randomColor(color(generator),color(generator),color(generator),255);

	cout<<SpriteLib["testi"].getLocalBounds().height;


	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();
			}

	   //ReactionWindow.clear(Color(color(generator),color(generator),color(generator),255)); // Epilepsia v‰ri
	   ReactionWindow.clear(Color::Black); // Musta

	   /*if (kello.getElapsedTime().asSeconds() > 0.5)
	   {
		   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH);
		   SpriteLib["testi"].setColor(Color(color(generator),color(generator),color(generator),255));
		   kello.restart();
	   }*/

	   /*if (MouseClick(SpriteLib["testi"]))
		   cout<<"Osui";*/

	   /*if (Mouse::isButtonPressed(Mouse::Button::Left))
		   cout<<"VASEN! ";*/

	   if(SpriteLib["testi"].contains(Mouse::getPosition(ReactionWindow)))
		   cout<<"SISƒLLƒ! ";

	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.display(); 
	}

}


//bool MouseClick(Sprite sprite)
//{
//	//if (sprite.getLocalBounds().contains((float)(Mouse.getPosition(ReactionWindow).x), (float)(Mouse.getPosition(ReactionWindow).y)) && Mouse::isButtonPressed(Mouse.Left))
//	Rect<float> spriteNelio;
//	spriteNelio.height = sprite.getLocalBounds().height;
//	spriteNelio.width = sprite.getLocalBounds().width;
//	spriteNelio.left = sprite.getLocalBounds().left;
//	spriteNelio.top = sprite.getLocalBounds().top;
//
//	//if(sprite.getLocalBounds().contains(Mouse::getPosition(ReactionWindow)))
//	if(spriteNelio.contains(Mouse.getPosition))
//		return true;
//	else
//		return false;
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