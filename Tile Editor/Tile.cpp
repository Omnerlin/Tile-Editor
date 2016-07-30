#include "Tile.h"



Tile::Tile() : index(0)
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color(255, 0, 0, 40));
	sprite.setTextureRect(sf::IntRect(32*5, 32*4, 32, 32));
}


Tile::~Tile()
{
}
