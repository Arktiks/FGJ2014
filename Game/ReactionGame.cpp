#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

map<string, Sprite> SpriteLib; // Spritet
map<string, Text> TextLib; // Tekstit
vector<Texture> TextureLib(10); // Tekstuurit
default_random_engine generator((unsigned int)time(0)); // Random generattoori <random>

int textureIndex=0; // K‰ytet‰‰n CreateSpritess‰
float boxW=32, boxH=32; // Reactionbox Mitat
Font Impact; // Perusfontti
Clock kello, noiseKello;

uniform_real_distribution<float> width(boxW, 1024); // Leveys randomisaatio
uniform_real_distribution<float> height(boxH, 576); // Korkeus randomisaatio
uniform_real_distribution<float> color(1, 255); // Random v‰ri
uniform_real_distribution<int> tuhat(1, 1000);


void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "01100010011010010111010000100000011000010110010001110110011001010110111001110100011101010111001001100101", Style::Titlebar);
	Impact.loadFromFile("Resources/impact.ttf");
	Initialize();
	int pisteLaskuri=2, noise=0;
	string Pisteet;

	SpriteLib["testi"].setPosition(200.0f, 200.0f);
	SpriteLib["scoreBG"].setPosition(2.0f, 2.0f);
	TextLib["pisteet"].setPosition(23, 7.5f);
	TextLib["pisteet"].setColor(Color::Black);
	SpriteLib["ghost"].setColor(Color::Color(255,255,255,150));

	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();

			   if (ReactionEvent.type == Event::KeyPressed && ReactionEvent.key.code == Keyboard::Escape)
				   ReactionWindow.close();

			   if(MouseClickArea(SpriteLib["testi"], ReactionEvent, ReactionWindow))
				   {
					   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH);
					   pisteLaskuri++;
				   }
			 }

	   Pisteet = ConvertInt(pisteLaskuri);
	   (TextLib["pisteet"]).setString(Pisteet);
	   Color randomColor(color(generator), color(generator), color(generator),255); // Random v‰ri generaattori
	   Color randomOpacity(color(generator), color(generator), color(generator), color(generator)); // V‰ri + Opacity

	   if (pisteLaskuri==0)
			ReactionWindow.clear(Color::Black); // Musta
	   else if (pisteLaskuri==1)
		    ReactionWindow.clear(randomColor); // Epilepsia v‰ri
	   else if (pisteLaskuri==2)
			{
				ReactionWindow.clear(Color::Black);
				if(noiseKello.getElapsedTime().asMilliseconds() <= 80)
				{
					ReactionWindow.draw(SpriteLib["noise1"]);
					TextLib["pisteet"].setColor(randomOpacity);
				}
				else if(noiseKello.getElapsedTime().asMilliseconds() > 80 && noiseKello.getElapsedTime().asMilliseconds() <= 160)
				{
					ReactionWindow.draw(SpriteLib["noise2"]);
				}
				else if(noiseKello.getElapsedTime().asMilliseconds() > 160 && noiseKello.getElapsedTime().asMilliseconds() <= 240)
					ReactionWindow.draw(SpriteLib["noise3"]);
				else
					noiseKello.restart();
			}



	   if (kello.getElapsedTime().asSeconds() > 2)  // Pist‰‰ laatikon random spottiin.
		   {
			   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH);
			   SpriteLib["ghost"].setPosition(width(generator),height(generator));
			   kello.restart();
		   }


	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.draw(SpriteLib["ghost"]);
	   ReactionWindow.draw(SpriteLib["scoreBG"]);
	   ReactionWindow.draw(TextLib["pisteet"]);
	   ReactionWindow.display();
	}
}


// True kun hiiri on spriten alueella ja painat vasenta.
bool MouseClickArea(Sprite sprite, Event &event, RenderWindow &window)
{
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if(mouseX > sprite.getPosition().x && mouseY > sprite.getPosition().y && mouseX < (sprite.getPosition().x+32) && mouseY < (sprite.getPosition().y+32))
		{
			cout<<"\n Pisteet +1";
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
	cout<<textureIndex<<": "<<path<<"\n"; // Testausta

	texture.loadFromFile(path);
	TextureLib[textureIndex] = texture;
	sprite.setTexture(TextureLib[textureIndex]);
	textureIndex++;
	SpriteLib.insert(make_pair(name,sprite));
}


//void CreateText(string name, string texts, Font font, int size) 
//{
//	Text tekstia(" ", font, size);
//	tekstia.setString(texts);
//	//text.setCharacterSize(size);
//	//text.setFont(font);
//	//tekstia.setColor(color);
//	TextLib.insert(make_pair(name,tekstia));
//}


// Alustaa game assetit.
void Initialize()
{
	cout<<"Creating Sprites \n";
	CreateSprite("testi","Resources/reactionbox.png");
	CreateSprite("title","Resources/reactionbox2.png");
	CreateSprite("scoreBG","Resources/scoreBG.png");
	CreateSprite("noise1","Resources/noise1.png");
	CreateSprite("noise2","Resources/noise2.png");
	CreateSprite("noise3","Resources/noise3.png");
	CreateSprite("ghost","Resources/ghost.png");

	Text pisteet("1101010110",Impact,44);
	TextLib.insert(make_pair("pisteet", pisteet));

	cout<<"\nSprites: " <<SpriteLib.size();
	cout<<"\nTexture Space: " <<TextureLib.size();
	cout<<"\nTexture Count: "<<textureIndex;
	cout<<"\nTexts: " <<TextLib.size();
}


string ConvertInt(int number)
{
   stringstream ss; // Create a stringstream.
   ss << number; // Add number to the stream.
   return ss.str(); // return a string with the contents of the stream.
}