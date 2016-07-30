#pragma once
#include <vector>
#include "Tile.h"

class TileMap : public sf::Transformable
{

private:
	int width = 32;
	int height = 24;
	int depth = 1;

public:
	std::vector<Tile> tileArray;

	void save();
	void load();
	void newMap(sf::Texture *texture);
	void draw(sf::RenderWindow *window);
	void placeTiles();
	void checkMouseOverTile(sf::RenderWindow *window);
	void drawTileRects(sf::RenderWindow *window);

	TileMap();
	~TileMap();
};

