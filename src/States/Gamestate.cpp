#include "GameState.h"

#include <iostream>


GameState::GameState()
{
	TryPause = false;
}

GameState::~GameState()
{

}

bool GameState::input(Application& app)
{
	if (!isPaused)
	{
		vInput = Input::getInput();

		m_player.getInput(vInput);

		
		if (vInput.pause)
		{
			tryPause();
		}
	}
	return false;
}

void GameState::update(sf::RenderWindow* window, float dt)
{
	if (window->hasFocus() && !TryPause)
	{
		isPaused = false;
		//window->setMouseCursorVisible(false);
	}
	else
	{
		isPaused = true;
		TryPause = false;
		//window->setMouseCursorVisible(true);
	}

	if (!isPaused)
	{
		m_player.update(dt, window);

	}
}

void GameState::lateUpdate(Camera* cam)
{
	cam->follow(m_player);
}

void GameState::render(Renderer* renderer)
{
	renderer->drawCube(glm::vec3(0.0f, 0.0f, -5.0f));
}

void GameState::tryPause()
{
	TryPause = true;
}
