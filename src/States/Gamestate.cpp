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
		glm::vec3(-2.0f, -2.0f, -3.0f),
		glm::vec3(-4.0f, -2.0f, -12.0f),
		glm::vec3(2.0f, -1.0f, -4.0f),
		glm::vec3(-2.0f,  3.0f, -8.0f),
		glm::vec3(1.0f, -2.0f, -3.0f),
		glm::vec3(2.0f,  2.0f, -3.0f),
		glm::vec3(2.0f,  0.0f, -2.0f),
		glm::vec3(-1.0f,  1.0f, -2.0f)
	};
	for (int i = 0; i < 10; ++i)
	{
		Entity entity;
		entity.pos = cubePositions[i];
		renderer->drawCube(entity);
	}

	/*sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::White);
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(sf::Vector2f(400, 550));
	renderer->drawSFML(rect);*/

	//renderer->drawCube(glm::vec3(0.0f, 0.0f, -5.0f));
}

void GameState::tryPause()
{
	TryPause = true;
}
