#include "ResourceManager.h"
ResourceManager::ResourceManager(std::string resourceLoc) {
	std::fstream fin(resourceLoc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	if (!fin.is_open()) { std::cout << "Error: Could not open " << resourceLoc << std::endl; return; }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::string fileLoc, name, type;
	while (fin >> fileLoc >> name >> type) {
		if (type == "TEXTURE") {
			this->addTexture(fileLoc, name);
			continue;
		}
		if (type == "FONT") {
			this->addFont(fileLoc, name);
			continue;
		}
		if (type == "SOUNDBUFFER") {
			this->addSoundBuffer(fileLoc, name);
			continue;
		}
		if (type == "SONG") {
			this->addSong(fileLoc, name);
			continue;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "Error: Invalid file type: " << type << " for " << fileLoc << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	fin.close();
	std::cout << resourceLoc;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << " loaded successfully..." << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ResourceManager::addTexture(std::string fileLoc, std::string name) {
	std::cout << "Loading TEXTURE at " << fileLoc << "\tID: " << name << "...";
	mTextures[name] = new sf::Texture;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	if (!mTextures[name]->loadFromFile(fileLoc)) { 
		removeTexture(name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
		return; 
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "Loading complete." << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}
void ResourceManager::addFont(std::string fileLoc, std::string name) {
	std::cout << "Loading FONT at " << fileLoc << " \tID: " << name << "...";
	mFonts[name] = new sf::Font;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	if (!mFonts[name]->loadFromFile(fileLoc)) { 
		removeFont(name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
		return;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "Loading complete." << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}
void ResourceManager::addSoundBuffer(std::string fileLoc, std::string name) {
	std::cout << "Loading SOUNDBUFFER at " << fileLoc << "\tID: " << name << "...";
	mSoundBuffers[name] = new sf::SoundBuffer;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	if (mSoundBuffers[name]->loadFromFile(fileLoc)) {
		removeSoundBuffer(name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "Loading complete." << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}
void ResourceManager::addSong(std::string fileLoc, std::string name) {
	std::cout << "Loading SONG at " << fileLoc << "\tID: " << name << "...";
	mSongs[name] = new sf::Music;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	if (!mSongs[name]->openFromFile(fileLoc)) {
		removeSong(name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "Loading complete." << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}

void ResourceManager::removeTexture(std::string name) {
	std::cout << "Removing " << name << "...";
	delete mTextures.at(name);
	mTextures.erase(name);
	std::cout << "Removal complete." << std::endl;
}
void ResourceManager::removeFont(std::string name) {
	std::cout << "Removing " << name << "...";
	delete mFonts.at(name);
	mFonts.erase(name);
	std::cout << "Removal complete." << std::endl;
}
void ResourceManager::removeSoundBuffer(std::string name) {
	std::cout << "Removing " << name << "...";
	delete mSoundBuffers.at(name);
	mSoundBuffers.erase(name);
	std::cout << "Removal complete." << std::endl;
}
void ResourceManager::removeSong(std::string name) {
	std::cout << "Removing " << name << "...";
	delete mSongs.at(name);
	mSongs.erase(name);
	std::cout << "Removal complete." << std::endl;
}

sf::Texture& ResourceManager::getTexture(std::string name) {
	return *mTextures.at(name);
}
sf::Font& ResourceManager::getFont(std::string name) {
	return *mFonts.at(name);
}
sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string name) {
	return *mSoundBuffers.at(name);
}
sf::Music& ResourceManager::getSong(std::string name) {
	return *mSongs.at(name);
}