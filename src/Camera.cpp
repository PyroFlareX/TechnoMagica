#include "Camera.h"

Camera::Camera(sf::RenderWindow* p_win)
{
	p_window = p_win;
	lerp = 2.5f;

	proj = makeProjectionMatrix(60.0f, (sf::Vector2i)(p_window->getSize()));

	pos = glm::vec3(0.0f, 0.0f, 3.0f);
	rot = glm::vec3(0.0f);
}

void Camera::follow(Entity& entity)
{
	p_entity = &entity;
}

void Camera::update()
{
	pos = p_entity->pos;
	rot = p_entity->rot;
}

Camera::~Camera()
{

}
