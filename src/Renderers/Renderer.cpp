#include "Renderer.h"

Renderer::Renderer()
{
    //ctor
}

void Renderer::drawSFML(const sf::Drawable& drawable)
{
	m_SFMLRenderer.addToQueue(drawable);
}

void Renderer::drawCube(Entity& entity)
{
	m_cubeRenderer.addCube(entity);
}

void Renderer::render(Camera& cam, sf::RenderWindow* window)
{
	m_cubeRenderer.render(cam);
	m_SFMLRenderer.render(window);
}

Renderer::~Renderer()
{
    //dtor
}
