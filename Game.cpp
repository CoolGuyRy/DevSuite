#include "Game.h"

Entity::Entity(sf::RenderWindow* w, sf::Texture& t) :mWindow(w) {
	mSprite.setTexture(t);
}
void Entity::Update() {

}
void Entity::Render() {
	mWindow->draw(mSprite);
}

Game::Game(string s) {
	mResourceManager = new ResourceManager("Data/resources.rsc");
	mAnimationManager = new AnimationManager(&mWorld);

	mWindow.create(sf::VideoMode(1280, 960), "Game v0.3", sf::Style::Close);

	mWorld.world_name = s;

	mResourceManager->getSong("DruidCity").setVolume(2.0f);
	mResourceManager->getSong("DruidCity").setLoop(true);
	mResourceManager->getSong("DruidCity").setPlayingOffset(sf::seconds(0.5f));
	mResourceManager->getSong("DruidCity").play();

	Load();
	Run();
}
void Game::Run() {
	while (mWindow.isOpen()) {
		Input();
		Update(mDeltaTime.asSeconds());
		Render();

		mDeltaTime = mDeltaClock.restart();
	}
}
void Game::Input() {
	while (mWindow.pollEvent(mEvent)) {
		if (mEvent.type == sf::Event::Closed) {
			mWindow.close(); exit(0);
		}
		if (mEvent.type == sf::Event::KeyPressed) {
			if (mEvent.key.code == sf::Keyboard::LControl) {
				mInputContainer.keyboard_Ctrl = true;
			}
			if (mEvent.key.code == sf::Keyboard::LAlt) {
				mInputContainer.keyboard_Alt = true;
			}
			if (mEvent.key.code == sf::Keyboard::LShift) {
				mInputContainer.keyboard_Shift = true;
			}
			if (mEvent.key.code == sf::Keyboard::F1) {
				mInputContainer.keyboard_F1 = true;
			}
			if (mEvent.key.code == sf::Keyboard::F2) {
				mInputContainer.keyboard_F2 = true;
			}
			if (mEvent.key.code == sf::Keyboard::W) {
				mInputContainer.keyboard_W = true;
			}
			if (mEvent.key.code == sf::Keyboard::A) {
				mInputContainer.keyboard_A = true;
			}
			if (mEvent.key.code == sf::Keyboard::S) {
				mInputContainer.keyboard_S = true;
			}
			if (mEvent.key.code == sf::Keyboard::D) {
				mInputContainer.keyboard_D = true;
			}
			if (mEvent.key.code == sf::Keyboard::Up) {
				mInputContainer.keyboard_Up = true;
			}
			if (mEvent.key.code == sf::Keyboard::Left) {
				mInputContainer.keyboard_Left = true;
			}
			if (mEvent.key.code == sf::Keyboard::Down) {
				mInputContainer.keyboard_Down = true;
			}
			if (mEvent.key.code == sf::Keyboard::Right) {
				mInputContainer.keyboard_Right = true;
			}
			if (mEvent.key.code == sf::Keyboard::O) {
				mInputContainer.keyboard_O = true;
			}
			if (mEvent.key.code == sf::Keyboard::G) {
				mInputContainer.keyboard_G = true;
			}
		}
		if (mEvent.type == sf::Event::KeyReleased) {
			if (mEvent.key.code == sf::Keyboard::LControl) {
				mInputContainer.keyboard_Ctrl = false;
			}
			if (mEvent.key.code == sf::Keyboard::LAlt) {
				mInputContainer.keyboard_Alt = false;
			}
			if (mEvent.key.code == sf::Keyboard::LShift) {
				mInputContainer.keyboard_Shift = false;
			}
			if (mEvent.key.code == sf::Keyboard::F1) {
				mInputContainer.keyboard_F1 = false;
			}
			if (mEvent.key.code == sf::Keyboard::F2) {
				mInputContainer.keyboard_F2 = false;
			}
			if (mEvent.key.code == sf::Keyboard::W) {
				mInputContainer.keyboard_W = false;
			}
			if (mEvent.key.code == sf::Keyboard::A) {
				mInputContainer.keyboard_A = false;
			}
			if (mEvent.key.code == sf::Keyboard::S) {
				mInputContainer.keyboard_S = false;
			}
			if (mEvent.key.code == sf::Keyboard::D) {
				mInputContainer.keyboard_D = false;
			}
			if (mEvent.key.code == sf::Keyboard::Up) {
				mInputContainer.keyboard_Up = false;
			}
			if (mEvent.key.code == sf::Keyboard::Left) {
				mInputContainer.keyboard_Left = false;
			}
			if (mEvent.key.code == sf::Keyboard::Down) {
				mInputContainer.keyboard_Down = false;
			}
			if (mEvent.key.code == sf::Keyboard::Right) {
				mInputContainer.keyboard_Right = false;
			}
			if (mEvent.key.code == sf::Keyboard::O) {
				mInputContainer.keyboard_O = false;
			}
			if (mEvent.key.code == sf::Keyboard::G) {
				mInputContainer.keyboard_G = false;
			}
		}
		if (mEvent.type == sf::Event::MouseButtonPressed) {
			if (mEvent.mouseButton.button == sf::Mouse::Left) {
				mInputContainer.mouse_Left = true;
			}
			if (mEvent.mouseButton.button == sf::Mouse::Right) {
				mInputContainer.mouse_Right = true;
			}
			if (mEvent.mouseButton.button == sf::Mouse::Middle) {
				mInputContainer.mouse_Middle = true;
			}
		}
		if (mEvent.type == sf::Event::MouseButtonReleased) {
			if (mEvent.mouseButton.button == sf::Mouse::Left) {
				mInputContainer.mouse_Left = false;
			}
			if (mEvent.mouseButton.button == sf::Mouse::Right) {
				mInputContainer.mouse_Right = false;
			}
			if (mEvent.mouseButton.button == sf::Mouse::Middle) {
				mInputContainer.mouse_Middle = false;
			}
		}
		if (mEvent.type == sf::Event::MouseWheelMoved) {
			mInputContainer.mouse_Wheel = true;

			if (mEvent.mouseWheel.delta > 0) {
				mInputContainer.mouse_Dir = true;
			}
			else {
				mInputContainer.mouse_Dir = false;
			}
		}
	}
}
void Game::Update(float deltaTime) {
	mAnimationManager->Update();
}
void Game::Render() {
	mWindow.clear(sf::Color(4, 5, 18));

	for (auto it = mWorld.worldTiles.begin(); it != mWorld.worldTiles.end(); it++) {
		mWindow.draw(it->spr);
	}
	for (auto it = mWorld.objects.begin(); it != mWorld.objects.end(); it++) {
		mWindow.draw(it->spr);
	}

	mWindow.display();
}

