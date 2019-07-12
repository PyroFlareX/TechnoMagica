#include "Renderer.h"

Renderer::Renderer()
{
    //ctor
}

void Renderer::drawSFML(sf::Drawable& drawable)
{
	//m_queue.push_back(&drawable);
}

void Renderer::drawCube(glm::vec3 pos)
{
	m_cubeRenderer.addCube(pos);
}

void Renderer::render(Camera& cam)
{
	m_cubeRenderer.render(cam);
}

Renderer::~Renderer()
{
    //dtor
}
