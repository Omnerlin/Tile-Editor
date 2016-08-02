#pragma once
#include <string>
#include "Tile.h"
#include "TileMap.h"
#include "TileMapGuide.h"


class Editor
{
private:
	sf::Text layerText;
	int SCREENWIDTH = 1920;
	int SCREENHEIGHT = 1080;
	float layerSwitchTime = 0;
	sf::Texture *mapTexture = new sf::Texture;
	sf::RenderWindow *window = new sf::RenderWindow;
	sf::View view;
	sf::View tileMapView;
	TileMap tileMap;
	TileMap tileMap2;
	TileMapGuide mapGuide;
	std::string fileName;
	int currentLayer = 1;

public:
	bool updateCurrentLayer(sf::Time elapsed);
	void save(std::string fileName);
	void load(std::string fileName, sf::Texture *texture, TileMapGuide mapGuide);
	void update();
	void init();
	void printMenu();
	int getResponse();
	Editor();
	~Editor();
};

