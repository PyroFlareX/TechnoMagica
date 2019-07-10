#include "GameState.h"

#include <iostream>
#include "../Util/math.h"

GameState::GameState()
{
	TryPause = false;
}

GameState::~GameState()
{

}

bool GameState::input(Application &app)
{
	if (!isPaused)
	{
		vInput = Input::getInput();

		if (vInput.right)
		{
			momentum.x++;
		}
		if (vInput.left)
		{
			momentum.x--;
		}
		if (vInput.up)
		{
			momentum.y++;
		}
		if (vInput.down)
		{
			momentum.y--;
		}
		if (vInput.forth)
		{
			momentum.z--;
		}
		if (vInput.backwards)
		{
			momentum.z++;
		}
	}
	return false;
}

void GameState::update(sf::RenderWindow* window, float dt)
{
	if (window->hasFocus() && !TryPause)
	{
		isPaused = false;
	}
	else
	{
		isPaused = true;
		TryPause = false;
	}

	if (!isPaused)
	{
		static auto oldMousePos = sf::Mouse::getPosition(*window);
		sf::Vector2i offset = sf::Mouse::getPosition(*window) - sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2);//oldMousePos;
		rotation.y -= offset.y;
		rotation.x += offset.x;
		//std::cout << rotation.x << " " << rotation.y << "\n";
		momentum *= dt;
		rotation *= dt;
		/// Collision Detection Here
		//std::cout << rotation.x << " " << rotation.y << "\n";
	}
	sf::Mouse::setPosition(sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2), *window);
}

void GameState::lateUpdate(Camera* cam)
{
	cam->move(momentum);
	cam->rotate(rotation);
}

void GameState::render(Renderer* renderer)
{

}

void GameState::tryPause()
{
	TryPause = true;
}

bool GameState::isColliding(sf::Vector2f playerPos)
{
	/// Collision Detection Here
	
	// @TODO : Add Other Collisions
	return false;
}
