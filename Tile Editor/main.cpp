#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"

int main()
{
	const int SCREENWIDTH = 1920;
	const int SCREENHEIGHT = 1080;

	sf::Texture *mapTexture = new sf::Texture;
	mapTexture->loadFromFile("Media\\tileMap.png");
	


	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Tile Editor!");
	window->setVerticalSyncEnabled(true);

	TileMap tileMap;
	tileMap.newMap(mapTexture);

	sf::View view;
	sf::View tileMapView;
	view.setCenter(window->getDefaultView().getCenter());
	view.setSize(window->getDefaultView().getSize().x, window->getDefaultView().getSize().y);
	view.setViewport(sf::FloatRect(0.25, 0.25, 0.5, 0.5));
	window->setView(view);
	

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

		sf::Vector2f converted = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			window->setMouseCursorVisible(false);
			sf::Mouse::setPosition(sf::Vector2i(SCREENWIDTH / 2, SCREENHEIGHT / 2), *window);
	
			view.setCenter(converted.x, converted.y);
			window->setView(view);
		}

		else
		{
			window->setMouseCursorVisible(true);
		}

		tileMap.checkMouseOverTile(window);
		window->clear();
		tileMap.draw(window);

		tileMap.drawTileRects(window);
		window->display();
	}


	delete mapTexture;
	delete window;
	return 0;
}