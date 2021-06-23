#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"
#include "AnimationManager.h"
#include "Common.h"

using namespace std;

class LevelEditor {
public:
	LevelEditor(string);
private:
	void Run();

	void Input();
	void Update();
	void Render();

	bool Save();
	bool Load();

	World mWorld;

	vector<string> mSheets;
	sf::Sprite mSheetSprite;
	int mCurrentSheet;

	ResourceManager* mResourceManager;
	AnimationManager* mAnimationManager;

	sf::RenderWindow eWindow, tWindow;
	sf::Event mEvent;
	sf::View mView;

	InputContainer mInputContainer;
	Selector mSelector;
	bool eTransparent, eDrawWall;
};

#endif