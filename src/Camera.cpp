#include "Camera.h"

Camera::Camera(sf::RenderWindow* p_win)
{
	p_window = p_win;
	lerp = 2.5f;
}


void Camera::move(glm::vec3& movement)
{
	cameraPos -= movement.z * lerp * cameraFront;
	cameraPos += movement.x * lerp * glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraPos += movement.y * lerp * cameraUp;

	movement = glm::vec3(0.0f);
}

void Camera::rotate(glm::vec3& rotationOffset)
{
	rotationOffset * lerp;
	yaw += rotationOffset.x;
	pitch += rotationOffset.y;

	//Rotation Clamping
	if (pitch > 89.0f) { pitch = 89.0f; }
	if (pitch < -89.0f) { pitch = -89.0f; }

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	rotationOffset = glm::vec3(0.0f);

	cameraFront = glm::normalize(front);
}

Camera::~Camera()
{

}
