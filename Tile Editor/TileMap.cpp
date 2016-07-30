#include "TileMap.h"



TileMap::TileMap()
{
	setPosition(0, 0);
}

void TileMap::placeTiles()
{

	int row = 0;
	for (int i = 0, j = 0; i < width*height; i++, j++) {
		if (i % width == 0) {
			row++;
			j = 0;
		}
		tileArray[i].rect.setPosition(j * tileArray[i].width, row * tileArray[i].height);
		tileArray[i].sprite.setPosition(j * tileArray[i].width, row * tileArray[i].height);
	}
}

void TileMap::newMap(sf::Texture *texture)
{
	Tile tile;
	tile.sprite.setTexture(*texture);
	for (int i = 0; i < width*height; i++) {
		tileArray.push_back(tile);
	}
	placeTiles();
}

void TileMap::drawTileRects(sf::RenderWindow *window)
{
	for (int i = 0; i < tileArray.size(); i++)
	{
		if(tileArray[i].drawRect == true)
		window->draw(tileArray[i].rect);
	}
}

void TileMap::checkMouseOverTile(sf::RenderWindow *window)
{
	sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	
	for (int i = 0; i < tileArray.size(); i++)
	{
		if (converted.x > tileArray[i].rect.getPosition().x && converted.x < (tileArray[i].rect.getPosition().x + tileArray[i].rect.getSize().x) &&
			converted.y > tileArray[i].rect.getPosition().y && converted.y < tileArray[i].rect.getPosition().y + tileArray[i].rect.getSize().y) {
			tileArray[i].drawRect = true;
		}
		else {
			tileArray[i].drawRect = false;
		}
	}
}

void TileMap::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < tileArray.size(); i++)
	{
		window->draw(tileArray[i].sprite);
	}
}

void TileMap::save()
{

}

void TileMap::load()
{

}

TileMap::~TileMap()
{

}
