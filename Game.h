#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Common.h"
#include "ResourceManager.h"
#include "AnimationManager.h"

using namespace std;

class Game {
public:
	Game(string);
private:
	void Run();

	void Input();
	void Update(float);
	void Render();

	bool Load();

	World mWorld;

	ResourceManager* mResourceManager;
	AnimationManager* mAnimationManager;

	sf::RenderWindow mWindow;
	sf::Event mEvent;
	InputContainer mInputContainer;

	sf::Clock mDeltaClock;
	sf::Time mDeltaTime;
};

#endif