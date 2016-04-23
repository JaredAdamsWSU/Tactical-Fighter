#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

Game::Game()
{
	//sf::RenderWindow window(sf::VideoMode(550, 700), "Tactical Fighter!");
	window.create(sf::VideoMode(550, 700), "Tactical Fighter!", sf::Style::Default, sf::ContextSettings(0, 0, 0, 2, 0));
	window.setSize(sf::Vector2u(550, 700));
	window.setVisible(true);
	window.setActive(true);
	window.setPosition(sf::Vector2i(580, 150));
	screenDimensions.x = 550;
	screenDimensions.y = 700;
	
	cout << "windowisopen: " << window.isOpen() << endl;
	cout << "window settings: " << window.getSettings().antialiasingLevel << endl;

	//Load error detection
	if (!bg1Texture.loadFromFile("starsBackground.png")) //http://ksuweb.kennesaw.edu/~jprest20/tutorials/starsBackground.png Photo Credit
		std::cout << "Could not load background image" << std::endl;
	if (!bg2Texture.loadFromFile("starsBackground.png")) //http://ksuweb.kennesaw.edu/~jprest20/tutorials/starsBackground.png Photo Credit
		std::cout << "Could not load background image" << std::endl;
	if (!font.loadFromFile("ARDESTINE.ttf"))			 //.ttf true type font from windows
		std::cout << "Could not load font" << std::endl;

	bgImage1.setTexture(bg1Texture);
	bgImage1.setRotation(90);
	bgImage1.setScale(1.25f, (float)screenDimensions.y / bg2Texture.getSize().y);
	bgImage1.setTextureRect(sf::IntRect(0, 0, screenDimensions.x, screenDimensions.y));

	bgImage2.setTexture(bg2Texture);
	bgImage2.setRotation(90);
	bgImage2.setScale(1.25f, (float)screenDimensions.y / bg2Texture.getSize().y);
	bgImage2.setTextureRect(sf::IntRect(0, 0, screenDimensions.x, screenDimensions.y));

	//Initial backdrop image positions for seamless looping and player image position
	bg1Position.x = screenDimensions.x;
	bg1Position.y = -screenDimensions.y;

	bg2Position.x = screenDimensions.x;
	bg2Position.y = 0;

	//////////MAIN MENU TEXT//////////////////
	//Text, Play
	menuText1.setString("Play");
	menuText1.setFont(font);
	menuText1.setCharacterSize(40);
	menuText1.setColor(sf::Color::Blue);
	menuText1.setPosition((screenDimensions.x / 4)+ 87, 200); //previous x was 230 
	//text.setStyle(sf::Text::Bold);

	//Text //Highscores
	menuText2.setString("Highscores");
	menuText2.setFont(font);
	menuText2.setCharacterSize(40);
	menuText2.setColor(sf::Color::Blue);
	menuText2.setPosition((screenDimensions.x / 4) + 32, 260);
	//text.setStyle(sf::Text::Bold);

	//Text //Instructions
	menuText3.setString("How To Play");
	menuText3.setFont(font);
	menuText3.setCharacterSize(40);
	menuText3.setColor(sf::Color::Blue);
	menuText3.setPosition((screenDimensions.x / 4) + 12, 320);
	//text.setStyle(sf::Text::Bold);

	//////////////Play-Select Screen Text/////////////////////
	//Text, Game Mode
	playMenuText1.setString("Game Mode");
	playMenuText1.setStyle(sf::Text::Underlined | sf::Text::Italic);
	playMenuText1.setFont(font);
	playMenuText1.setCharacterSize(40);
	playMenuText1.setColor(sf::Color::Blue);
	playMenuText1.setPosition((screenDimensions.x / 4) + 20, 160); //previous x was 230 

	//Text //Campaign
	playMenuText2.setString("Campaign");
	playMenuText2.setFont(font);
	playMenuText2.setCharacterSize(40);
	playMenuText2.setColor(sf::Color::Blue);
	playMenuText2.setPosition((screenDimensions.x / 4) + 46, 210);

	//Text //Multi-Player
	playMenuText3.setString("Multi-player");
	playMenuText3.setFont(font);
	playMenuText3.setCharacterSize(40);
	playMenuText3.setColor(sf::Color::Blue);
	playMenuText3.setPosition((screenDimensions.x / 4) + 22, 270);

	//Text //Endless
	playMenuText4.setString("Endless");
	playMenuText4.setFont(font);
	playMenuText4.setCharacterSize(40);
	playMenuText4.setColor(sf::Color::Blue);
	playMenuText4.setPosition((screenDimensions.x / 4) + 58, 330);

	//Text //Back
	playMenuText5.setString("Back");
	playMenuText5.setFont(font);
	playMenuText5.setCharacterSize(40);
	playMenuText5.setColor(sf::Color::Blue);
	playMenuText5.setPosition((screenDimensions.x / 4) + 86, 390);

}

