#include "AnimationManager.h"

AnimationManager::AnimationManager(World* w) : mWorld(w) {
	mFrameTime = 125;
}

void AnimationManager::Update() {
	if (mAnimationClock.getElapsedTime().asMilliseconds() > mFrameTime) {
		for (unsigned i = 0; i < mWorld->worldTiles.size(); i++) {
			if (mWorld->worldTiles.at(i).animated) {
				if (mWorld->worldTiles.at(i).currentFrame + 1 == mWorld->worldTiles.at(i).frameCount) {
					mWorld->worldTiles.at(i).currentFrame = 0;
				}
				else {
					mWorld->worldTiles.at(i).currentFrame++;
				}
				mWorld->worldTiles.at(i).spr.setTextureRect(sf::IntRect(sf::Vector2i(mWorld->worldTiles.at(i).tilePos.x + mWorld->worldTiles.at(i).currentFrame * mWorld->worldTiles.at(i).tileSize.x, mWorld->worldTiles.at(i).tilePos.y), sf::Vector2i(mWorld->worldTiles.at(i).tileSize.x, mWorld->worldTiles.at(i).tileSize.y)));
			}
		}
		for (unsigned i = 0; i < mWorld->objects.size(); i++) {
			if (mWorld->objects.at(i).animated) {
				if (mWorld->objects.at(i).currentFrame + 1 == mWorld->objects.at(i).frameCount) {
					mWorld->objects.at(i).currentFrame = 0;
				}
				else {
					mWorld->objects.at(i).currentFrame++;
				}
				mWorld->objects.at(i).spr.setTextureRect(sf::IntRect(sf::Vector2i(mWorld->objects.at(i).tilePos.x + mWorld->objects.at(i).currentFrame * mWorld->objects.at(i).tileSize.x, mWorld->objects.at(i).tilePos.y), sf::Vector2i(mWorld->objects.at(i).tileSize.x, mWorld->objects.at(i).tileSize.y)));
			}
		}
		mAnimationClock.restart();
	}
}

void AnimationManager::Reset() {
	for (unsigned i = 0; i < mWorld->worldTiles.size(); i++) {
		if (mWorld->worldTiles.at(i).animated) {
			mWorld->worldTiles.at(i).currentFrame = 0;
		}
	}
}