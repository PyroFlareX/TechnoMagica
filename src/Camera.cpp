#include "Camera.h"

Camera::Camera(sf::RenderWindow* p_win)
{
	p_window = p_win;
	lerp = 2.5f;
}


void Camera::move(glm::vec3& movement)
{
	float y = cameraPos.y;
	cameraPos -= movement.z * lerp * cameraFront;
	cameraPos += movement.x * lerp * glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraPos.y = y;
	cameraPos += movement.y * lerp * cameraUp;

	movement = glm::vec3(0.0f);
}

void Camera::rotate(glm::vec3& rotationOffset)
{
	rotationOffset * 1.55f;
	rot.x += rotationOffset.x;
	rot.y += rotationOffset.y;

	//Rotation Clamping
	if (rot.y > 89.0f) { rot.y = 89.0f; }
	if (rot.y < -89.0f) { rot.y = -89.0f; }

	glm::vec3 front;
	front.x = cos(glm::radians(rot.y)) * cos(glm::radians(rot.x));
	front.y = sin(glm::radians(rot.y));
	front.z = cos(glm::radians(rot.y)) * sin(glm::radians(rot.x));

	rotationOffset = glm::vec3(0.0f);

	cameraFront = glm::normalize(front);
}

Camera::~Camera()
{

}
