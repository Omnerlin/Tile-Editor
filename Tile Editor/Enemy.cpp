#include "Enemy.h"



Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color(255, 0, 255, 100));
}


Enemy::~Enemy()
{
}
