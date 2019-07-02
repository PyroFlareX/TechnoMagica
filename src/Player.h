#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();

	sf::Sprite Character;

	sf::FloatRect getBounds();

	~Player();
private:

};

