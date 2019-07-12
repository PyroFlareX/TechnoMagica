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
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (int i = 0; i < 10; ++i)
	{
		renderer->drawCube(cubePositions[i]);
	}
	renderer->drawCube(glm::vec3(0.0f, 0.0f, -5.0f));
}

void GameState::tryPause()
{
	TryPause = true;
}
