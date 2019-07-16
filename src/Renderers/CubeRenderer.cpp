#include "CubeRenderer.h"


CubeRenderer::CubeRenderer()
{
	m_shader.load("res/Shaders/vert.glsl", "res/Shaders/frag.glsl");

	img.loadFromFile("res/Textures/Blocks.png");
	//tex.i
	tex.loadFromImage(img);
	tex.bind(&tex, sf::Texture::CoordinateType::Pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//These are commented out because of GL_LINEAR making textures blurry

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);


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
		//Back
		0.125f, 0.0625f,	//TR
		0.0625f, 0.0625f,	//TL
		0.0625f, 0.0f,		//BL
		0.125f, 0.0f,		//BR

		//Front
		0.125f, 0.0625f,	//TR
		0.0625f, 0.0625f,	//TL
		0.0625f, 0.0f,		//BL
		0.125f, 0.0f,		//BR

		//Right
		0.125f, 0.0625f,	//TR
		0.0625f, 0.0625f,	//TL
		0.0625f, 0.0f,		//BL
		0.125f, 0.0f,		//BR

		//Left
		0.125f, 0.0625f,	//TR
		0.0625f, 0.0625f,	//TL
		0.0625f, 0.0f,		//BL
		0.125f, 0.0f,		//BR
		
		//Top
		0.1875f, 0.0f,
		0.25f, 0.0f,
		0.25f, 0.0625f,
		0.1875f, 0.0625f,

		//Bottom
		0.0625f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0625f,
		0.0625f, 0.0625f
	};

	m_cubeModel.addData({ vertexCoords, indices, texCoords});
}

void CubeRenderer::addCube(Entity& entity)
{
	m_queue.push_back(entity);
}

void CubeRenderer::render(Camera& cam)
{
	m_shader.use();
	m_cubeModel.bindVAO();
	sf::Texture::bind(&tex, sf::Texture::CoordinateType::Pixels);

	m_shader.setMat4("view", cam.getViewMatrix(cam));
	m_shader.setMat4("proj", cam.getProjMatrix());

	glEnable(GL_CULL_FACE);

	for (auto& entity : m_queue)
	{
		m_shader.setMat4("model", makeModelMatrix(entity));

		glDrawElements(GL_TRIANGLES, m_cubeModel.getNumIndicies(), GL_UNSIGNED_INT, nullptr);
	}
	m_queue.clear();
}

CubeRenderer::~CubeRenderer()
{

}
