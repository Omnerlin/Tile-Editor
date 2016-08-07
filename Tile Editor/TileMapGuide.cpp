#include "TileMapGuide.h"
#include <iostream>


TileMapGuide::TileMapGuide()
{
	texture.loadFromFile("Media\\tileMap.png");
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	for (int i = 0; i < (texture.getSize().x / rectWidth) *(texture.getSize().y / rectHeight); i++)
	{
		Tile tile;
		tile.sprite.setTexture(texture);
		tile.index = i;
		tiles.push_back(tile);
	}
}

void TileMapGuide::selectRectangle()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].drawRect && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			selectedTile.rect.setPosition(tiles[i].rect.getPosition());
			selectedTile.sprite.setPosition(tiles[i].rect.getPosition());
			selectedTile.index = tiles[i].index;
			tiles[i].sprite.setTextureRect(sf::IntRect(tiles[i].rect.getPosition().x, tiles[i].rect.getPosition().y, tiles[i].width, tiles[i].height));
		}
	}
}

void TileMapGuide::placeRects()
{
	
	int row = -1;
	for (int i = 0, j = 0; i < tiles.size(); i++, j++)
	{
		
		if (i % (texture.getSize().x / rectWidth) == 0) {
			row++;
			j = 0;
		}

		tiles[i].rect.setPosition(j * rectWidth, row * rectHeight);
		tiles[i].sprite.setPosition(tiles[i].rect.getPosition());
		tiles[i].sprite.setTextureRect(sf::IntRect(tiles[i].rect.getPosition().x, tiles[i].rect.getPosition().y, tiles[i].width,tiles[i].height));
	}
}


void TileMapGuide::checkMouseOverTile(sf::RenderWindow *window)
{
	sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	//sf::Vector2i converted = (sf::Mouse::getPosition(*window));

	for (int i = 0; i < tiles.size(); i++)
	{
		if (converted.x > tiles[i].rect.getPosition().x && converted.x < (tiles[i].rect.getPosition().x + tiles[i].rect.getSize().x) &&
			converted.y > tiles[i].rect.getPosition().y && converted.y < tiles[i].rect.getPosition().y + tiles[i].rect.getSize().y) {
			tiles[i].drawRect = true;
		}
		else {
			tiles[i].drawRect = false;
		}
	}
}

void TileMapGuide::drawRects(sf::RenderWindow *window) {
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].drawRect == true)
		{
			window->draw(tiles[i].rect);
		}
	}
	window->draw(selectedTile.rect);
}

TileMapGuide::~TileMapGuide()
{
}
