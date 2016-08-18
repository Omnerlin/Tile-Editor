#pragma once
#include <string>
#include "Tile.h"
#include "TileMap.h"
#include "TileMapGuide.h"


class Editor
{
private:
	sf::Text currentLayerText;
	sf::Text layerOneShown;
	sf::Text layerTwoShown;
	sf::Text collisionMapShown;
	std::vector<sf::Text> gridX;
	std::vector<sf::Text> gridY;

	sf::Font font;
	sf::RectangleShape textRect;

	int SCREENWIDTH = 1920;
	int SCREENHEIGHT = 1080;

	float layerSwitchTime = 0;
	sf::Texture *mapTexture = new sf::Texture;
	sf::RenderWindow *window = new sf::RenderWindow;
	sf::View textView;
	sf::View view;
	sf::View tileMapView;


	CollisionMap collisionMap;
	TileMap tileMap;
	TileMap tileMap2;
	TileMapGuide mapGuide;
	std::string fileName;
	int currentLayer = 1;
	float layerOneToggleTime = 0;
	float layerTwoToggleTime = 0;
	bool drawLayerOne = true;
	bool drawLayerTwo = true;

public:
	void setupText();
	void drawGridText();
	void drawCollisions();
	bool toggleDrawLayerOne(sf::Time elapsed);
	bool toggleDrawLayerTwo(sf::Time elapsed);
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

