#include "Player.h"

Player::Player()
{
	if (!playerTexture.loadFromFile("airFighter48.png")) //http://freegameassets.blogspot.com/2013_08_01_archive.html		  Photo Credit
		std::cout << "Could not load image" << std::endl;

	playerImage.setTexture(playerTexture);
	playerImage.setTextureRect(sf::IntRect(4, 4, 40, 42)); //Biggest plane on sprite sheet
	sf::Vector2f playerPosition(0, 0);
	playerImage.setPosition(playerPosition);
}
Player::~Player()
{

}