#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <string.h>
#include <iostream>

class Game
{
	//friend Player;
public:
	Game();
	~Game();

	void runGame(void);
	void playMenu(void);
	//{
		void playCampaign(bool isMulti = false);
			void campaignSplashScreen1(void);

		void playMultiplayer(void);
			void multiplayerSplashScreen(void);

		void playEndless(bool isMulti = false);
			void endlessSplashScreen();
	//}
	void highscoresMenu(void);
	void howToPlayMenu(void);


private:
	Player mPlayer1;
	sf::RenderWindow window;
	sf::WindowHandle windowHandle;
	sf::Vector2i screenDimensions;
	sf::Vector2f bg1Position;
	sf::Vector2f bg2Position;
	sf::Texture bg1Texture;
	sf::Texture bg2Texture;
	sf::Sprite bgImage1;
	sf::Sprite bgImage2;
	sf::Clock clock;				//SF clock for timing 
	sf::View view;					//ViewPort object
	sf::Font font;					//Font for text
	//Use Text vector and pass by reference or allocate and deallocate with usage use objects in current function and delete when not in current function.
	sf::Text menuText1;
	sf::Text menuText2;
	sf::Text menuText3;
	sf::Text playMenuText1;			//Game Mode underlined
	sf::Text playMenuText2;			//option 1, Campaign
	sf::Text playMenuText3;			//option 2, Multiplayer
	sf::Text playMenuText4;			//option 3, Endless
	sf::Text playMenuText5;			//option 4, Back
	sf::Mouse mouse;

	bool player1IsHit = false;
	bool player2IsHit = false;
	bool isMultiplayer = false;
	float x, y = 0;
};