Game::~Game()
{

}

//Jared
void Game::runGame()
{
	//textbox1 rect
		sf::RectangleShape rect1(sf::Vector2f(80, 40));
		rect1.setPosition(menuText1.getPosition().x - 3, menuText1.getPosition().y + 9);
		rect1.setTextureRect(sf::IntRect(0, 0, 80, 40));
		rect1.setFillColor(sf::Color::Transparent);
	//textbox2 rect
		sf::RectangleShape rect2(sf::Vector2f(208, 40));
		rect2.setPosition(menuText2.getPosition().x - 3, menuText2.getPosition().y + 9);
		rect2.setTextureRect(sf::IntRect(0, 0, 208, 40));
		rect2.setFillColor(sf::Color::Transparent);
	//textbox3 rect
		sf::RectangleShape rect3(sf::Vector2f(241, 40));
		rect3.setPosition(menuText3.getPosition().x - 3, menuText3.getPosition().y + 9);
		rect3.setTextureRect(sf::IntRect(0, 0, 241, 40));
		rect3.setFillColor(sf::Color::Transparent);
		
		//Initial setting of the ship next to play
		mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y);

	//print text options on screen, highlight when hovered over, assign player position to current selection, check if click is pressed in bounds and set to choice, update background flow
	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			//if (event.type == sf::Event::MouseButtonReleased && (mouse.getPosition(window).x >= rect1.getPosition().x && mouse.getPosition(window).x <= rect1.getPosition().x + 80) && (mouse.getPosition(window).y >= rect1.getPosition().y && mouse.getPosition(window).x <= rect1.getPosition().y + 40));
			
			if ((mouse.getPosition(window).x >= rect1.getPosition().x && mouse.getPosition(window).x <= rect1.getPosition().x + 80) && (mouse.getPosition(window).y >= rect1.getPosition().y && mouse.getPosition(window).y <= rect1.getPosition().y + 40))
			{
				//PLAY
				menuText1.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					playMenu();
					mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y - 3);
				}
			}
			else if((mouse.getPosition(window).x >= rect2.getPosition().x && mouse.getPosition(window).x <= rect2.getPosition().x + 208) && (mouse.getPosition(window).y >= rect2.getPosition().y && mouse.getPosition(window).y <= rect2.getPosition().y + 40))
			{
				//HIGHSCORES
				menuText2.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect2.getPosition().x - 50, rect2.getPosition().y);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					highscoresMenu();
					mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y - 3);
				}
			}
			else if ((mouse.getPosition(window).x >= rect3.getPosition().x && mouse.getPosition(window).x <= rect3.getPosition().x + 241) && (mouse.getPosition(window).y >= rect3.getPosition().y && mouse.getPosition(window).y <= rect3.getPosition().y + 40))
			{
				//HOW TO PLAY
				menuText3.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect3.getPosition().x - 50, rect3.getPosition().y);
				if (event.type == sf::Event::MouseButtonReleased)   //mouse.isButtonPressed(mouse.Left)
				{
					howToPlayMenu();
					mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y - 3);
				}
			}
			else
			{
				menuText1.setColor(sf::Color::Blue);
				menuText2.setColor(sf::Color::Blue);
				menuText3.setColor(sf::Color::Blue);
			}
		}

		//constant flow of background
		if (bg2Position.y >= screenDimensions.y)
			bg2Position.y = -screenDimensions.y;
		if (bg1Position.y >= screenDimensions.y)
			bg1Position.y = -screenDimensions.y;

		//handle mouse events
		//print text options to screen

		//Update 
		bg1Position.y += .01;
		bgImage1.setPosition(bg1Position.x, bg1Position.y);
		bg2Position.y += .01;
		bgImage2.setPosition(bg2Position.x, bg2Position.y);

		window.draw(bgImage2);
		window.draw(bgImage1);

		//according to mouse position
		window.draw(mPlayer1.playerImage);
		//	window.draw(rect);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
			//Draw menu to screen, plane should be set to the location of the currently selected option
		window.draw(menuText1);
		window.draw(menuText2);
		window.draw(menuText3);
		window.display();
		window.clear();

	}

}

