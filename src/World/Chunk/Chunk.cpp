#include "Chunk.h"

Chunk::Chunk()
{
	m_blocks.fill(ChunkBlock(BlockId::DIRT));
}

void Chunk::makeMesh()
{

}

void Chunk::deleteMesh()
{

}

void Chunk::renderChunk(Renderer & render, const Camera & cam)
{
	//render.drawChunk();
}

Chunk::~Chunk()
{

}
