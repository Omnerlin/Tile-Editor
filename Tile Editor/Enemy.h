#pragma once
#include "SFML\Graphics.hpp"

class Enemy
{
public:
	const static int width = 32;
	const static int height = 32;
	sf::RectangleShape rect;
	bool remove = false;
	bool mousedOver = false;
	Enemy();
	~Enemy();
};

