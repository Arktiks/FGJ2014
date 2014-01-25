#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

//Libraryt eri peli asseteille.
map<string, Sprite> SpriteLib; 
map<string, Text> TextLib; 
map<string, Sound> SoundLib; 
vector<Texture> TextureLib(10); 
vector<SoundBuffer> BufferLib(10); 
vector<Sprite> HarmBoxes(5); // Punaiset laatikot.

default_random_engine generator((unsigned int)time(0)); // Random generattoori <random>
double randomizeTime=0.7; // Boxin randomize interval.
int textureIndex=0, bufferIndex=0; // K‰ytet‰‰n Create funktioissa.
float boxW=32, boxH=32; // Reactionbox mitat testailuun.
Font Impact; // Perusfontti
Clock kello, noiseKello;

uniform_real_distribution<float> width(boxW, 1024);
uniform_real_distribution<float> height(boxH, 576);
uniform_real_distribution<float> color(1, 255); // V‰reille
uniform_real_distribution<int> tuhat(1, 1000);


void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "01100010011010010111010000100000011000010110010001110110011001010110111001110100011101010111001001100101", Style::Titlebar);
	Impact.loadFromFile("Resources/impact.ttf"); // Fontti ladataan.
	Initialize(); // Alustetaan peli assetit.

	// Peli muuttujia.
	int pisteLaskuri=2, noise=0;
	bool ghostclicked=false;
	string Pisteet;

	// Sprite v‰rien ja sijaintien alustus.
	SpriteLib["testi"].setPosition(200.0f, 200.0f);
	SpriteLib["scoreBG"].setPosition(2.0f, 2.0f);
	TextLib["pisteet"].setPosition(23, 7.5f);
	TextLib["pisteet"].setColor(Color::Black);
	SpriteLib["ghost"].setColor(Color::Color(255,255,255,150));
	ReactionWindow.setFramerateLimit(60);

	while (ReactionWindow.isOpen()) 
	{
	   while (ReactionWindow.pollEvent(ReactionEvent)) 
			{
			   if (ReactionEvent.type == Event::Closed) 
				   ReactionWindow.close();

			   if (ReactionEvent.type == Event::KeyPressed && ReactionEvent.key.code == Keyboard::Escape) // Suljetaan peli escist‰.
				   ReactionWindow.close();

			   if(MouseClickArea(SpriteLib["testi"], ReactionEvent, ReactionWindow)) // Testataan klikkaatko reaktioboxia.
				   {
					   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH); // Randomisoi reaktioboxin lokaatiota.
					   pisteLaskuri++;
				   }

			   if(MouseClickArea(SpriteLib["ghost"], ReactionEvent, ReactionWindow) && pisteLaskuri==2) // Spawnaa ghostin kun tietyt ehdot t‰yttyy.
					{
						ghostclicked=true;
						SoundLib["glitch"].play();
						SpriteLib["ghost"].setPosition(-100,-100);

						//Sprite harmbox;
						//Texture box;
						//box.loadFromFile("Resources/testi.png");
						//harmbox.setTexture(box);
						//harmbox.setColor(Color::Red);

						for(int i=0; i<3; i++) // Luodaan h‰irint‰boxit kun Ghost h‰vi‰‰.
						{
							HarmBoxes[i] = InstantSprite("Resources/reactionbox.png");
							HarmBoxes[i].setColor(Color::Red);
						}
					}
			 }

	   // Muuttaa pisteet stringiksi.
	   Pisteet = ConvertInt(pisteLaskuri);
	   (TextLib["pisteet"]).setString(Pisteet);

	   // Random v‰rej‰.
	   Color randomColor(color(generator), color(generator), color(generator),255);
	   Color randomOpacity(color(generator), color(generator), color(generator), color(generator)); //Myˆs random opacity.

	   // ### Piirt‰mis Logiikka ###
	   if (pisteLaskuri==0) // Normaali
			ReactionWindow.clear(Color::Black);
	   else if (pisteLaskuri==1) // Epilepsia
		    ReactionWindow.clear(randomColor);
	   else if (pisteLaskuri==2) // Kummitus
			{
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
					noiseKello.restart(); // Pit‰‰ noise-kuvat kierrossa.

				if(ghostclicked==false)
						ReactionWindow.draw(SpriteLib["ghost"]); // Piirt‰‰ kummitusta niin kauan kun sit‰ ei ole klikattu.
			}


	   if (kello.getElapsedTime().asSeconds() > randomizeTime)
		   {
			   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH); // Pist‰‰ reaktioboxin random spottiin.

			   if(ghostclicked==false)
					SpriteLib["ghost"].setPosition(width(generator),height(generator)); // Kummituksen sijainnin vaihto.
			   else if(ghostclicked==true)
			   {
				   for(int i=0; i<3; i++) // P‰ivitet‰‰n h‰irint‰boxien sijainnit.
						{
							HarmBoxes[i].setPosition(width(generator)-boxW,height(generator)-boxH);
						}
			   }
			   kello.restart();
		   }


	   ReactionWindow.draw(SpriteLib["testi"]);
	   ReactionWindow.draw(SpriteLib["scoreBG"]);
	   ReactionWindow.draw(TextLib["pisteet"]);

	   if(ghostclicked==true)  // Piirret‰‰n h‰irint‰boxit.
			for(int i=0; i<3; i++)
				{
					ReactionWindow.draw(HarmBoxes[i]);
				}
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
		if(mouseX > sprite.getPosition().x && mouseY > sprite.getPosition().y && mouseX < (sprite.getPosition().x+sprite.getGlobalBounds().width) && mouseY < (sprite.getPosition().y+sprite.getGlobalBounds().height))
		{
			cout<<"\n Pisteet +1";
			return true;
		}
		else return false;
	}
	else return false;
}

