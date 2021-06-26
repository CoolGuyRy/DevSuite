#include "LevelEditor.h"

LevelEditor::LevelEditor(string levelname) : eTransparent(false), eDrawWall(true) {
	mResourceManager = new ResourceManager("Data/resources.rsc");
	mAnimationManager = new AnimationManager(&mWorld);

	mSheets.push_back("tiles");
	mSheets.push_back("objects");
	mSheets.push_back("aTiles");
	mSheets.push_back("aObjects");

	mCurrentSheet = 0;

	tWindow.create(sf::VideoMode(mResourceManager->getTexture(mSheets.at(mCurrentSheet)).getSize().x, mResourceManager->getTexture(mSheets.at(mCurrentSheet)).getSize().y), mSheets.at(mCurrentSheet), sf::Style::Titlebar);
	tWindow.setPosition(sf::Vector2i(0, 0));
	eWindow.create(sf::VideoMode(1280, 960), "Level Editor", sf::Style::Close);
	eWindow.setVerticalSyncEnabled(true);
	eWindow.setFramerateLimit(165);

	eWindow.requestFocus();

	mView = eWindow.getDefaultView();

	mSheetSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));

	mSelector.spr.setFillColor(sf::Color(255, 0, 0, 160));
	mSelector.spr.setPosition(0, 0);
	mSelector.spr.setSize(sf::Vector2f(16, 16));

	mWorld.world_name = levelname;

	if (Load()) {
		cout << "SUCCESS: Loaded file named " << levelname << "." << endl;
	} else {
		cout << "ERROR: Failed to load file named " << levelname << "." << endl;
	}

	mResourceManager->getSong("DruidCity").setVolume(2.0f);
	mResourceManager->getSong("DruidCity").setLoop(true);
	mResourceManager->getSong("DruidCity").setPlayingOffset(sf::seconds(0.5f));
	mResourceManager->getSong("DruidCity").play();

	Run();
}

void LevelEditor::Run() {
	while (eWindow.isOpen()) {
		Input();
		Update();
		Render();
	}
}

