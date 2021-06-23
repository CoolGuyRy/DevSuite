#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <fstream>
#include <sfml/Graphics.hpp>
#include <sfml/Audio.hpp>
#include <Windows.h>

class ResourceManager {
private:
	std::map<std::string, sf::Texture*> mTextures;
	std::map<std::string, sf::Font*> mFonts;
	std::map<std::string, sf::SoundBuffer*> mSoundBuffers;
	std::map<std::string, sf::Music*> mSongs;
public:
	ResourceManager(std::string);

	void addTexture(std::string, std::string);
	void addFont(std::string, std::string);
	void addSoundBuffer(std::string, std::string);
	void addSong(std::string, std::string);

	void removeTexture(std::string);
	void removeFont(std::string);
	void removeSoundBuffer(std::string);
	void removeSong(std::string);

	sf::Texture& getTexture(std::string);
	sf::Font& getFont(std::string);
	sf::SoundBuffer& getSoundBuffer(std::string);
	sf::Music& getSong(std::string);
};
#endif