#pragma once

#include "../Texture/Texture.h"
#include <vector>
#include <unordered_map>
#include <array>
#include "FileUtil.h"
#include "../mesh.h"

class ResourceManager
{
public:
	ResourceManager();

	void addImg(sf::Image img, const std::string texName);

	sf::Image& getSheet();
	std::array<float, 8> getTexCoords(const std::string texName);

	~ResourceManager();
private:
	void buildTextureSheet();

	std::unordered_map<std::string, std::array<float, 8>> m_blockTexCoordsMap;
	std::vector<std::pair<sf::Image, std::string>> imgs;
	sf::Image sheet;
};