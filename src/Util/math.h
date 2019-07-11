#pragma once

#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera;
class Entity;

inline sf::Vector2f lerp(sf::Vector2f current, sf::Vector2f target, float gradient)
{
	return sf::Vector2f((target - current) * gradient + current);
}

const glm::mat4 makeViewMatrix(const Camera& camera);

const glm::mat4 makeModelMatrix(const Entity& entity);

//constexpr glm::mat4 makeProjectionMatrix(const float fov);
const glm::mat4 makeProjectionMatrix(float fov, sf::Vector2i winSize);