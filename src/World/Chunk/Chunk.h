#pragma once

#include <SFML/Graphics.hpp>
#include "../../Entity.h"

class Chunk : public Entity
{
public:
	Chunk();

	void makeMesh();

	~Chunk();
private:

};