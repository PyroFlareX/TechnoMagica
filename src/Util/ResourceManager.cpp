#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	sf::Image filler;
	filler.create(16, 16, sf::Color::Green);
	for (int x = 4; x <= 12; x++)
	{
		for (int y = 4; y <= 12; y++)
		{
			filler.setPixel(x, y, sf::Color::Blue);
		}
	}
	addImg(filler, "temp");
}

void ResourceManager::addImg(sf::Image img, const std::string texName)
{
	imgs.push_back({ img, texName });
}

void ResourceManager::buildTextureSheet()
{
	unsigned int x = 0, y = 0;
	sf::Image sheet;
	sheet.create(256, 16 * ((imgs.size() / 16) + 1));

	sf::Vector2f offsetXY = sf::Vector2f(0.125f, sheet.getSize().y / 16.0f);

	for (auto& image : imgs)
	{
		sheet.copy(image.first, x * 16, y);

		std::array<float, 8> texCoords;
		texCoords[0] = (float)(offsetXY.x * x);
		texCoords[1] = (float)(offsetXY.y * y);
		texCoords[2] = (float)(offsetXY.x + offsetXY.x * x);
		texCoords[3] = (float)(offsetXY.y * y);
		texCoords[4] = (float)(offsetXY.x + offsetXY.x * x);	
		texCoords[5] = (float)(offsetXY.y + offsetXY.y * y);
		texCoords[6] = (float)(offsetXY.x * x);
		texCoords[7] = (float)(offsetXY.y + offsetXY.y * y);

		m_blockTexCoordsMap.insert({ image.second, texCoords });

		++x;
		if (x >= 16)
		{
			x = 0;
			y += 16;
		}
	}
}

sf::Texture* ResourceManager::getSheet()
{
	return &tex;
}

std::array<float, 8> ResourceManager::getTexCoords(const std::string texName)
{
	std::unordered_map<std::string, std::array<float, 8>>::const_iterator iter = m_blockTexCoordsMap.find(texName);
	return iter->second;
}

ResourceManager::~ResourceManager()
{
	imgs.clear();
}
