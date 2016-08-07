#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
class CollisionMap
{
private:
	int rectWidth = 32;
	int rectHeight = 32;

public:

	bool drawRects = false;
	std::vector<sf::RectangleShape> rects;
	void setup(int width, int height);
	CollisionMap();
	~CollisionMap();
};

