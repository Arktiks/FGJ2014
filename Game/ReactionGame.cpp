#include "ReactionGame.h"
RenderWindow ReactionWindow; // Window that serves as a target for OpenGL rendering.
Event ReactionEvent;

//Libraryt eri peli asseteille.
map<string, Sprite> SpriteLib; 
map<string, Text> TextLib; 
map<string, Sound> SoundLib; 
vector<Texture> TextureLib(18); 
vector<SoundBuffer> BufferLib(5); 
vector<Sprite> HarmBoxes(5); // Punaiset laatikot.

default_random_engine generator((unsigned int)time(0)); // Random generattoori <random>
double randomizeTime=2; // Boxin randomize interval.
int textureIndex=0, bufferIndex=0; // K‰ytet‰‰n Create funktioissa.
float boxW=32, boxH=32; // Reactionbox mitat testailuun.
Font Impact; // Perusfontti
Clock kello, noiseKello;

uniform_real_distribution<float> width(boxW, 1024);
uniform_real_distribution<float> height(boxH, 576);
uniform_real_distribution<float> color(1, 255); // V‰reille
uniform_real_distribution<float> kulma(1, 360); // Kulmille


void ReactionGame()
{
	ReactionWindow.create(VideoMode(1024, 576), "01100010011010010111010000100000011000010110010001110110011001010110111001110100011101010111001001100101", Style::Titlebar);
	Impact.loadFromFile("Resources/impact.ttf"); // Fontti ladataan.
	Initialize(); // Alustetaan peli assetit.
	SoundLib["bleep"].setVolume(10);
	SoundLib["glitch"].setVolume(40);

	// Peli muuttujia.
	int pisteLaskuri=0, noise=0;
	bool ghostclicked=false;
	string Pisteet;

	// Muuta alustusta.
	SpriteLib["testi"].setPosition(200.0f, 200.0f);
	SpriteLib["scoreBG"].setPosition(2.0f, 2.0f);
	TextLib["pisteet"].setPosition(23, 7.5f);
	TextLib["pisteet"].setColor(Color::Black);
	SpriteLib["ghost"].setColor(Color::Color(255,255,255,150));
	SpriteLib["tech1"].setOrigin(SpriteLib["tech1"].getGlobalBounds().width/2,SpriteLib["tech1"].getGlobalBounds().height/2);
	SpriteLib["tech1"].setPosition(512,238);
	ReactionWindow.setFramerateLimit(60);
	Music ambience;		ambience.openFromFile("Resources/ambience.wav");	ambience.setVolume(70);		ambience.play(); // Musiikkia


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
						pisteLaskuri++;

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

	   else if (pisteLaskuri==3) // Face
			{
				SpriteLib["testi"].setColor(Color::Green);
				if(noiseKello.getElapsedTime().asMilliseconds() <= 80)
				{
					ReactionWindow.draw(SpriteLib["face1"]);
					TextLib["pisteet"].setColor(randomOpacity);
				}
				else if(noiseKello.getElapsedTime().asMilliseconds() > 80 && noiseKello.getElapsedTime().asMilliseconds() <= 160)
				{
					ReactionWindow.draw(SpriteLib["face2"]);
				}
				else if(noiseKello.getElapsedTime().asMilliseconds() > 160 && noiseKello.getElapsedTime().asMilliseconds() <= 240)
					ReactionWindow.draw(SpriteLib["face3"]);
				else
					noiseKello.restart();
			}

	   else if (pisteLaskuri==4) // Tech
		   {
			   SpriteLib["testi"].setColor(randomColor);
			   TextLib["pisteet"].setColor(Color::Black);
				if(noiseKello.getElapsedTime().asMilliseconds() <= 80)
				{
					SpriteLib["tech1"].setRotation(kulma(generator));
					ReactionWindow.draw(SpriteLib["tech1"]);
				}
				else if(noiseKello.getElapsedTime().asMilliseconds() > 80 && noiseKello.getElapsedTime().asMilliseconds() <= 80*2)
					ReactionWindow.draw(SpriteLib["tech2"]);
				else if(noiseKello.getElapsedTime().asMilliseconds() > 80*2 && noiseKello.getElapsedTime().asMilliseconds() <= 80*3)
					ReactionWindow.draw(SpriteLib["tech3"]);
				else if(noiseKello.getElapsedTime().asMilliseconds() > 80*3 && noiseKello.getElapsedTime().asMilliseconds() <= 80*4)
					ReactionWindow.draw(SpriteLib["tech4"]);
				else
					noiseKello.restart();
		   }

	   else if(pisteLaskuri==5) // Heart
			{
				ReactionWindow.clear(Color::Black);
				//ReactionWindow.draw(SpriteLib["free"]);
				//int opacity=255;

					if(noiseKello.getElapsedTime().asSeconds() <= 3.0f)
					{
						/*SpriteLib["free"].setColor(Color::Color(255,255,255,opacity--));
						ReactionWindow.clear(Color::Black);*/
						ReactionWindow.draw(SpriteLib["free"]);
					}
					else if(noiseKello.getElapsedTime().asSeconds() > 3.0f && noiseKello.getElapsedTime().asSeconds() <= 4.5f)
					{
						//SpriteLib["free"].setColor(Color::Color(255,255,255,opacity--));
						SoundLib["laugh"].play();
						ReactionWindow.clear(Color::Black);
						ReactionWindow.draw(SpriteLib["bit"]);
					}
					else
						ReactionWindow.close();

				// Syd‰n Animaatio
				////ReactionWindow.clear(Color::Black);
				////noiseKello.restart();
				//int row=0,lines=0;
				//noiseKello.restart();
				//SpriteLib["heartline"].setTextureRect(IntRect(row*1024, lines*576, 1024*(row+1), 576*(lines+1)));
				//SpriteLib["testi"].setPosition(-100,-100);

				//for(int frames=0; frames<15;)
				//{
				//	ReactionWindow.clear(Color::Black);
				//	ReactionWindow.draw(SpriteLib["heartline"]);
				//
				//	if(noiseKello.getElapsedTime().asSeconds() >= 2.0f)
				//	{
				//		SpriteLib["heartline"].setTextureRect(IntRect(row*1024, lines*576, 1024*(row+1), 576*(lines+1)));
				//		frames++;
				//		row++;
				//		if (row==3)
				//		{
				//			row=0;
				//			lines++;
				//				if(lines==5)
				//				{
				//					lines=0;
				//					frames=0;
				//				}
				//		}
				//		noiseKello.restart();
				//	}
				//}
			}


	   if (kello.getElapsedTime().asSeconds() > randomizeTime && pisteLaskuri!=5)
		   {
			   SpriteLib["testi"].setPosition(width(generator)-boxW,height(generator)-boxH); // Pist‰‰ reaktioboxin random spottiin.
			   if (pisteLaskuri>=3)
				   TextLib["pisteet"].setPosition(width(generator)-boxW,height(generator)-boxH);


			   if(ghostclicked==false)
					SpriteLib["ghost"].setPosition(width(generator),height(generator)); // Kummituksen sijainnin vaihto.
			   else if(ghostclicked==true && pisteLaskuri!=5)
			   {
				   for(int i=0; i<3; i++) // P‰ivitet‰‰n h‰irint‰boxien sijainnit.
						{
							HarmBoxes[i].setPosition(width(generator)-boxW,height(generator)-boxH);
						}
			   }
			   kello.restart();
		   }

	   if(pisteLaskuri<3 && pisteLaskuri!=5)
			ReactionWindow.draw(SpriteLib["scoreBG"]);

	   if(pisteLaskuri!=5)
		   {
			   ReactionWindow.draw(SpriteLib["testi"]);
			   ReactionWindow.draw(TextLib["pisteet"]);
		   }

	   if(ghostclicked==true && pisteLaskuri<5)  // Piirret‰‰n h‰irint‰boxit.
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
		//if(mouseX > sprite.getPosition().x && mouseY > sprite.getPosition().y && mouseX < (sprite.getPosition().x+sprite.getGlobalBounds().width) && mouseY < (sprite.getPosition().y+sprite.getGlobalBounds().height))
		if(mouseX > sprite.getGlobalBounds().left &&
			mouseY > sprite.getGlobalBounds().top &&
			mouseX < (sprite.getGlobalBounds().left+sprite.getGlobalBounds().width) &&
			mouseY < (sprite.getGlobalBounds().top+sprite.getGlobalBounds().height))
		{
			cout<<"\n Pisteet +1";
			SoundLib["bleep"].play();
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
	CreateSprite("face1","Resources/face1.png");
	CreateSprite("face2","Resources/face2.png");
	CreateSprite("face3","Resources/face3.png");
	CreateSprite("tech1","Resources/tech1.png");
	CreateSprite("tech2","Resources/tech2.png");
	CreateSprite("tech3","Resources/tech3.png");
	CreateSprite("tech4","Resources/tech4.png");
	CreateSprite("free","Resources/free.png");
	CreateSprite("bit","Resources/bit.png");

	Text pisteet("1101010110",Impact,44);
	TextLib.insert(make_pair("pisteet", pisteet));

	cout<<"\nCreating Sounds \n";
	CreateSound("glitch","Resources/glitch.wav");
	CreateSound("bleep","Resources/bleep.wav");
	CreateSound("laugh","Resources/laugh.wav");

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