bool Game::Load() {
	ifstream levelFile(mWorld.world_name);
	if (levelFile.fail()) {
		cout << "ERROR: Failed to open file..." << endl;
		return false;
	}

	unsigned worldTileSize, wallTileSize, objectSize;
	levelFile >> worldTileSize >> wallTileSize >> objectSize;

	while (worldTileSize) {
		bool animated;
		unsigned tilePosX, tilePosY, tileSizeX, tileSizeY, posX, posY, cF, fC;
		levelFile >> animated >> tilePosX >> tilePosY >> tileSizeX >> tileSizeY >> posX >> posY >> cF >> fC;

		sf::Sprite tempSprite;
		if (animated) {
			tempSprite.setTexture(mResourceManager->getTexture("aTiles"));
			tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(tilePosX, tilePosY), sf::Vector2i(tileSizeX, tileSizeY)));
			tempSprite.setPosition(sf::Vector2f(posX, posY));
			mWorld.worldTiles.push_back(Tile(sf::Vector2f(tilePosX, tilePosY), sf::Vector2f(tileSizeX, tileSizeY), tempSprite, fC, cF));
		}
		else {
			tempSprite.setTexture(mResourceManager->getTexture("tiles"));
			tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(tilePosX, tilePosY), sf::Vector2i(tileSizeX, tileSizeY)));
			tempSprite.setPosition(sf::Vector2f(posX, posY));
			mWorld.worldTiles.push_back(Tile(sf::Vector2f(tilePosX, tilePosY), sf::Vector2f(tileSizeX, tileSizeY), tempSprite));
		}
		worldTileSize--;
	}

	while (wallTileSize) {
		unsigned posX, posY;
		levelFile >> posX >> posY;

		sf::Sprite tempSprite;
		tempSprite.setTexture(mResourceManager->getTexture("selector"));
		tempSprite.setPosition(sf::Vector2f(posX, posY));
		mWorld.wallTiles.push_back(Tile(sf::Vector2f(0, 0), sf::Vector2f(16, 16), tempSprite));
		wallTileSize--;
	}

	while (objectSize) {
		bool animated;
		string id;
		unsigned tilePosX, tilePosY, tileSizeX, tileSizeY, posX, posY, cF, fC;
		levelFile >> id >> animated >> tilePosX >> tilePosY >> tileSizeX >> tileSizeY >> posX >> posY >> cF >> fC;

		sf::Sprite tempSprite;
		if (animated) {
			tempSprite.setTexture(mResourceManager->getTexture("aObjects"));
			tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(tilePosX, tilePosY), sf::Vector2i(tileSizeX, tileSizeY)));
			tempSprite.setPosition(sf::Vector2f(posX, posY));
			mWorld.objects.push_back(Object(sf::Vector2f(tilePosX, tilePosY), sf::Vector2f(tileSizeX, tileSizeY), tempSprite, fC, cF, id));
		}
		else {
			tempSprite.setTexture(mResourceManager->getTexture("objects"));
			tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(tilePosX, tilePosY), sf::Vector2i(tileSizeX, tileSizeY)));
			tempSprite.setPosition(sf::Vector2f(posX, posY));
			mWorld.objects.push_back(Object(sf::Vector2f(tilePosX, tilePosY), sf::Vector2f(tileSizeX, tileSizeY), tempSprite, id));
		}
		objectSize--;
	}

	levelFile.close();
	return true;
}
