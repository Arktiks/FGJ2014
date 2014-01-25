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


void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "01100010011010010111010000100000011000010110010001110110011001010110111001110100011101010111001001100101", Style::Titlebar);
	Initialize();
	Font font; font.loadFromFile("Resources/impact.ttf");
	SpriteLib["testi"].setPosition(200.0f,200.0f);
	int PisteLaskuri=0;

	//Vector2f mousePosition = Vector2f(Mouse.getPosition(ReactionWindow).x,Mouse.getPosition(ReactionWindow).y);
	//float mouseX=0, mouseY=0;
	//Vector2<float> mousePosition(mouseX, mouseY);


	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();

			   if (ReactionEvent.type == Event::KeyPressed && ReactionEvent.key.code == Keyboard::Escape)
				   ReactionWindow.close();

			   if(MouseClickArea(SpriteLib["testi"], ReactionEvent, ReactionWindow))
				   PisteLaskuri++;

			   /*else if(ReactionEvent.type == Event::MouseButtonPressed && ReactionEvent.mouseButton.button == Mouse::Left)
			   {
				   cout<<" TOIMITT";
				   if(SpriteLib["testi"].getGlobalBounds().contains(mousePosition))
				   cout<<"VEKTORIIIII";*/
			 }


	   //ReactionWindow.clear(Color(color(generator),color(generator),color(generator),255)); // Epilepsia v‰ri
	   ReactionWindow.clear(Color::Black); // Musta
	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.display();

	   //CheckForMouseTrigger(SpriteLib["testi"], ReactionWindow);
	   /*mousePosition.x=Mouse::getPosition(ReactionWindow).x;
	   mousePosition.y=Mouse::getPosition(ReactionWindow).y;*/

	}
}

bool MouseClickArea(Sprite sprite, Event &event, RenderWindow &window)
{
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if(mouseX > sprite.getPosition().x && mouseY > sprite.getPosition().y && mouseX < (sprite.getPosition().x+32) && mouseY < (sprite.getPosition().y+32))
		{
			cout<<"TOIMII";
			return true;
		}
		else return false;
	}
	else return false;
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


//bool CheckForMouseTrigger(Sprite &sprite, RenderWindow &window)
//{
//	int mouseX = Mouse::getPosition(window).x;
//	int mouseY = Mouse::getPosition(window).y;
//
//	if (mouseX > sprite.getPosition().x && mouseX > sprite.getPosition().y && mouseY < (sprite.getPosition().y + sprite.getGlobalBounds().height))
//		{
//			if(Mouse::isButtonPressed(Mouse::Left))
//				{
//					return true;
//					cout<<" PAINETTU";
//				}
//			return false;
//		}
//	return false;
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