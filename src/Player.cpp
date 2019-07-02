#include "Player.h"


Player::Player()
{
	
}

sf::FloatRect Player::getBounds()
{
	return Character.getGlobalBounds();
}


Player::~Player()
{

}
