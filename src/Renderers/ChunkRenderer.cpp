#include "ChunkRenderer.h"
#include "../Texture/TextureAtlas.h"


ChunkRenderer::ChunkRenderer()
{
	tex.loadFromImage(resManager.getSheet());
}

void ChunkRenderer::addChunk(ChunkMesh & mesh)
{
	m_queue.push_back(&mesh.getModel().getInfo());
}

void ChunkRenderer::render(Camera & cam)
{
	m_shader.use();
	tex.bind();


	m_shader.setMat4("view", cam.getViewMatrix(cam));
	m_shader.setMat4("proj", cam.getProjMatrix());

	glEnable(GL_CULL_FACE);

	for (auto& mesh : m_queue)
	{
		glBindVertexArray(mesh->VAO);

		glDrawElements(GL_TRIANGLES, mesh->indiciesCount, GL_UNSIGNED_INT, nullptr);
	}
	m_queue.clear();
}

ChunkRenderer::~ChunkRenderer()
{

}
