#pragma once

#include "BlockID.h"
#include "../../Entity.h"
/*
struct BlockDataCompressed
{
	uint8_t XZ;
	uint8_t Y_Facing;
	BlockId ID;
};

class Block
{
public:
	Block(BlockId id);
	
	BlockDataCompressed compress();
private:
	BlockId id;
	Facing dir;
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
};

//uint32_t globalTemp;*/

class Block
{
public:
	Block() = default;
	Block(BlockId id);
	BlockId id;

	bool operator ==(Block other) const
	{
		return id == other.id;
	}
	bool operator !=(Block other) const
	{
		return id != other.id;
	}

	std::string getTextureName(Facing dir);
private:

};

