#pragma once

#include "../Model.h"
#include "../Camera.h"
#include "../Shaders/Shader.h"

class CubeRenderer
{
public:
	CubeRenderer();

	void addCube(glm::vec3 pos);
	void render(Camera& cam);

	~CubeRenderer();
private:
	std::vector<glm::vec3> m_queue;
	Shader m_shader;
	Model m_cubeModel;
	sf::Texture tex;
};

