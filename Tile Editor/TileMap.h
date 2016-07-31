#pragma once
#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include "Tile.h"
#include "TileMapGuide.h"

class TileMap : public sf::Transformable
{

private:
	

public:
	std::vector<Tile> tileArray;
	int width = 32;
	int height = 24;
	int depth = 1;

	void save(std::string fileName);
	void load(std::string fileName, sf::Texture *texture, TileMapGuide mapGuide);
	void newMap(sf::Texture *texture);
	void draw(sf::RenderWindow *window);
	void placeTiles();
	void checkMouseOverTile(sf::RenderWindow *window);
	void drawTileRects(sf::RenderWindow *window);
	void changeTiles(Tile tile);
	TileMap();
	~TileMap();
};

