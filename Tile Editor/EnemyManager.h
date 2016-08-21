#pragma once
#include "Enemy.h"
#include <vector>
class EnemyManager
{
private:

public:
	std::vector<Enemy>::const_iterator iter;
	std::vector<Enemy> enemyArray;
	void addEnemy(float positionX, float PositionY);
	void deleteRemovedEnemies();
	void drawEnemies(sf::RenderWindow *window);
	void checkMouseOverEnemies(sf::RenderWindow *window);
	EnemyManager();
	~EnemyManager();
};

