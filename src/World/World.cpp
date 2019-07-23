#include "World.h"



World::World(const Camera& cam, Player& player)	:	m_chunkManager(*this)
{
	//loadThreads.push_back(std::thread(loadChunks, cam));
	loadChunks(cam);
}

void World::update()
{

}

void World::renderWorld(const Camera& cam, Renderer& renderer)
{
	m_chunkManager.getChunk(0, 0, 0).renderChunk(renderer, cam);
}

World::~World()
{
    //dtor
}

void World::loadChunks(const Camera& cam)
{
	//while (isRunning)
	//{
	//	m_chunkManager.loadChunk()
	//}
	m_chunkManager.loadChunk(0, 0, 0);
	return;
}
