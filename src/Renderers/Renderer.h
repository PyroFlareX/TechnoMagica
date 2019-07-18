#ifndef RENDERER_H
#define RENDERER_H

#include "../Camera.h"
#include "CubeRenderer.h"
#include "SFMLRenderer.h"
#include "ComputeRenderer.h"
#include "../mesh.h"

#include <vector>

class Renderer
{
    public:
        Renderer();

		void drawSFML(const sf::Drawable& drawable);
		void drawCube(Entity& entity);
		void doCompute();
		void render(Camera& cam, sf::RenderWindow* window);

        ~Renderer();
    protected:

    private:
		CubeRenderer m_cubeRenderer;
		SFMLRenderer m_SFMLRenderer;
		ComputeRenderer m_computeRenderer;
};

#endif // RENDERER_H
