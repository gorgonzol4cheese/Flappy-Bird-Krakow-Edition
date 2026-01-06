#pragma once

#include <iostream>
#include <string>
#include <map> //do przechowywania tekstur i czcionek
#include <SFML/Graphics.hpp>
using namespace std;

namespace Flappy {
	//MENADZER ZASOBOW -> do przechowywania tekstur i czcionek
	//zapewnia, ze nie bedziemy ladowac ciagle tych samych rzeczy
	class AssetManager {
	public:
		AssetManager(){} //konstruktor
		~AssetManager() {} //dekonstruktor

		//wczytuje plik z dysku do pamieci
		void LoadTexture(string name, string fileName); //stad bierze nazwe tekstury do &GetTexture
		sf::Texture& GetTexture(string name); //zwroci referencje nazwy tekstury - nie kopiuje tylko daje bezposredni dostep do juz zaladowanej rzeczy

		void LoadFont(string name, string fileName); 
		sf::Font& GetFont(string name);

	private: //zamiast szukac na dysku
		map<string, sf::Texture> _textures;
		map<string, sf::Font> _fonts;
	};
}