// Siirt‰‰ spritej‰ SpriteLibbiin - voi hakea nimell‰. S‰ilytt‰‰ niiden tekstuurit vectorissa.
void CreateSprite(string name, string path)
{
	Texture texture;
	Sprite sprite;
	cout<<textureIndex<<": "<<path<<"\n";

	texture.loadFromFile(path);
	TextureLib[textureIndex] = texture;
	sprite.setTexture(TextureLib[textureIndex]);
	textureIndex++;
	SpriteLib.insert(make_pair(name,sprite));
}

// Siirt‰‰ soundeja SoundLibbiin - voi hakea nimell‰. S‰ilytt‰‰ niiden soundBufferit vectorissa.
void CreateSound(string name, string path)
{
	SoundBuffer buffer;
	Sound sound;
	cout<<bufferIndex<<": "<<path<<"\n";

	buffer.loadFromFile(path);
	BufferLib[bufferIndex] = buffer;
	sound.setBuffer(BufferLib[bufferIndex]);
	bufferIndex++;
	SoundLib.insert(make_pair(name,sound));
}

// Tekee spriten instana.
Sprite InstantSprite(string path)
{
	Sprite sprite;
	Texture texture;

	texture.loadFromFile(path);
	sprite.setTexture(texture);
	return sprite;
}

// Alustaa peliassetit - tulostaa consoleen myˆs varmistuslukuja.
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

	cout<<"\nCreating Sounds \n";
	CreateSound("glitch","Resources/glitch.wav");

	cout<<"\nSprites: " <<SpriteLib.size();
	cout<<"\nTexture Space: " <<TextureLib.size();
	cout<<"\nTexture Count: "<<textureIndex;
	cout<<"\nSound Space: " <<SoundLib.size();
	cout<<"\nSound Count: "<<bufferIndex;
	cout<<"\nTexts: " <<TextLib.size();
}

// Muuttaa Int-luvun stringiksi.
string ConvertInt(int number)
{
   stringstream ss; // Create a stringstream.
   ss << number; // Add number to the stream.
   return ss.str(); // return a string with the contents of the stream.
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