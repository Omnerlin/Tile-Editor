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

void respondToInput(int response)
{
	if (response == 1) {

	}
	else if (response == 2) {

	}
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

		int mapHeight = 0;
		std::cout << "Choose map height: ";
		std::cin >> mapHeight;
		tileMap.height = mapHeight;

		int mapDepth = 0;
		std::cout << "Choose map depth: ";
		std::cin >> mapDepth;
		tileMap.depth = mapDepth;
		tileMap.newMap(mapTexture);
	}

	else if (mapChoice == 2)
	{
		tileMap.load(fileName, mapTexture, mapGuide);
	}

	window->create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "AdventureGame");
	window->setVerticalSyncEnabled(true);

	mapTexture->loadFromFile("Media\\tileMap.png");
	

	// Set Up Guide View
	tileMapView.setViewport(sf::FloatRect(0, 0, 0.45, 1));

	// Set up Map View
	view.setViewport(sf::FloatRect(0.4, 0, 1, 1));
	view.setCenter(window->getDefaultView().getCenter());
	view.setSize(window->getDefaultView().getSize().x, window->getDefaultView().getSize().y);
}

void Editor::update()
{
	sf::Clock clock;
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

		tileMap.changeTiles(mapGuide.selectedTile);
		tileMap.checkMouseOverTile(window);

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
			//std::cout << "T pressed" << std::endl;
			tileMap.save(fileName);
			clock.restart();
			
		}

		//window->setKeyRepeatEnabled(true);
		tileMap.draw(window);
		tileMap.drawTileRects(window);
		

		window->setView(tileMapView);
		mapGuide.checkMouseOverTile(window);
		mapGuide.selectRectangle();
		window->draw(mapGuide.sprite);
		mapGuide.drawRects(window);
		window->setView(view);
		window->display();
	}
}





Editor::~Editor()
{
	delete window;
	delete mapTexture;
}
