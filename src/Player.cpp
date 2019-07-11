#include "Player.h"


Player::Player()
{
	pos = glm::vec3(0.0f, 0.0f, 1.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::getInput(Input::Inputs vInput)
{
	glm::vec3 change = glm::vec3(0.0f);
	if (vInput.right)
	{
		change.x += glm::cos(glm::radians(rot.y));
		change.z += glm::sin(glm::radians(rot.y));
	}
	if (vInput.left)
	{
		change.x += -glm::cos(glm::radians(rot.y));
		change.z += -glm::sin(glm::radians(rot.y));
	}
	if (vInput.up)
	{
		velocity.y++;
		//jump();
	}
	if (vInput.down)
	{
		velocity.y--;
	}
	if (vInput.forth)
	{
		change.x += -glm::cos(glm::radians(rot.y + 90));
		change.z += -glm::sin(glm::radians(rot.y + 90));
	}
	if (vInput.backwards)
	{
		change.x += glm::cos(glm::radians(rot.y + 90));
		change.z += glm::sin(glm::radians(rot.y + 90));
	}

	velocity += change;
}

void Player::jump()
{
	velocity.y++;
}

void Player::update(float dt, sf::RenderWindow* window)
{
	static auto lastMousePosition = sf::Mouse::getPosition(*window);
	auto offset = sf::Mouse::getPosition() - lastMousePosition;

	rot.x += (float)offset.y * dt;
	rot.y += (float)offset.x * dt;


	//velocity.y -= 0.1f;

	pos += velocity * dt;
	velocity *= 0.0f;

	std::cout << "Pos " << pos.x << " " << pos.y << " " << pos.z << "\n";
	std::cout << "Rot " << rot.x << " " << rot.y << " " << rot.z << "\n";


	auto cx = static_cast<int>(window->getSize().x / 2);
	auto cy = static_cast<int>(window->getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, *window);

	lastMousePosition = sf::Mouse::getPosition();
}

Player::~Player()
{

}
