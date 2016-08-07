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
	std::string prefix = "SavedMaps\\";
	std::cin >> fileName;
	prefix += fileName;
	fileName = prefix;
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

		tileMap.depth = 1;
		tileMap2.depth = 2;
		tileMap.newMap(mapTexture);
		tileMap2.newMap(mapTexture);
		collisionMap.setup(tileMap.width, tileMap.height);


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

	font.loadFromFile("Fonts\\gameplay.ttf");
	currentLayerText.setFont(font);
	layerOneShown.setFont(font);
	layerTwoShown.setFont(font);

	currentLayerText.setString("Current Layer: Layer One"); currentLayerText.setCharacterSize(70);
	layerOneShown.setString("Layer One: Shown"); layerOneShown.setCharacterSize(70);
	layerTwoShown.setString("Layer Two: Shown"); layerTwoShown.setCharacterSize(70);
	textRect.setFillColor(sf::Color(0, 0, 0, 50));
	

	currentLayerText.setPosition(0, 0);
	layerOneShown.setPosition(0, 120);
	layerTwoShown.setPosition(0, 240);


	window->create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "AdventureGame");
	window->setVerticalSyncEnabled(true);

	mapTexture->loadFromFile("Media\\tileMap.png");
	

	// Set Up Guide View
	tileMapView.setViewport(sf::FloatRect(0, 0, 0.45, 1));

	// Set up Text ViewPort
	textView.setSize(window->getDefaultView().getSize());
	textRect.setSize(sf::Vector2f(textView.getSize().x - 100, textView.getSize().y - 700));
	textView.setViewport(sf::FloatRect(0.24, 0, 0.4, 0.4));



	// Set up Map View
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	view.setSize(window->getDefaultView().getSize().x, window->getDefaultView().getSize().y);
	view.setCenter(view.getSize().x / 2 - 500, view.getSize().y / 2);

	setupText();
}

bool Editor::updateCurrentLayer(sf::Time elapsed)
{
	layerSwitchTime = elapsed.asSeconds();
	
	if (layerSwitchTime > 1.5 && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		if (currentLayer == 1)
		{
			currentLayer = 2;
			currentLayerText.setString("Current Layer: Layer Two");
			return true;
		}
		else if (currentLayer == 2)
		{
			currentLayerText.setString("Current Layer: Layer One");
			currentLayer = 1;
			return true;
		}
	}
	return false;
}

bool Editor::toggleDrawLayerOne(sf::Time elapsed)
{
	layerOneToggleTime = elapsed.asSeconds();

	if (layerOneToggleTime > 0.3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (drawLayerOne == true)
		{
			drawLayerOne = false;
			layerOneShown.setString("Layer One: Hidden");
			return true;
		}
		else if (drawLayerOne == false)
		{
			layerOneShown.setString("Layer One: Shown");
			drawLayerOne = true;
			return true;
		}
	}
	return false;
}

bool Editor::toggleDrawLayerTwo(sf::Time elapsed)
{
	layerTwoToggleTime = elapsed.asSeconds();

	if (layerTwoToggleTime > 0.3 && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (drawLayerTwo == true)
		{
			drawLayerTwo = false;
			layerTwoShown.setString("Layer Two: Hidden");
			return true;
		}
		else if (drawLayerTwo == false)
		{
			layerTwoShown.setString("Layer Two: Shown");
			drawLayerTwo = true;
			return true;
		}
	}

	return false;
}

void Editor::drawCollisions() {
	if (collisionMap.drawRects)
	{
		for (int i = 0; i < collisionMap.rects.size(); i++) {
			if (tileMap.tileArray[i].collidable == true)
			{
				window->draw(collisionMap.rects[i]);
			}

		}
	}
}

void Editor::setupText()
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	char letter = 65;
	sf::Uint8 number = 0;

	for (int i = 0, j = 0; i < tileMap.height; i++, j++)
	{
		text.setString(letter);
		text.setPosition(0 - tileMap.tileArray[i].width, (i * tileMap.tileArray[i].height));
		gridY.push_back(text);
		letter++;
	}
	for (int i = 0; i < tileMap.width; i++)
	{
		text.setString(std::to_string(number));
		if (number < 10)
		{
			text.setPosition((i * tileMap.tileArray[i].width) + tileMap.tileArray[i].width / 4, (0 - tileMap.tileArray[i].height));
		}
		else
		{
			text.setPosition((i * tileMap.tileArray[i].width), (0 - tileMap.tileArray[i].height));
		}
		gridX.push_back(text);
		number++;
	}

}

void Editor::drawGridText()
{
	for (int i = 0; i < tileMap.width; i++)
	{
		window->draw(gridX[i]);
	}
	for (int i = 0; i < tileMap.height; i++)
	{
		window->draw(gridY[i]);
	}
}

void Editor::load(std::string fileName, sf::Texture *texture, TileMapGuide mapGuide)
{
	std::ifstream mapFile;
	mapFile.open(fileName);

	mapFile >> tileMap.width;
	mapFile >> tileMap.height;
	mapFile >> tileMap.depth;

	for (int i = 0; i < (tileMap.width*tileMap.height); i++)
	{
		Tile tile;
		tile.sprite.setTexture(*texture);
		mapFile >> tile.index;
		mapFile >> tile.collidable;
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
	collisionMap.setup(tileMap.width, tileMap.height);

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

		if (tileMap.tileArray[i].collidable == true)
		{
			mapFile << 1 << " ";
		}
		else
		{
			mapFile << 0 << " ";
		}

		
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
		//mapFile << tileMap2.tileArray[i].collidable << " ";
	}

	mapFile.close();
	std::cout << "Map File Saved To: " << fileName << std::endl;
}

void Editor::update()
{
	sf::Clock clock;
	sf::Clock editorClock;
	sf::Clock layerToggleClock;
	sf::Clock collisionClock;
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
		sf::Time layerToggleTime = layerToggleClock.getElapsedTime();
		sf::Time collisionToggleTime = collisionClock.getElapsedTime();

		if (updateCurrentLayer(editorElapsed) == true)
		{
			editorClock.restart();
		}

		if (toggleDrawLayerOne(layerToggleTime) == true || toggleDrawLayerTwo(layerToggleTime) == true)
		{
			layerToggleClock.restart();
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
			else if (converted.y < view.getCenter().y)
			{
				view.move(0, 2);
			}
			
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && elapsed.asSeconds() > 6)
		{
			save(fileName);
			clock.restart();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && collisionToggleTime.asSeconds() > 0.5)
		{
			if (collisionMap.drawRects == false)
			{
				collisionMap.drawRects = true;
				collisionClock.restart();
			}
			else if (collisionMap.drawRects == true)
			{
				collisionMap.drawRects = false;
				collisionClock.restart();
			}
		}


		if (drawLayerOne == true)
		{
			tileMap.draw(window);
			tileMap.drawTileRects(window);
		}

		if (drawLayerTwo == true)
		{
			tileMap2.draw(window);
			tileMap2.drawTileRects(window);
		}

		
		
		window->setView(tileMapView);
		mapGuide.checkMouseOverTile(window);
		mapGuide.selectRectangle();
		window->draw(mapGuide.sprite);
		mapGuide.drawRects(window);
		window->setView(view);
		drawGridText();
		window->setView(textView);
		window->draw(textRect);
		window->draw(currentLayerText);
		window->draw(layerOneShown);
		window->draw(layerTwoShown);
		window->setView(view);
		if (collisionMap.drawRects)
		{
			drawCollisions();
		}
		window->display();
	}
}

Editor::~Editor()
{
	delete window;
	delete mapTexture;
}
