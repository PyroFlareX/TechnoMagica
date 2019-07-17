#pragma once

#include <SFML/Graphics.hpp>
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
	void buildTextureSheet();

	sf::Texture* getSheet();
	std::array<float, 8> getTexCoords(const std::string texName);

	~ResourceManager();
private:
	std::unordered_map<std::string, std::array<float, 8>> m_blockTexCoordsMap;
	sf::Texture tex;
	std::vector<std::pair<sf::Image, std::string>> imgs;
	std::vector<Mesh> meshes;
};