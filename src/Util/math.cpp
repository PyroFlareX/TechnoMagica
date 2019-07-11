#include "math.h"

#include "../Camera.h"

glm::mat4 makeViewMatrix(const Camera & camera)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(camera.rot.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rot.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rot.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -camera.pos);

	return matrix;
}

glm::mat4 makeModelMatrix(const Entity & entity)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(entity.rot.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rot.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rot.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, entity.pos);

	return matrix;
}

glm::mat4 makeProjectionMatrix(float fov, sf::Vector2i winSize)
{
	return glm::perspective(glm::radians(fov), (float)(winSize.x / winSize.y), 0.1f, 1000.0f);
}