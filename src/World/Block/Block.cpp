#include "Block.h"
//#include <bitset>

/*Block::Block(BlockId id)	:	id(id)
{

}

BlockDataCompressed Block::compress()
{
	union
	{
		BlockDataCompressed block;
		unsigned int intBlock;
	};
	//BlockDataCompressed block;
	block.ID = id;
	uint8_t X = static_cast<uint8_t>(pos.x) * 16;
	uint8_t Y = static_cast<uint8_t>(pos.y)	* 16;
	uint8_t Z = static_cast<uint8_t>(pos.z);
	uint8_t XZ = X + Z;
	uint8_t Y_Facing = Y + static_cast<uint8_t>(dir);

	block.XZ = XZ;
	block.Y_Facing = Y_Facing;

	//globalTemp = intBlock;

	return block;
}*/

Block::Block(BlockId id)	:	id(id)
{

}

std::string Block::getTextureName(Facing dir)
{
	/*switch (dir)
	{
		case Facing::
	}*/
	return std::string("dirt");
}
