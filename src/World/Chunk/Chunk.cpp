#include "Chunk.h"

#include "../../Renderers/Renderer.h"
#include "ChunkMeshBuilder.h"

#include "../World.h"

bool inRange(int n)
{
	return (n >= 0 && n <= 15);
}

Chunk::Chunk(World* p_world, int x, int y, int z)	: p_world(p_world), pos(x, y, z)
{
	for(int i = 0; i < CHUNK_VOLUME; ++i)
	{
		m_blocks[i] = resources::BlockDatabase.getBlock("dirt");
	}
}

const Block& Chunk::getBlock(int x, int y, int z) const
{
	if (!(inRange(x) && inRange(y) && inRange(z)))
	{
		x = getPos().x % 16;
		y = getPos().y % 16;
		z = getPos().z % 16;
	}

	int blockNum = y * CHUNK_AREA + z * CHUNK_SIZE + x;
	if (blockNum < 0)
	{
		std::cout << blockNum;
	}
	return m_blocks.at(blockNum);
}

const sf::Vector3i Chunk::getPos() const
{
	return pos;
}

void Chunk::makeMesh()
{
	ChunkMeshBuilder(*this, mesh).buildMesh();
	mesh.bufferMesh();
	hasMesh = true;
}

void Chunk::deleteMesh()
{
	mesh.deleteData();
}

void Chunk::renderChunk(Renderer& render, const Camera& cam)
{
	if (hasMesh)
	{
		render.drawChunk(mesh);
		std::cout << "Test\n";
	}
	else
	{
		std::cout << "Test2\n";
		makeMesh();
		render.drawChunk(mesh);
	}
}

Chunk::~Chunk()
{

}
