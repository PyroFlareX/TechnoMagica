#pragma once

#include "../../Entity.h"
#include <array>
#include "../Block/Block.h"
#include "../../Renderers/Renderer.h"

constexpr int CHUNK_SIZE = 16;

class Chunk : public Entity
{
public:
	Chunk();

	void makeMesh();
	void deleteMesh();

	void renderChunk(Renderer& render, const Camera& cam);

	~Chunk();
private:
	std::array<ChunkBlock, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE> m_blocks;

	bool hasMesh = false;
};