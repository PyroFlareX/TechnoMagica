#include "Input.h"
#include <iostream>

Input::Inputs Input::getInput()
{
	Input::Inputs input = { false, false, false, false, false, false, sf::Vector2i(0,0)};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		input.forth = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		input.backwards = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		input.left = true;
	}		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		input.right = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		input.up = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		input.down = true;
	}
	input.mousePos = sf::Mouse::getPosition();
	
	return input;
}
