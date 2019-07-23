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

void Renderer::doCompute()
{
//	m_computeRenderer.
}

void Renderer::drawChunk(Entity & entity)
{
	m_chunkRenderer.addChunk(entity);
}

void Renderer::render(Camera& cam, sf::RenderWindow* window)
{
	m_cubeRenderer.render(cam);
	m_SFMLRenderer.render(window);
//	m_computerRenderer.render();
}

Renderer::~Renderer()
{
    //dtor
}
