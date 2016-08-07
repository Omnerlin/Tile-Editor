#pragma once
#include "SFML\Graphics.hpp"
#include "Tile.h"

class TileMapGuide
{
private:
	std::vector<sf::RectangleShape> rects;
	
	sf::Texture texture;

public:

	std::vector<Tile> tiles;
	Tile selectedTile;
	int rectWidth = 32;
	int rectHeight = 32;
	sf::Sprite sprite;
	void drawRects(sf::RenderWindow *window);
	void placeRects();
	void checkMouseOverTile(sf::RenderWindow *window);
	void selectRectangle();
	TileMapGuide();
	~TileMapGuide();
};

