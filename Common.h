#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

struct InputContainer {
	// Generic
	bool mouse_Left = false;
	bool mouse_Right = false;
	bool mouse_Middle = false;
	bool mouse_Wheel = false;
	bool mouse_Dir = false;			// 1 - up 0 - down

	// Level Editor
	bool keyboard_Ctrl = false;
	bool keyboard_Alt = false;
	bool keyboard_Shift = false;
	bool keyboard_W = false;
	bool keyboard_A = false;
	bool keyboard_S = false;
	bool keyboard_D = false;
	bool keyboard_Up = false;
	bool keyboard_Left = false;
	bool keyboard_Down = false;
	bool keyboard_Right = false;
	bool keyboard_O = false;
	bool keyboard_G = false;
	bool keyboard_F1 = false;
	bool keyboard_F2 = false;
};

struct Selector {
	sf::Vector2f startPos, currentPos;
	sf::RectangleShape spr;
};

struct Tile {
	Tile(sf::Vector2f pos, sf::Vector2f size, sf::Sprite s) : tilePos(pos), tileSize(size), spr(s) { animated = false; frameCount = 0; currentFrame = 0; }
	Tile(sf::Vector2f pos, sf::Vector2f size, sf::Sprite s, unsigned fc, unsigned cf) : tilePos(pos), tileSize(size), spr(s), frameCount(fc), currentFrame(cf) { animated = true; }

	sf::Vector2f tilePos;
	sf::Vector2f tileSize;
	sf::Sprite spr;
	unsigned frameCount, currentFrame;
	bool animated;
};

struct Object {
	Object(sf::Vector2f index, sf::Vector2f size, sf::Sprite s) : tilePos(index), tileSize(size), spr(s) { animated = false; frameCount = 0; currentFrame = 0; }
	Object(sf::Vector2f index, sf::Vector2f size, sf::Sprite s, string name) : tilePos(index), tileSize(size), spr(s), id(name) { animated = false; frameCount = 0; currentFrame = 0; }
	Object(sf::Vector2f index, sf::Vector2f size, sf::Sprite s, unsigned fc, unsigned cf) : tilePos(index), tileSize(size), spr(s), frameCount(fc), currentFrame(cf) { animated = true; }
	Object(sf::Vector2f index, sf::Vector2f size, sf::Sprite s, unsigned fc, unsigned cf, string name) : tilePos(index), tileSize(size), spr(s), frameCount(fc), currentFrame(cf), id(name) { animated = true; }
	
	sf::Vector2f tilePos;
	sf::Vector2f tileSize;
	sf::Sprite spr;
	string id;

	unsigned frameCount, currentFrame;
	bool animated;
};

struct World {
	string world_name;

	vector<Tile> worldTiles;
	vector<Tile> wallTiles;
	vector<Object> objects;
};

#endif