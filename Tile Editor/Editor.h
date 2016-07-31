#pragma once
#include <string>
#include "Tile.h"
#include "TileMap.h"
#include "TileMapGuide.h"


class Editor
{
private:
	int SCREENWIDTH = 1920;
	int SCREENHEIGHT = 1080;
	sf::Texture *mapTexture = new sf::Texture;
	sf::RenderWindow *window = new sf::RenderWindow;
	sf::View view;
	sf::View tileMapView;
	TileMap tileMap;
	TileMapGuide mapGuide;
	std::string fileName;
public:
	void update();
	void init();
	void printMenu();
	int getResponse();
	Editor();
	~Editor();
};

