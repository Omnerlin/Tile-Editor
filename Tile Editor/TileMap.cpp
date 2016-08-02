#include "TileMap.h"




TileMap::TileMap()
{
	setPosition(0, 0);
}

void TileMap::placeTiles()
{
	int row = -1;
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

void TileMap::changeTiles(Tile tile)
{
	for (int i = 0; i < tileArray.size(); i++)
	{
		if (tileArray[i].drawRect && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			tileArray[i].sprite.setTextureRect(sf::IntRect(sf::IntRect(tile.rect.getPosition().x, tile.rect.getPosition().y, tile.width, tile.height)));
			tileArray[i].index = tile.index;
		}
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

void TileMap::save(std::string fileName)
{
	std::ofstream mapFile;
	mapFile.open(fileName);
	mapFile << width << "\n";
	mapFile << height << "\n";
	mapFile << depth << "\n";

	for (int i = 0, j = 0; i < tileArray.size(); i++, j++)
	{
		if( i % width == 0)
		{
			mapFile << "\n";
		}
		mapFile << tileArray[i].index << " ";
	}

	mapFile.close();
	std::cout << "Map File Saved To: " << fileName << std::endl;
}

void TileMap::load(std::string fileName, sf::Texture *texture, TileMapGuide mapGuide)
{
	std::ifstream mapFile;
	mapFile.open(fileName);
	mapFile >> width;
	mapFile >> height;
	mapFile >> depth;

	for (int i = 0; i < width*height; i++)
	{
		Tile tile;
		tile.sprite.setTexture(*texture);
		mapFile >> tile.index;
		//(tiles[i].rect.getPosition().x, tiles[i].rect.getPosition().y, tiles[i].width, tiles[i].height)
		tile.sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tile.index].rect.getPosition().x, mapGuide.tiles[tile.index].rect.getPosition().y, tile.width,tile.height));
		
		tileArray.push_back(tile);
	}

	mapFile.close();
	std::cout << "Map Loaded from file: " << fileName << std::endl;
	placeTiles();
}

TileMap::~TileMap()
{

}
