#include "CollisionMap.h"

void CollisionMap::setup(int width, int height) {
	sf::RectangleShape rect;

	int row = -1;
	for (int i = 0; i < width*height; i++)
	{
		rect.setSize(sf::Vector2f(rectWidth, rectHeight));
		rect.setFillColor(sf::Color(255, 255, 255, 150));
		rects.push_back(rect);
	}
	for (int i = 0, j = 0; i < rects.size(); i++, j++)
	{
		if (i % width == 0)
		{
			row++;
			j = 0;
		}
		rects[i].setPosition(j * rectWidth, row * rectHeight);
	}
}

CollisionMap::CollisionMap()
{
}

CollisionMap::~CollisionMap()
{
}