//Jared
void Game::playMenu(void)
{
	//textbox1 rect Campaign
	sf::RectangleShape rect1(sf::Vector2f(170, 40));
	rect1.setPosition(playMenuText2.getPosition().x - 3, playMenuText2.getPosition().y + 9);
	rect1.setTextureRect(sf::IntRect(0, 0, 170, 40));
	rect1.setFillColor(sf::Color::Transparent);
	//textbox2 rect Multi-player
	sf::RectangleShape rect2(sf::Vector2f(230, 40));
	rect2.setPosition(playMenuText3.getPosition().x - 3, playMenuText3.getPosition().y + 9);
	rect2.setTextureRect(sf::IntRect(0, 0, 230, 40));
	rect2.setFillColor(sf::Color::Transparent);
	//textbox3 rect Endless
	sf::RectangleShape rect3(sf::Vector2f(148, 40));
	rect3.setPosition(playMenuText4.getPosition().x - 3, playMenuText4.getPosition().y + 9);
	rect3.setTextureRect(sf::IntRect(0, 0, 148, 40));
	rect3.setFillColor(sf::Color::Transparent);
	//textbox4 rect Back
	sf::RectangleShape rect4(sf::Vector2f(92, 40));
	rect4.setPosition(playMenuText5.getPosition().x - 3, playMenuText5.getPosition().y + 9);
	rect4.setTextureRect(sf::IntRect(0, 0, 92, 40));
	rect4.setFillColor(sf::Color::Transparent);

	mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y - 3);

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();

			//set these to the rect sizes and change rect sizes
			if ((mouse.getPosition(window).x >= rect1.getPosition().x && mouse.getPosition(window).x <= rect1.getPosition().x + 170) && (mouse.getPosition(window).y >= rect1.getPosition().y && mouse.getPosition(window).y <= rect1.getPosition().y + 40))
			{
				//Campaign
				playMenuText2.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect1.getPosition().x - 50, rect1.getPosition().y - 3);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					cout << "mouse event for Campaign activated." << endl;
					playCampaign();
					return; //Return to main menu after playing game mode
				}
			}
			else if ((mouse.getPosition(window).x >= rect2.getPosition().x && mouse.getPosition(window).x <= rect2.getPosition().x + 230) && (mouse.getPosition(window).y >= rect2.getPosition().y && mouse.getPosition(window).y <= rect2.getPosition().y + 40))
			{
				//Multi-Player
				playMenuText3.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect2.getPosition().x - 50, rect2.getPosition().y - 3);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					cout << "Mouse event for Multiplayer activated." << endl;
					playMultiplayer();
					return; //Return to main menu after playing game mode
				}
			}
			else if ((mouse.getPosition(window).x >= rect3.getPosition().x && mouse.getPosition(window).x <= rect3.getPosition().x + 148) && (mouse.getPosition(window).y >= rect3.getPosition().y && mouse.getPosition(window).y <= rect3.getPosition().y + 40))
			{
				//Endless
				playMenuText4.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect3.getPosition().x - 50, rect3.getPosition().y - 3);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					cout << "Mouse event for Endless activated." << endl;
					playEndless();
					return; //Return to main menu after playing game mode
				}
			}
			else if ((mouse.getPosition(window).x >= rect4.getPosition().x && mouse.getPosition(window).x <= rect4.getPosition().x + 92) && (mouse.getPosition(window).y >= rect4.getPosition().y && mouse.getPosition(window).y <= rect4.getPosition().y + 40))
			{
				//Back
				playMenuText5.setColor(sf::Color::Cyan);
				mPlayer1.playerImage.setPosition(rect4.getPosition().x - 50, rect4.getPosition().y - 3);
				if (event.type == sf::Event::MouseButtonReleased)
				{
					//playMultiplayer();
					cout << "Mouse event for Back activated." << endl;
					return; //Return to previous menu
				}
			}
			else
			{
				playMenuText2.setColor(sf::Color::Blue);
				playMenuText3.setColor(sf::Color::Blue);
				playMenuText4.setColor(sf::Color::Blue);
				playMenuText5.setColor(sf::Color::Blue);
			}
		}


		//constant flow of background
		if (bg2Position.y >= screenDimensions.y)
			bg2Position.y = -screenDimensions.y;
		if (bg1Position.y >= screenDimensions.y)
			bg1Position.y = -screenDimensions.y;

		//handle mouse events
		//print text options to screen

		//Update 
		bg1Position.y += .01;
		bgImage1.setPosition(bg1Position.x, bg1Position.y);
		bg2Position.y += .01;
		bgImage2.setPosition(bg2Position.x, bg2Position.y);

		window.draw(bgImage2);
		window.draw(bgImage1);

		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(rect4);

		window.draw(mPlayer1.playerImage);
		window.draw(playMenuText1);
		window.draw(playMenuText2);
		window.draw(playMenuText3);
		window.draw(playMenuText4);
		window.draw(playMenuText5);

		window.display();
		window.clear();
	}
}

//Jared
void Game::playCampaign(bool isMulti)
{
	campaignSplashScreen1();
	//build single player campaign then just set player two options to true is is multi is true
}
void Game::campaignSplashScreen1(void)
{
	//print Misson message or images to introduce level depending on structure
	//Intro story goes here before gameplay begins
}

