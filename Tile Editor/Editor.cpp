#include "Editor.h"

Editor::Editor()
{
}

void Editor::printMenu()
{
	std::cout << "Choose an option:" << std::endl;
	std::cout << "1. New Map" << std::endl;
	std::cout << "2. Load Map" << std::endl;
}

int Editor::getResponse()
{
	int response = 0;

	while (response != 1 && response != 2)
	{
		std::cin >> response;
	}
	return response;
}

void Editor::init()
{
	mapGuide.placeRects();
	printMenu();

	int mapChoice = getResponse();
	std::cout << "Choose the filename: ";
	std::cin >> fileName;
	fileName += ".txt";

	if (mapChoice == 1)
	{
		int mapWidth = 0;
		std::cout << "Choose map width: ";
		std::cin >> mapWidth;
		tileMap.width = mapWidth;
		tileMap2.width = mapWidth;

		int mapHeight = 0;
		std::cout << "Choose map height: ";
		std::cin >> mapHeight;
		tileMap.height = mapHeight;
		tileMap2.height = mapHeight;

		//int mapDepth = 0;
		//std::cout << "Choose map depth: ";
		//std::cin >> mapDepth;
		tileMap.depth = 1;
		tileMap2.depth = 2;
		tileMap.newMap(mapTexture);
		tileMap2.newMap(mapTexture);

		for (int i = 0; i < tileMap2.tileArray.size(); i++)
		{
			tileMap2.tileArray[i].index = -1;
			tileMap2.tileArray[i].rect.setFillColor(sf::Color(0, 0, 200, 50));
			tileMap2.tileArray[i].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
	}

	else if (mapChoice == 2)
	{
		load(fileName, mapTexture, mapGuide);
	}

	window->create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "AdventureGame");
	window->setVerticalSyncEnabled(true);

	mapTexture->loadFromFile("Media\\tileMap.png");
	

	// Set Up Guide View
	tileMapView.setViewport(sf::FloatRect(0, 0, 0.45, 1));

	// Set up Map View
	view.setViewport(sf::FloatRect(0.4, 0, 1, 1));
	view.setCenter(window->getDefaultView().getCenter().x-100, window->getDefaultView().getCenter().y);
	view.setSize(window->getDefaultView().getSize().x, window->getDefaultView().getSize().y);
}

bool Editor::updateCurrentLayer(sf::Time elapsed)
{
	layerSwitchTime = elapsed.asSeconds();
	
	if (layerSwitchTime > 1.5 && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		if (currentLayer == 1)
		{
			currentLayer = 2;
			std::cout << "Switched to layer 2" << std::endl;
			return true;
		}
		else if (currentLayer == 2)
		{
			std::cout << "Switched to layer 1" << std::endl;
			currentLayer = 1;
			return true;
		}
	}
	return false;
}

void Editor::load(std::string fileName, sf::Texture *texture, TileMapGuide mapGuide)
{
	std::ifstream mapFile;
	mapFile.open(fileName);

	mapFile >> tileMap.width;
	mapFile >> tileMap.height;
	mapFile >> tileMap.depth;

	for (int i = 0; i < tileMap.width*tileMap.height; i++)
	{
		Tile tile;
		tile.sprite.setTexture(*texture);
		mapFile >> tile.index;
		tile.sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tile.index].rect.getPosition().x, mapGuide.tiles[tile.index].rect.getPosition().y, tile.width, tile.height));

		tileMap.tileArray.push_back(tile);
	}
	tileMap.placeTiles();

	mapFile >> tileMap2.width;
	mapFile >> tileMap2.height;
	mapFile >> tileMap2.depth;

	for (int j = 0; j < tileMap2.width*tileMap2.height; j++)
	{
		Tile tile;
		tile.sprite.setTexture(*texture);
		mapFile >> tile.index;

		if (tile.index > -1)
		{
			tile.sprite.setTextureRect(sf::IntRect(mapGuide.tiles[tile.index].rect.getPosition().x, mapGuide.tiles[tile.index].rect.getPosition().y, tile.width, tile.height));
		}
		else
		{
			tile.sprite.setTextureRect(sf::IntRect(0,0,0,0));
		}
		tileMap2.tileArray.push_back(tile);
	}
	tileMap2.placeTiles();

	mapFile.close();
	std::cout << "Map Loaded from file: " << fileName << std::endl;
	
}

void Editor::save(std::string fileName)
{
	std::ofstream mapFile;
	mapFile.open(fileName);
	mapFile << tileMap.width << "\n";
	mapFile << tileMap.height << "\n";
	mapFile << tileMap.depth << "\n";

	for (int i = 0, j = 0; i < tileMap.tileArray.size(); i++, j++)
	{
		if (i % tileMap.width == 0)
		{
			mapFile << "\n";
		}
		mapFile << tileMap.tileArray[i].index << " ";
	}

	mapFile << "\n";

	mapFile << tileMap2.width << "\n";
	mapFile << tileMap2.height << "\n";
	mapFile << tileMap2.depth << "\n";

	for (int i = 0, j = 0; i < tileMap2.tileArray.size(); i++, j++)
	{
		if (i % tileMap2.width == 0)
		{
			mapFile << "\n";
		}
		mapFile << tileMap2.tileArray[i].index << " ";
	}

	mapFile.close();
	std::cout << "Map File Saved To: " << fileName << std::endl;
}

void Editor::update()
{
	sf::Clock clock;
	sf::Clock editorClock;
	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta > 0) {
					view.zoom(0.9);
				}
				else if (event.mouseWheel.delta < 0) {
					view.zoom(1.1);
				}
				else
				{
					view.zoom(1.0);
				}
				window->setView(view);
			}
		}

		sf::Time elapsed = clock.getElapsedTime();
		sf::Time editorElapsed = editorClock.getElapsedTime();


		if (updateCurrentLayer(editorElapsed) == true)
		{
			editorClock.restart();
		}

		
		if (currentLayer == 1)
		{
			tileMap.changeTiles(mapGuide.selectedTile);
			tileMap.checkMouseOverTile(window);
		}
		else if (currentLayer == 2) {
			tileMap2.changeTiles(mapGuide.selectedTile);
			tileMap2.checkMouseOverTile(window);
		}

		window->clear();
		// Draw and Switch Views
		sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		window->setView(view);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

			if (converted.x > view.getCenter().x)
			{
				view.move(-2, 0);
			}
			else if (converted.x < view.getCenter().x)
			{
				view.move(2, 0);
			}
			if ((converted.y > view.getCenter().y))
			{
				view.move(0, -2);
			}
			else if (converted.y > view.getCenter().y)
			{
				view.move(0, 2);
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && elapsed.asSeconds() > 6)
		{
			save(fileName);
			clock.restart();
		}

		tileMap.draw(window);
		tileMap.drawTileRects(window);
		tileMap2.draw(window);
		tileMap2.drawTileRects(window);
		
		
		window->setView(tileMapView);
		mapGuide.checkMouseOverTile(window);
		mapGuide.selectRectangle();
		window->draw(mapGuide.sprite);
		mapGuide.drawRects(window);
		window->setView(view);
		window->display();
		//editorClock.restart();
	}
}

Editor::~Editor()
{
	delete window;
	delete mapTexture;
}
