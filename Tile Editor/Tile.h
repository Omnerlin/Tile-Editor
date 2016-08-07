#pragma once
#include "SFML\Graphics.hpp"
class Tile
{

private:

public:
	int index;
	int width = 32;
	int height = 32;
	bool drawRect = false;
	bool collidable = false;

	sf::Texture texture;
	sf::RectangleShape rect;
	sf::Sprite sprite;

	Tile();
	~Tile();
};

