#include "EnemyManager.h"

void EnemyManager::addEnemy(float positionX, float positionY)
{
	Enemy enemy;
	enemy.rect.setPosition(positionX, positionY);
	enemyArray.push_back(enemy);
}

void EnemyManager::deleteRemovedEnemies()
{
	int counter = 0;
	for (iter = enemyArray.begin(); iter != enemyArray.end(); iter++)
	{
		if (enemyArray[counter].remove == true)
		{
			enemyArray.erase(iter);
			break;
		}
		counter++;
	}
}

void EnemyManager::drawEnemies(sf::RenderWindow * window)
{
	if (enemyArray.size() > 0)
	{
		for (int i = 0; i < enemyArray.size(); i++) {
			window->draw(enemyArray[i].rect);
		}
	}
}

void EnemyManager::checkMouseOverEnemies(sf::RenderWindow *window)
{
	for (int i = 0; i < enemyArray.size(); i++)
	{
		if (enemyArray[i].rect.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
		{
			enemyArray[i].mousedOver = true;
		}
		else {
			enemyArray[i].mousedOver = false;
		}
	}
}

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
