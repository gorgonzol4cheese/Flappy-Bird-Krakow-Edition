#include "AssetManager.h"
//#include <iostream>
//#include <string>
//#include <SFML/Graphics.hpp> //nie musimy tego dodawac bo jest w AssetManager.h
//using namespace std;

namespace Flappy {

	//TEKSTURY
	void AssetManager::LoadTexture(string name, string fileName) { //rejestrowanie obrazow
		sf::Texture tex; //tworzy obiekt struktury

		if (tex.loadFromFile(fileName)) { //ladowanie/wczytywanie tekstur
			this->_textures[name] = tex; //zapisuje tekture w map, pod podana nazwa
		}
	}

	sf::Texture& AssetManager::GetTexture(string name) {
		return this->_textures.at(name);
	}

	//CZCIONKI
	void AssetManager::LoadFont(string name, string fileName) {
		sf::Font font;

		if (font.loadFromFile(fileName)) { //ladowanie czcionek
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(string name) {
		return this->_fonts.at(name);
	}
}