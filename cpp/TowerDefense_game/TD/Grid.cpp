#include "Grid.h"
#include <SFML/Graphics.hpp>

static const int BLOCK_NOT_FOR_BUILDING = 257;

Grid::Grid():
	width(30),
	height(20),
	blocks(),
	path()
{
	blocks = {
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,257,257,257,257,257,257,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,24,24,24,24,257,257,257,257,257,257,257,257,257,257,257,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,257,257,257,257,257,257,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24,257,257,257,257,257,257,257,257,257,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24,257,24,24,24,24,24,24,24,24,24,24,24,24},
		{257,257,257,257,257,24,24,24,24,24,24,24,24,24,24,24,24,257,257,257,257,257,257,257,257,257,257,257,257,257},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
		{24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24},
	};
	path = Path{
		Sector{-1, 16},
		Sector{4, 16},
		Sector{4, 4},
		Sector{9, 4},
		Sector{9, 10},
		Sector{14, 10},
		Sector{14, 5},
		Sector{25, 5},
		Sector{25, 12},
		Sector{17, 12},
		Sector{17, 16},
		Sector{30, 16}
	};
}

bool Grid::isBuildingAllowedAt(const Sector& sector) const
{
	return sector.x >= 0 && sector.y >= 0 && sector.x < width && sector.y < height && isBuildingAllowedOn(blockAt(sector));
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sprite;
	sprite.setTexture(*states.texture);
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			sprite.setPosition(static_cast<float>(Sector::SIZE * j), static_cast<float>(Sector::SIZE * i));
			const int block = blockAt(j, i);
			sprite.setTextureRect(textureRectById(block));
			target.draw(sprite, states);
		}
}

bool Grid::isBuildingAllowedOn(int block) const
{
	return block != BLOCK_NOT_FOR_BUILDING;
}
