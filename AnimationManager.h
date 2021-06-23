#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Common.h"

using namespace std;

class AnimationManager {
public:
	AnimationManager(World*);
	void Update();
	void Reset();

private:
	World* mWorld;

	sf::Clock mAnimationClock;
	unsigned mFrameTime;
};

#endif