//Jared
void Game::playMultiplayer(void)
{
	//display multiplayer game modes to choose, endless, multiplayer campaign, others?
	//play game mode with isMulti set to true.

	//		SELECT GAME MODE
	//			Campaign
	//			Endless
	//			Others?
	//

	//call game mode function with multi set to true

	//multiplayerSplashScreen();
}
void Game::multiplayerSplashScreen(void)
{

}

//Jared
void Game::playEndless(bool isMultiPlayer)
{
	endlessSplashScreen();

	//Play loop immediatley after splashscreen
}
void Game::endlessSplashScreen()
{

}


//Matt
void Game::highscoresMenu(void)
{

}

//Donny
void Game::howToPlayMenu(void)
{

}


	//enum PlaneLevel {High, Medium, Base};

	//sf::Vector2i source(1, Base);

	//test rect
	/*sf::RectangleShape rect(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(sf::Vector2f(40, 400));*/

	//Initial backdrop image positions for seamless looping and player image position
//	bg1Position.x = screenDimensions.x;
//	bg1Position.y = -screenDimensions.y;
//
//	bg2Position.x = screenDimensions.x;
//	bg2Position.y = 0;
//
//	playerPosition.x = screenDimensions.x / 2 - 31;
//	playerPosition.y = screenDimensions.y / 2 + (screenDimensions.y / 4);
//	playerImage.setPosition(playerPosition);
//
//	//Text
//	sf::Text menuText1("Play", font, 40);
//	menuText1.setColor(sf::Color(sf::Color::Blue));
//	//text.setStyle(sf::Text::Bold);
//	menuText1.setPosition(sf::Vector2f(230, 200));
//	
//	//test rect
//	sf::RectangleShape rect(sf::Vector2f(20, 20));
//	rect.setPosition(300, 300);
//	rect.setFillColor(sf::Color::Cyan);
//	rect.setTextureRect(sf::IntRect(0, 0, 20, 20));
//
//	//update game loop
//	while (window.isOpen()) {
//
//		//constant flow of background
//		if (bg2Position.y >= screenDimensions.y)
//			bg2Position.y = -screenDimensions.y;
//		if (bg1Position.y >= screenDimensions.y)
//			bg1Position.y = -screenDimensions.y;
//		
//		//Collision detection with edges
//		if (playerImage.getPosition().x + 40 >= screenDimensions.x) //RIGHT SIDE BOUNDARY
//			playerImage.setPosition(screenDimensions.x - 40, playerImage.getPosition().y);
//		if (playerImage.getPosition().x <= 0)						//LEFT SIDE BOUNDARY
//			playerImage.setPosition(0, playerImage.getPosition().y);
//		if (playerImage.getPosition().y <= 0)						//TOP BOUNDARY
//			playerImage.setPosition(playerImage.getPosition().x, 0);
//		if (playerImage.getPosition().y + 42 >= screenDimensions.y) //BOTTOM BOUDNARY
//			playerImage.setPosition(playerImage.getPosition().x, screenDimensions.y - 42);
//
//		//enemy collision detection incomplete
//		if (playerImage.getGlobalBounds().intersects(rect.getGlobalBounds()))
//			playerIsHit = true;
//		else
//			playerIsHit = false;
//
//		if (playerIsHit)
//			playerImage.setColor(sf::Color::Red);
//		else
//			playerImage.setColor(sf::Color::White);
//
//		//clock.restart(); //restart clock for real time updating
//		clock.restart();
//
//		sf::Event event;
//
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed)
//				window.close();
//			if (event.key.code == sf::Keyboard::Escape)
//				window.close();
//		}
//		
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//			playerImage.move(.1, 0); // OR   playerImage.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//			playerImage.move(-.1, 0); // OR   playerImage.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//			playerImage.move(0, -.1);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//			playerImage.move(0, .1);
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//		{
//			//Fire Bullets
//		}
//		
//		/*if (isMultiplayer)
//		{
//			//MultiPlayer
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//			player2Image.move(.1, 0); // OR   player2Image.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//			player2Image.move(-.1, 0); // OR   player2Image.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//			player2Image.move(0, -.1);
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//			player2Image.move(0, .1);
//		} */
//
//		bg1Position.y += .01;
//		bgImage1.setPosition(bg1Position.x, bg1Position.y);
//		bg2Position.y += .01;
//		bgImage2.setPosition(bg2Position.x, bg2Position.y);
//		
//		//rect.setPosition(rect.getPosition().x + 0.01, rect.getPosition().y);
//		//cout << "x: " <<bg2Position.x << " y: " << bg2Position.y << endl;
//		window.draw(bgImage2);
//		window.draw(bgImage1);
//
//		window.draw(playerImage);
//		window.draw(rect);
//		
//		//Draw menu to screen, plane should be set to the location of the currently selected option
//		window.draw(menuText1);
//		window.display();
//		window.clear();
//	}
//}