void LevelEditor::Input() {

	// Editor Window Event Handling
	while (eWindow.pollEvent(mEvent)) {
		if (mEvent.type == sf::Event::Closed) {
			eWindow.close(); tWindow.close(); exit(0);
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

	// Tile Window Event Handling
	while (tWindow.pollEvent(mEvent)) {
		if (mEvent.type == sf::Event::KeyPressed) {
			if (mEvent.key.code == sf::Keyboard::LControl) {
				mInputContainer.keyboard_Ctrl = true;
			}
			if (mEvent.key.code == sf::Keyboard::LShift) {
				mInputContainer.keyboard_Shift = true;
			}
			if (mEvent.key.code == sf::Keyboard::F1) {
				mInputContainer.keyboard_F1 = true;
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
			if (mEvent.key.code == sf::Keyboard::LShift) {
				mInputContainer.keyboard_Shift = false;
			}
			if (mEvent.key.code == sf::Keyboard::F1) {
				mInputContainer.keyboard_F1 = false;
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
void LevelEditor::Update() {
	// Iterate Through Sheets
	if (mInputContainer.keyboard_F1) {
		if (mCurrentSheet == mSheets.size() - 1) {
			mCurrentSheet = 0;
		} else {
			mCurrentSheet++;
		}

		tWindow.create(sf::VideoMode(mResourceManager->getTexture(mSheets.at(mCurrentSheet)).getSize().x, mResourceManager->getTexture(mSheets.at(mCurrentSheet)).getSize().y), mSheets.at(mCurrentSheet), sf::Style::Titlebar);
		tWindow.setPosition(sf::Vector2i(0, 0));
		mSheetSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));
		eWindow.requestFocus();

		mInputContainer.keyboard_F1 = false;
	}
	// Place Tile 
	if (mInputContainer.mouse_Left && !mInputContainer.keyboard_Ctrl && eWindow.hasFocus() && mCurrentSheet == 0) {
		sf::Sprite tempSprite;
		tempSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));
		tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y), sf::Vector2i(mSelector.spr.getSize().x, mSelector.spr.getSize().y)));
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		tempSprite.setPosition(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);
		mWorld.worldTiles.push_back(Tile(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite));

		mInputContainer.mouse_Left = false;
	}
	// Place Animated Tile
	if (mInputContainer.mouse_Left && !mInputContainer.keyboard_Ctrl && eWindow.hasFocus() && mCurrentSheet == 2) {
		sf::Sprite tempSprite;
		tempSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));
		tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y), sf::Vector2i(mSelector.spr.getSize().x, mSelector.spr.getSize().y)));
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		tempSprite.setPosition(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);
		mWorld.worldTiles.push_back(Tile(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite, 8, 0));
		mAnimationManager->Reset();
		mInputContainer.mouse_Left = false;
	}
	// Place Object
	if (mInputContainer.mouse_Left && !mInputContainer.keyboard_Ctrl && eWindow.hasFocus() && mCurrentSheet == 1) {
		sf::Sprite tempSprite;
		tempSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));
		tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y), sf::Vector2i(mSelector.spr.getSize().x, mSelector.spr.getSize().y)));
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		tempSprite.setPosition(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);

		if (mInputContainer.keyboard_Alt) {
			string id;
			cout << "ID for Object: "; cin >> id;
			mWorld.objects.push_back(Object(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite, id));
		} else {
			mWorld.objects.push_back(Object(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite, to_string(mWorld.objects.size())));
		}

		mInputContainer.mouse_Left = false;
	}
	// Place Animated Object
	if (mInputContainer.mouse_Left && !mInputContainer.keyboard_Ctrl && eWindow.hasFocus() && mCurrentSheet == 3) {
		sf::Sprite tempSprite;
		
		tempSprite.setTexture(mResourceManager->getTexture(mSheets.at(mCurrentSheet)));
		tempSprite.setTextureRect(sf::IntRect(sf::Vector2i(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y), sf::Vector2i(mSelector.spr.getSize().x, mSelector.spr.getSize().y)));
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		tempSprite.setPosition(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);
		
		if (mInputContainer.keyboard_Alt) {
			string id;
			cout << "ID for Object: "; cin >> id;
			mWorld.objects.push_back(Object(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite, 4, 0, id));
		} else {
			mWorld.objects.push_back(Object(mSelector.spr.getPosition(), mSelector.spr.getSize(), tempSprite, 4, 0, to_string(mWorld.objects.size())));
		}
		
		mAnimationManager->Reset();
		mInputContainer.mouse_Left = false;
	}
	// Place Wall
	if (mInputContainer.mouse_Left && mInputContainer.keyboard_Ctrl && eWindow.hasFocus()) {
		sf::Sprite tempSprite;
		tempSprite.setTexture(mResourceManager->getTexture("selector"));
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		tempSprite.setPosition(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);

		mWorld.wallTiles.push_back(Tile(mSelector.spr.getPosition(), sf::Vector2f(16, 16), tempSprite));
		mInputContainer.mouse_Left = false;
	}
	// Remove Tile and Object
	if (mInputContainer.mouse_Right && !mInputContainer.keyboard_Ctrl && eWindow.hasFocus()) {
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		sf::Vector2f cursorIndexPos(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);
		bool done = false;
		for (vector<Object>::reverse_iterator iter = mWorld.objects.rbegin(); iter != mWorld.objects.rend(); ++iter) {
			if (iter->spr.getGlobalBounds().contains(mousePos)) {
				mWorld.objects.erase((iter + 1).base());
				done = true;
				break;
			}
		}
		if (!done) {
			for (vector<Tile>::reverse_iterator iter = mWorld.worldTiles.rbegin(); iter != mWorld.worldTiles.rend(); ++iter) {
				if (iter->spr.getGlobalBounds().contains(mousePos)) {
					mWorld.worldTiles.erase((iter + 1).base());
					break;
				}
			}
		}

		mInputContainer.mouse_Right = false;
	}
	// Remove Wall
	if (mInputContainer.mouse_Right && mInputContainer.keyboard_Ctrl && eWindow.hasFocus()) {
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(eWindow).x, sf::Mouse::getPosition(eWindow).y));
		sf::Vector2f cursorIndexPos(floor(mousePos.x / 16) * 16, floor(mousePos.y / 16) * 16);
		for (vector<Tile>::reverse_iterator iter = mWorld.wallTiles.rbegin(); iter != mWorld.wallTiles.rend(); ++iter) {
			if (iter->spr.getPosition() == cursorIndexPos) {
				mWorld.wallTiles.erase((iter + 1).base());
				break;
			}
		}

		mInputContainer.mouse_Right = false;
	}
	// Save Level
	if (mInputContainer.keyboard_Ctrl && mInputContainer.keyboard_S) {
		sf::sleep(sf::seconds(0.5f));
		if (Save()) {
			cout << "Saved Level " << mWorld.world_name << "." << endl;
		}
		else {
			cout << "ERROR: Failed to save level " << mWorld.world_name << "..." << endl;
		}
	}
	// Translate Level
	if (mInputContainer.mouse_Middle && eWindow.hasFocus()) {
		sf::Vector2f mousePos = eWindow.mapPixelToCoords(sf::Mouse::getPosition(eWindow));
		sf::Vector2f viewPos = mView.getCenter();
		mView.move(round((mousePos.x - viewPos.x) * 0.02), round((mousePos.y - viewPos.y) * 0.02));
		eWindow.setView(mView);
	}
	// Zoom Level
	if (mInputContainer.mouse_Wheel && eWindow.hasFocus()) {
		if (mInputContainer.mouse_Dir) {
			mView.zoom(0.5);
			eWindow.setView(mView);
		}
		else {
			mView.zoom(2.0f);
			eWindow.setView(mView);
		}
		mInputContainer.mouse_Wheel = false;
	}
	// Translate Selector
	if (mInputContainer.keyboard_W && !mInputContainer.keyboard_Shift) {
		mSelector.spr.setPosition(sf::Vector2f(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y - 16));
		mInputContainer.keyboard_W = false;
	}
	if (mInputContainer.keyboard_S && !mInputContainer.keyboard_Shift) {
		mSelector.spr.setPosition(sf::Vector2f(mSelector.spr.getPosition().x, mSelector.spr.getPosition().y + 16));
		mInputContainer.keyboard_S = false;
	}
	if (mInputContainer.keyboard_A && !mInputContainer.keyboard_Shift) {
		mSelector.spr.setPosition(sf::Vector2f(mSelector.spr.getPosition().x - 16, mSelector.spr.getPosition().y));
		mInputContainer.keyboard_A = false;
	}
	if (mInputContainer.keyboard_D && !mInputContainer.keyboard_Shift) {
		mSelector.spr.setPosition(sf::Vector2f(mSelector.spr.getPosition().x + 16, mSelector.spr.getPosition().y));
		mInputContainer.keyboard_D = false;
	}
	// Scale Selector
	if (mInputContainer.keyboard_W && mInputContainer.keyboard_Shift) {
		if (mSelector.spr.getSize().y != 16) {
			mSelector.spr.setSize(sf::Vector2f(mSelector.spr.getSize().x, mSelector.spr.getSize().y - 16));
			mInputContainer.keyboard_W = false;
		}
	}
	if (mInputContainer.keyboard_S && mInputContainer.keyboard_Shift) {
		mSelector.spr.setSize(sf::Vector2f(mSelector.spr.getSize().x, mSelector.spr.getSize().y + 16));
		mInputContainer.keyboard_S = false;
	}
	if (mInputContainer.keyboard_A && mInputContainer.keyboard_Shift) {
		if (mSelector.spr.getSize().x != 16) {
			mSelector.spr.setSize(sf::Vector2f(mSelector.spr.getSize().x - 16, mSelector.spr.getSize().y));
			mInputContainer.keyboard_A = false;
		}
	}
	if (mInputContainer.keyboard_D && mInputContainer.keyboard_Shift) {
		mSelector.spr.setSize(sf::Vector2f(mSelector.spr.getSize().x + 16, mSelector.spr.getSize().y));
		mInputContainer.keyboard_D = false;
	}
	// Check For Duplicates
	if (mInputContainer.keyboard_O && eWindow.hasFocus()) {
		eTransparent = !eTransparent;
		if (eTransparent) {
			for (auto it = mWorld.worldTiles.begin(); it != mWorld.worldTiles.end(); it++) {
				it->spr.setColor(sf::Color(255, 255, 255, 128));
			}
		} else {
			for (auto it = mWorld.worldTiles.begin(); it != mWorld.worldTiles.end(); it++) {
				it->spr.setColor(sf::Color(255, 255, 255, 255));
			}
		}
		mInputContainer.keyboard_O = false;
	}
	// Draw Wall
	if (mInputContainer.keyboard_G && eWindow.hasFocus()) {
		eDrawWall = !eDrawWall;
		mInputContainer.keyboard_G = false;
	}
	// Tile Selection (T Window)
	if (mInputContainer.mouse_Left && tWindow.hasFocus()) {
		mSelector.startPos = sf::Vector2f(sf::Mouse::getPosition(tWindow).x / 16 * 16, sf::Mouse::getPosition(tWindow).y / 16 * 16);
		mSelector.spr.setPosition(sf::Vector2f(sf::Mouse::getPosition(tWindow).x / 16 * 16, sf::Mouse::getPosition(tWindow).y / 16 * 16));
		mSelector.spr.setSize(sf::Vector2f(16, 16));
		mInputContainer.mouse_Left = false;
	}
	if (mEvent.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) && tWindow.hasFocus()) {
		mSelector.currentPos.x = ceil((sf::Mouse::getPosition(tWindow).x - mSelector.startPos.x) / 16) * 16;
		mSelector.currentPos.y = ceil((sf::Mouse::getPosition(tWindow).y - mSelector.startPos.y) / 16) * 16;
		mSelector.spr.setSize(mSelector.currentPos);
	}

	// Update Animations
	mAnimationManager->Update();
}
void LevelEditor::Render() {
	tWindow.clear(sf::Color(4, 5, 18)); eWindow.clear(sf::Color(4, 5, 18));
	tWindow.draw(mSheetSprite);

	for (auto it = mWorld.worldTiles.begin(); it != mWorld.worldTiles.end(); it++) {
		eWindow.draw((*it).spr);
	}
	for (auto it = mWorld.objects.begin(); it != mWorld.objects.end(); it++) {
		eWindow.draw((*it).spr);
	}
	if (eDrawWall) {
		for (auto it = mWorld.wallTiles.begin(); it != mWorld.wallTiles.end(); it++) {
			eWindow.draw((*it).spr);
		}
	}
	tWindow.draw(mSelector.spr);

	tWindow.display(); eWindow.display();
}

