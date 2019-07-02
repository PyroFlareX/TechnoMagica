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
	Input::Inputs input;
	if (!isPaused)
	{
		input = Input::getInput();

		if (input.right)
		{
			std::cout << "Going Right!\n";
		}
		else
			if (input.left)
			{
				std::cout << "Going Left!\n";
			}
			else
				if (input.up)
				{
					std::cout << "Going Up!\n";
					
				}
				else
					if (input.down)
					{
						std::cout << "Going Down!\n";
					}
					else
						if (input.forth)
						{
							std::cout << "Going Forward!\n";
						}
						else
							if (input.backwards)
							{
								std::cout << "Going Back!\n";
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
		
		/// Collision Detection Here

	}
}

void GameState::lateUpdate(Camera* cam)
{
	
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
