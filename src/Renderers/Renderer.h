#ifndef RENDERER_H
#define RENDERER_H

#include "../Camera.h"
#include "CubeRenderer.h"
#include "../mesh.h"

#include <vector>

class Renderer
{
    public:
        Renderer();

		void drawSFML(sf::Drawable& drawable);
		void drawCube(Entity& entity);
		void render(Camera& cam);

        ~Renderer();
    protected:

    private:
		CubeRenderer m_cubeRenderer;
};

#endif // RENDERER_H