bool LevelEditor::Save() {
	ofstream levelFile(mWorld.world_name);
	if (levelFile.fail()) {
		cout << "ERROR: Failed to open file..." << endl;
		return false;
	}

	levelFile << mWorld.worldTiles.size() << " " << mWorld.wallTiles.size() << " " << mWorld.objects.size() << endl;

	for (auto it = mWorld.worldTiles.begin(); it != mWorld.worldTiles.end(); it++) {
		levelFile << it->animated << " " << it->tilePos.x << " " << it->tilePos.y << " " << it->tileSize.x << " " << it->tileSize.y << " " << it->spr.getPosition().x << " " << it->spr.getPosition().y << " " << it->currentFrame << " " << it->frameCount << endl;
	}
	for (auto it = mWorld.wallTiles.begin(); it != mWorld.wallTiles.end(); it++) {
		levelFile << it->spr.getPosition().x << " " << it->spr.getPosition().y << endl;
	}
	for (auto it = mWorld.objects.begin(); it != mWorld.objects.end(); it++) {
		levelFile << it->id << " " << it->animated << " " << it->tilePos.x << " " << it->tilePos.y << " " << it->tileSize.x << " " << it->tileSize.y << " " << it->spr.getPosition().x << " " << it->spr.getPosition().y << " " << it->currentFrame << " " << it->frameCount << endl;
	}
	levelFile.close();
	/*
	sf::Texture worldTexture; worldTexture.create(1280, 960); worldTexture.update(eWindow);
	sf::Image world = worldTexture.copyToImage();
	string filename = mWorld.world_name + ".png";
	world.saveToFile(filename);
	*/
	return true;
}

bool LevelEditor::Load() {
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
		} else {
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