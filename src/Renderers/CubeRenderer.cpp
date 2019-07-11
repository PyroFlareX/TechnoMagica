#include "CubeRenderer.h"


CubeRenderer::CubeRenderer()
{
	m_shader.load("res/Shaders/vert.glsl", "res/Shaders/frag.glsl");

	tex.loadFromFile("res/container.jpg");
	tex.bind(&tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex.generateMipmap();

	tex.bind(NULL);

	std::vector<float> vertexCoords
	{
		//Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		//Left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		//Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		//Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1.
	};

	std::vector<unsigned int> indices
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	std::vector<float> texCoords
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	m_cubeModel.addData({ vertexCoords, indices, texCoords});
}

void CubeRenderer::addCube(glm::vec3 pos)
{
	m_queue.push_back(pos);
}

void CubeRenderer::render(Camera& cam)
{
	m_shader.use();
	m_cubeModel.bindVAO();
	sf::Texture::bind(&tex);

	m_shader.setMat4("view", cam.getViewMatrix(cam));
	m_shader.setMat4("proj", cam.getProjMatrix());

	for (auto& pos : m_queue)
	{
		m_shader.setMat4("model", makeModelMatrix({ pos,{0.0f, 0.0f, 0.0f} }));

		glDrawElements(GL_TRIANGLES, m_cubeModel.getNumIndicies(), GL_UNSIGNED_INT, nullptr);
	}
}

CubeRenderer::~CubeRenderer()
{

}
