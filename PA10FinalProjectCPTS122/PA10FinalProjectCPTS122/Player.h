#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <string.h>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	sf::Texture playerTexture;		//Player image texture
	sf::Sprite playerImage;			//Player sprite to hold the image
	float moveSpeed = 1000.0f;		//objects movespeed if using time to determine speed
	sf::Vector2f playerPosition;
private:

};