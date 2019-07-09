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
			std::cout << "Going Right!\n";
			momentum.x++;
		}
		else
			if (vInput.left)
			{
				std::cout << "Going Left!\n";
				momentum.x--;
			}
			else
				if (vInput.up)
				{
					std::cout << "Going Up!\n";
					momentum.y++;
				}
				else
					if (vInput.down)
					{
						std::cout << "Going Down!\n";
						momentum.y--;
					}
					else
						if (vInput.forth)
						{
							std::cout << "Going Forward!\n";
							momentum.z--;
						}
						else
							if (vInput.backwards)
							{
								std::cout << "Going Back!\n";
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
		momentum *= dt;
		/// Collision Detection Here

	}
}

void GameState::lateUpdate(Camera* cam)
{
	cam->move(momentum);
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
