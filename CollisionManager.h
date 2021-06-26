#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "Common.h"

const int SCREEN_X = 1280;
const int SCREEN_Y = 960;
const int DIV_X = 4;
const int DIV_Y = 4;

class HashTable {
public:
	HashTable(int);

	void Update(vector<sf::Sprite*>);
	bool Check(sf::Sprite*);
	bool Check(sf::Vector2f);
	void Insert(sf::Sprite*);
	void Remove(sf::Sprite*);

	void DebugInfo();
private:
	int ComputeHash(sf::Vector2f);

	vector<list<sf::Sprite*>> mHashTable;
	int mSize;
};

class CollisionManager {
public:
	CollisionManager(World*);

	void Update();
private:
	World* mWorld;
	HashTable* mHashTable;
};

#endif