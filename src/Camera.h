#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(sf::RenderWindow* p_win);

	~Camera();
private:
	sf::RenderWindow* p_window;
};

